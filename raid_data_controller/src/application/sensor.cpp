#include "application/sensor.hpp"

using namespace raid::data;

SensorService::SensorService(const rclcpp::Node::SharedPtr &node, const Parameter::SharedPtr &parameter)
    : node_(node)
    , parameter_(parameter)
{
    this->sensor_ = std::make_shared<raid_msgs::msg::Sensor>();
    this->message_ = std::make_shared<raid::common::Message>();

    this->sensor_publish_timer_cb_group_ = this->node_->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    this->sensor_publish_timer_ = this->node_->create_wall_timer(
        std::chrono::milliseconds(this->parameter_->sensor_rate_),
        std::bind(&SensorService::sensor_publish_timer_cb, this),
        this->sensor_publish_timer_cb_group_);

    this->sensor_publisher_cb_group_ = this->node_->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    rclcpp::PublisherOptions sensor_publisher_opts;
    sensor_publisher_opts.callback_group = this->sensor_publisher_cb_group_;
    this->sensor_publisher_ = this->node_->create_publisher<raid_msgs::msg::Sensor>(
        this->parameter_->sensor_topic_,
        rclcpp::QoS(rclcpp::SensorDataQoS()),
        sensor_publisher_opts);

    this->scan_subscription_cb_group_ = this->node_->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    rclcpp::SubscriptionOptions scan_subscription_opts;
    scan_subscription_opts.callback_group = this->scan_subscription_cb_group_;
    this->scan_subscription_ = this->node_->create_subscription<sensor_msgs::msg::LaserScan>(
        this->parameter_->sensor_lidar_topic_,
        rclcpp::QoS(rclcpp::SensorDataQoS()),
        std::bind(&SensorService::scan_subscription_cb, this, _1),
        scan_subscription_opts);

    this->imu_subscription_cb_group_ = this->node_->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    rclcpp::SubscriptionOptions imu_subscription_opts;
    imu_subscription_opts.callback_group = this->imu_subscription_cb_group_;
    this->imu_subscription_ = this->node_->create_subscription<sensor_msgs::msg::Imu>(
        this->parameter_->sensor_imu_topic_,
        rclcpp::QoS(rclcpp::SensorDataQoS()),
        std::bind(&SensorService::imu_subscription_cb, this, _1),
        imu_subscription_opts);

    this->gps_subscription_cb_group_ = this->node_->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    rclcpp::SubscriptionOptions gps_subscription_opts;
    gps_subscription_opts.callback_group = this->gps_subscription_cb_group_;
    this->gps_subscription_ = this->node_->create_subscription<sensor_msgs::msg::NavSatFix>(
        this->parameter_->sensor_gps_topic_,
        rclcpp::QoS(rclcpp::SensorDataQoS()),
        std::bind(&SensorService::gps_subscription_cb, this, _1),
        gps_subscription_opts);

    this->battery_state_subscription_cb_group_ = this->node_->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    rclcpp::SubscriptionOptions battery_state_subscription_opts;
    battery_state_subscription_opts.callback_group = this->battery_state_subscription_cb_group_;
    this->battery_state_subscription_ = this->node_->create_subscription<sensor_msgs::msg::BatteryState>(
        this->parameter_->sensor_battery_topic_,
        rclcpp::QoS(rclcpp::SensorDataQoS()),
        std::bind(&SensorService::battery_state_subscription_cb, this, _1),
        battery_state_subscription_opts);

    this->temperature_subscription_cb_group_ = this->node_->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    rclcpp::SubscriptionOptions temperature_subscription_opts;
    temperature_subscription_opts.callback_group = this->temperature_subscription_cb_group_;
    this->temperature_subscription_ = this->node_->create_subscription<sensor_msgs::msg::Temperature>(
        this->parameter_->sensor_temperature_topic_,
        rclcpp::QoS(rclcpp::SensorDataQoS()),
        std::bind(&SensorService::temperature_subscription_cb, this, _1),
        temperature_subscription_opts);
}

SensorService::~SensorService() = default;

void
SensorService::sensor_publish_timer_cb()
{
    const std_msgs::msg::Header &header = this->message_->build_header(this->node_->now(), "raid_sensor");
    this->sensor_->set__header(header);
    this->sensor_publisher_->publish(*this->sensor_);
}

void
SensorService::scan_subscription_cb(const sensor_msgs::msg::LaserScan::SharedPtr scan)
{
    this->sensor_->set__scan(*scan);
}

void
SensorService::imu_subscription_cb(const sensor_msgs::msg::Imu::SharedPtr imu)
{
    this->sensor_->set__imu(*imu);
}

void
SensorService::gps_subscription_cb(const sensor_msgs::msg::NavSatFix::SharedPtr gps)
{
    this->sensor_->set__gps(*gps);
}

void
SensorService::battery_state_subscription_cb(const sensor_msgs::msg::BatteryState::SharedPtr battery_state)
{
    this->sensor_->set__battery(*battery_state);
}

void
SensorService::temperature_subscription_cb(const sensor_msgs::msg::Temperature::SharedPtr temperature)
{
    this->sensor_->set__temperature(*temperature);
}