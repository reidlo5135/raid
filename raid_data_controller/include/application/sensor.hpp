#ifndef APPLICATION_SENSOR_HPP
#define APPLICATION_SENSOR_HPP

#include <rclcpp/rclcpp.hpp>
#include <raid_msgs/msg/sensor.hpp>
#include <raid_common/message.hpp>
#include <std_msgs/msg/header.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <sensor_msgs/msg/battery_state.hpp>
#include <sensor_msgs/msg/temperature.hpp>

#include "domain/parameter.hpp"

using std::placeholders::_1;

namespace raid
{
    namespace data
    {
        class SensorService final
        {
        private:
            rclcpp::Node::SharedPtr node_;
            Parameter::SharedPtr parameter_;
            raid_msgs::msg::Sensor::SharedPtr sensor_;
            raid::common::Message::SharedPtr message_;

            rclcpp::CallbackGroup::SharedPtr sensor_publish_timer_cb_group_;
            rclcpp::TimerBase::SharedPtr sensor_publish_timer_;
            void sensor_publish_timer_cb();

            rclcpp::CallbackGroup::SharedPtr sensor_publisher_cb_group_;
            rclcpp::Publisher<raid_msgs::msg::Sensor>::SharedPtr sensor_publisher_;

            rclcpp::CallbackGroup::SharedPtr scan_subscription_cb_group_;
            rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_subscription_;
            void scan_subscription_cb(const sensor_msgs::msg::LaserScan::SharedPtr scan);

            rclcpp::CallbackGroup::SharedPtr imu_subscription_cb_group_;
            rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscription_;
            void imu_subscription_cb(const sensor_msgs::msg::Imu::SharedPtr imu);

            rclcpp::CallbackGroup::SharedPtr gps_subscription_cb_group_;
            rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr gps_subscription_;
            void gps_subscription_cb(const sensor_msgs::msg::NavSatFix::SharedPtr gps);

            rclcpp::CallbackGroup::SharedPtr battery_state_subscription_cb_group_;
            rclcpp::Subscription<sensor_msgs::msg::BatteryState>::SharedPtr battery_state_subscription_;
            void battery_state_subscription_cb(const sensor_msgs::msg::BatteryState::SharedPtr battery_state);

            rclcpp::CallbackGroup::SharedPtr temperature_subscription_cb_group_;
            rclcpp::Subscription<sensor_msgs::msg::Temperature>::SharedPtr temperature_subscription_;
            void temperature_subscription_cb(const sensor_msgs::msg::Temperature::SharedPtr temperature);

        public:
            explicit SensorService(const rclcpp::Node::SharedPtr &node = nullptr, const Parameter::SharedPtr &parameter = nullptr);
            virtual ~SensorService();

        public:
            using SharedPtr = std::shared_ptr<SensorService>;

        };
    }
}

#endif