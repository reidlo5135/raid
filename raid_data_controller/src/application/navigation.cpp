#include "application/navigation.hpp"

using namespace raid::data;

NavigationService::NavigationService(const rclcpp::Node::SharedPtr &node, const Parameter::SharedPtr &parameter)
    : node_(node)
    , parameter_(parameter)
{
    this->navigation_ = std::make_shared<raid_msgs::msg::Navigation>();
    this->message_ = std::make_shared<raid::common::Message>();

    this->navigation_publish_timer_cb_group_ = this->node_->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    this->navigation_publish_timer_ = this->node_->create_wall_timer(
        std::chrono::milliseconds(this->parameter_->navigation_rate_),
        std::bind(&NavigationService::navigation_publish_timer_cb, this),
        this->navigation_publish_timer_cb_group_);

    this->navigation_publisher_cb_group_ = this->node_->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    rclcpp::PublisherOptions navigation_publisher_opts;
    navigation_publisher_opts.callback_group = this->navigation_publisher_cb_group_;
    this->navigation_publisher_ = this->node_->create_publisher<raid_msgs::msg::Navigation>(
        this->parameter_->navigation_topic_,
        rclcpp::QoS(rclcpp::SystemDefaultsQoS()),
        navigation_publisher_opts);

    this->velocity_subscription_cb_group_ = this->node_->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    rclcpp::SubscriptionOptions velocity_subscription_opts;
    velocity_subscription_opts.callback_group = this->velocity_subscription_cb_group_;
    this->velocity_subscription_ = this->node_->create_subscription<geometry_msgs::msg::Twist>(
        this->parameter_->navigation_velocity_topic_,
        rclcpp::QoS(rclcpp::SystemDefaultsQoS()),
        std::bind(&NavigationService::velocity_subscription_cb, this, _1),
        velocity_subscription_opts);

    this->slam_pose_subscription_cb_group_ = this->node_->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    rclcpp::SubscriptionOptions slam_pose_subscription_opts;
    slam_pose_subscription_opts.callback_group = this->slam_pose_subscription_cb_group_;
    this->slam_pose_subscription_ = this->node_->create_subscription<geometry_msgs::msg::PoseStamped>(
        this->parameter_->navigation_slam_pose_topic_,
        rclcpp::QoS(rclcpp::SystemDefaultsQoS()),
        std::bind(&NavigationService::slam_pose_subscription_cb, this, _1),
        slam_pose_subscription_opts);

    this->plan_subscription_cb_group_ = this->node_->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    rclcpp::SubscriptionOptions plan_subscription_opts;
    plan_subscription_opts.callback_group = this->plan_subscription_cb_group_;
    this->plan_subscription_ = this->node_->create_subscription<nav_msgs::msg::Path>(
        this->parameter_->navigation_plan_topic_,
        rclcpp::QoS(rclcpp::SystemDefaultsQoS()),
        std::bind(&NavigationService::plan_subscription_cb, this, _1),
        plan_subscription_opts);
}

NavigationService::~NavigationService() = default;

void
NavigationService::navigation_publish_timer_cb()
{
    const std_msgs::msg::Header &header = this->message_->build_header(this->node_->now(), "raid_navigation");
    this->navigation_->set__header(header);
    this->navigation_publisher_->publish(*this->navigation_);
}

void
NavigationService::velocity_subscription_cb(const geometry_msgs::msg::Twist::SharedPtr velocity)
{
    this->navigation_->set__velocity(*velocity);
}

void
NavigationService::slam_pose_subscription_cb(const geometry_msgs::msg::PoseStamped::SharedPtr slam_pose)
{
    this->navigation_->set__slam_pose(*slam_pose);
}

void
NavigationService::plan_subscription_cb(const nav_msgs::msg::Path::SharedPtr plan)
{
    this->navigation_->set__plan(*plan);
}