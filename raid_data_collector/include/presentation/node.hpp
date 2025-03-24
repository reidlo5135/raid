#ifndef PRESENTATION_NODE_HPP
#define PRESENTATION_NODE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <yaml-cpp/yaml.h>

#include <rclcpp/rclcpp.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>

#include "application/navigation.hpp"

#define NODE_NAME "raid_data_collector"
#define RCL_LOG_INFO(logger, format, ...)  RCLCPP_INFO(logger, "%s():%d:" format, __func__, __LINE__, ##__VA_ARGS__)
#define RCL_LOG_WARN(logger, format, ...)  RCLCPP_WARN(logger, "%s():%d:" format, __func__, __LINE__, ##__VA_ARGS__)
#define RCL_LOG_DEBUG(logger, format, ...) RCLCPP_DEBUG(logger, "%s():%d:" format, __func__, __LINE__, ##__VA_ARGS__)
#define RCL_LOG_ERROR(logger, format, ...) RCLCPP_ERROR(logger, "%s():%d:" format, __func__, __LINE__, ##__VA_ARGS__)
#define RCL_LOG_FATAL(logger, format, ...) RCLCPP_FATAL(logger, "%s():%d:" format, __func__, __LINE__, ##__VA_ARGS__)

namespace raid
{
    class DataCollector final : public rclcpp::Node
    {
    private:
        rclcpp::Node::SharedPtr node_;
        Navigation::SharedPtr navigation_;

    private:
        std::pair<std::vector<std::string>, std::vector<std::variant<std::string, std::vector<std::string>, int, double, bool>>>
        extract_parameter_from_yaml(const YAML::Node &node, const std::string &prefix = "");
        void declare_parameters();

    public:
        explicit DataCollector();
        virtual ~DataCollector();

    };
}

#endif // PRESENTATION_NODE_HPP
