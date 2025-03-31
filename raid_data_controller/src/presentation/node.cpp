#include "presentation/node.hpp"

using namespace raid::data;

DataControllerNode::DataControllerNode()
    : Node(NODE_NAME)
{
    this->node_ = std::shared_ptr<rclcpp::Node>(this, [](rclcpp::Node *){});

    if (!this->node_)
    {
        RCLCPP_ERROR(this->node_->get_logger(), "[%s] node pointer've not been assigned.", NODE_NAME);
        rclcpp::shutdown();
    }
    else
    {
        RCLCPP_INFO(this->node_->get_logger(), "[%s] executed.", this->node_->get_name());

        this->parameter_ = std::make_shared<Parameter>();
        this->declare_parameters();
        this->navigation_service_ = std::make_shared<NavigationService>(this->node_, this->parameter_);
        this->sensor_service_ = std::make_shared<SensorService>(this->node_, this->parameter_);
    }
}

DataControllerNode::~DataControllerNode() = default;

void
DataControllerNode::declare_parameters()
{
    std::vector<std::pair<std::string, std::variant<std::string, int>>> param_vec =
    {
        {PARAM_SENSOR_TOPIC, ""},
        {PARAM_SENSOR_RATE, 0},
        {PARAM_SENSOR_LIDAR_TOPIC, ""},
        {PARAM_SENSOR_IMU_TOPIC, ""},
        {PARAM_SENSOR_GPS_TOPIC, ""},
        {PARAM_SENSOR_BATTERY_TOPIC, ""},
        {PARAM_SENSOR_TEMPERATURE_TOPIC, ""},
        {PARAM_NAVIGATION_TOPIC, ""},
        {PARAM_NAVIGATION_RATE, 0},
        {PARAM_NAVGATION_VELOCITY_TOPIC, ""},
        {PARAM_NAVIGATION_SLAM_POSE_TOPIC, ""},
        {PARAM_NAVIGATION_PLAN_TOPIC, ""}
    };

    for (const auto &param : param_vec)
    {
        const std::string &param_name = param.first;
        const auto &default_value = param.second;

        std::visit([this, &param_name](auto &&value)
        {
            using T = std::decay_t<decltype(value)>;
            this->node_->declare_parameter<T>(param_name, value);
        }, default_value);
    }

    this->node_->get_parameter<std::string>(PARAM_SENSOR_TOPIC, this->parameter_->sensor_topic_);
    this->node_->get_parameter<int>(PARAM_SENSOR_RATE, this->parameter_->sensor_rate_);
    this->node_->get_parameter<std::string>(PARAM_SENSOR_LIDAR_TOPIC, this->parameter_->sensor_lidar_topic_);
    this->node_->get_parameter<std::string>(PARAM_SENSOR_IMU_TOPIC, this->parameter_->sensor_imu_topic_);
    this->node_->get_parameter<std::string>(PARAM_SENSOR_GPS_TOPIC, this->parameter_->sensor_gps_topic_);
    this->node_->get_parameter<std::string>(PARAM_SENSOR_BATTERY_TOPIC, this->parameter_->sensor_battery_topic_);
    this->node_->get_parameter<std::string>(PARAM_SENSOR_TEMPERATURE_TOPIC, this->parameter_->sensor_temperature_topic_);
    this->node_->get_parameter<std::string>(PARAM_NAVIGATION_TOPIC, this->parameter_->navigation_topic_);
    this->node_->get_parameter<int>(PARAM_NAVIGATION_RATE, this->parameter_->navigation_rate_);
    this->node_->get_parameter<std::string>(PARAM_NAVGATION_VELOCITY_TOPIC, this->parameter_->navigation_velocity_topic_);
    this->node_->get_parameter<std::string>(PARAM_NAVIGATION_SLAM_POSE_TOPIC, this->parameter_->navigation_slam_pose_topic_);
    this->node_->get_parameter<std::string>(PARAM_NAVIGATION_PLAN_TOPIC, this->parameter_->navigation_plan_topic_);
}