#ifndef APPLICATION_NAVIGATION_HPP
#define APPLICATION_NAVIGATION_HPP

#include <rclcpp/rclcpp.hpp>
#include <raid_msgs/msg/navigation.hpp>
#include <raid_common/message.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/path.hpp>

#include "domain/parameter.hpp"

using std::placeholders::_1;

namespace raid
{
    namespace data
    {
        class NavigationService final
        {
        private:
            rclcpp::Node::SharedPtr node_;
            Parameter::SharedPtr parameter_;
            raid_msgs::msg::Navigation::SharedPtr navigation_;
            raid::common::Message::SharedPtr message_;

            rclcpp::CallbackGroup::SharedPtr navigation_publish_timer_cb_group_;
            rclcpp::TimerBase::SharedPtr navigation_publish_timer_;
            void navigation_publish_timer_cb();

            rclcpp::CallbackGroup::SharedPtr navigation_publisher_cb_group_;
            rclcpp::Publisher<raid_msgs::msg::Navigation>::SharedPtr navigation_publisher_;

            rclcpp::CallbackGroup::SharedPtr velocity_subscription_cb_group_;
            rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr velocity_subscription_;
            void velocity_subscription_cb(const geometry_msgs::msg::Twist::SharedPtr velocity);

            rclcpp::CallbackGroup::SharedPtr slam_pose_subscription_cb_group_;
            rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr slam_pose_subscription_;
            void slam_pose_subscription_cb(const geometry_msgs::msg::PoseStamped::SharedPtr slam_pose);

            rclcpp::CallbackGroup::SharedPtr plan_subscription_cb_group_;
            rclcpp::Subscription<nav_msgs::msg::Path>::SharedPtr plan_subscription_;
            void plan_subscription_cb(const nav_msgs::msg::Path::SharedPtr plan);

        public:
            explicit NavigationService(const rclcpp::Node::SharedPtr &node = nullptr, const Parameter::SharedPtr &parameter = nullptr);
            virtual ~NavigationService();

        public:
            using SharedPtr = std::shared_ptr<NavigationService>;

        };
    }
}

#endif