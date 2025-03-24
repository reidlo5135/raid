#include "presentation/node.hpp"

using namespace raid;

DataCollector::DataCollector()
    : Node(NODE_NAME)
{
    this->node_ = std::shared_ptr<rclcpp::Node>(this, [](rclcpp::Node *){});

    if (this->node_)
    {
        RCL_LOG_INFO(this->node_->get_logger(), "Node... OK");
        this->declare_parameters();

        this->navigation_ = std::make_shared<Navigation>(this->node_);

        if (this->navigation_)
        {
            RCL_LOG_INFO(this->node_->get_logger(), "Navigation... OK");
        }
        else
        {
            RCL_LOG_ERROR(this->node_->get_logger(), "Navigation... NOT OK");
        }
    }
    else
    {
        RCL_LOG_ERROR(this->node_->get_logger(), "Node... NOT OK");
    }
}

DataCollector::~DataCollector()
{
}

std::pair<std::vector<std::string>, std::vector<std::variant<std::string, std::vector<std::string>, int, double, bool>>>
DataCollector::extract_parameter_from_yaml(const YAML::Node &node, const std::string &prefix)
{
    std::pair<std::vector<std::string>, std::vector<std::variant<std::string, std::vector<std::string>, int, double, bool>>> parameter_pair;
    std::vector<std::string> parameter_key_vec;
    std::vector<std::variant<std::string, std::vector<std::string>, int, double, bool>> parameter_value_variant_vec;

    for (auto it = node.begin(); it != node.end(); ++it)
    {
        std::string key = it->first.as<std::string>();
        std::string full_key = prefix.empty() ? key : prefix + "." + key;

        if (it->second.IsMap())
        {
            std::pair<std::vector<std::string>, std::vector<std::variant<std::string, std::vector<std::string>, int, double, bool>>> child_keys = this->extract_parameter_from_yaml(it->second, full_key);
            parameter_key_vec.insert(parameter_key_vec.end(), child_keys.first.begin(), child_keys.first.end());
            parameter_value_variant_vec.insert(parameter_value_variant_vec.end(), child_keys.second.begin(), child_keys.second.end());
        }
        else if (it->second.IsScalar())
        {
            RCL_LOG_INFO(this->node_->get_logger(), "full_key : %s", full_key.c_str());
            std::string delimiter = ".ros__parameters.";
            const size_t &pos = full_key.find(delimiter);
            std::string key = "";

            if (pos != std::string::npos)
            {
                key = full_key.substr(pos + delimiter.length());
                RCL_LOG_INFO(this->node_->get_logger(), "parameter key : %s", key.c_str());
                parameter_key_vec.push_back(key);
            }

            try
            {
                std::string value = it->second.as<std::string>();

                if (value.size() > 0)
                {
                    parameter_value_variant_vec.push_back("");
                }
                if (value == "true" || value == "false")
                {
                    parameter_value_variant_vec.push_back(false);
                }
                if (std::stoi(value) >= 0 || std::stoi(value) < 0)
                {
                    parameter_value_variant_vec.push_back(0.0);
                }
                // if (it->second.as<int>() || value.find_first_not_of("-0123456789") == std::string::npos)
                // {
                //     parameter_value_variant_vec.push_back(0);
                // }
                if (std::stod(value) >= 0.0 || std::stod(value) < 0.0)
                {
                    parameter_value_variant_vec.push_back(0.0);
                }
            }
            catch (const std::exception &expn)
            {
                RCL_LOG_ERROR(this->node_->get_logger(), "Failed to parse value for key: %s. Defaulting to empty string.", key.c_str());
                parameter_value_variant_vec.push_back("");
            }
        }
    }

    parameter_pair.first = parameter_key_vec;
    parameter_pair.second = parameter_value_variant_vec;
    return parameter_pair;
}

void
DataCollector::declare_parameters()
{
    try
    {
        const std::string &package_path = ament_index_cpp::get_package_share_directory(this->node_->get_name());
        const std::string &file_name = package_path + "/config/" + this->node_->get_name() + ".yaml";
        const YAML::Node &config = YAML::LoadFile(file_name);

        const auto &parameter_pair = this->extract_parameter_from_yaml(config, file_name);
        const std::vector<std::string> &parameter_key_vec = parameter_pair.first;
        const std::vector<std::variant<std::string, std::vector<std::string>, int, double, bool>> &parameter_value_vec = parameter_pair.second;

        if (parameter_key_vec.empty())
        {
            RCL_LOG_ERROR(this->node_->get_logger(), "Parameter key vector is empty");
            return;
        }

        if (parameter_value_vec.empty())
        {
            RCL_LOG_ERROR(this->node_->get_logger(), "Parameter value vector is empty");
            return;
        }

        for (int i = 0;i < parameter_key_vec.size();i++)
        {
            const std::string &key = parameter_key_vec[i];
            const std::variant<std::string, std::vector<std::string>, int, double, bool> &variant = parameter_value_vec[i];

            std::visit([this, &key](auto &&variant)
            {
                using T = std::decay_t<decltype(variant)>;
                this->node_->declare_parameter<T>(key, variant);
            }, variant);

            RCL_LOG_INFO(this->node_->get_logger(), "<%d>[%s] declared", i, key.c_str());
        }
    }
    catch (const std::exception &expn)
    {
        RCL_LOG_ERROR(this->node_->get_logger(), "%s", expn.what());
    }
}