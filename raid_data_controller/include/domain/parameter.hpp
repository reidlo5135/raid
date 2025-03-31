#ifndef DOMAIN_PARAMETER_HPP
#define DOMAIN_PARAMETER_HPP

#include <memory>
#include <string>

#define PARAM_SENSOR_TOPIC "sensor.topic"
#define PARAM_SENSOR_RATE "sensor.rate"
#define PARAM_SENSOR_LIDAR_TOPIC "sensor.lidar.topic"
#define PARAM_SENSOR_IMU_TOPIC "sensor.imu.topic"
#define PARAM_SENSOR_GPS_TOPIC "sensor.gps.topic"
#define PARAM_SENSOR_BATTERY_TOPIC "sensor.battery.topic"
#define PARAM_SENSOR_TEMPERATURE_TOPIC "sensor.temperature.topic"
#define PARAM_NAVIGATION_TOPIC "navigation.topic"
#define PARAM_NAVIGATION_RATE "navigation.rate"
#define PARAM_NAVGATION_VELOCITY_TOPIC "navigation.velocity.topic"
#define PARAM_NAVIGATION_SLAM_POSE_TOPIC "navigation.slam_pose.topic"
#define PARAM_NAVIGATION_PLAN_TOPIC "navigation.plan.topic"


namespace raid
{
    namespace data
    {
        class Parameter final
        {
        public:
            std::string sensor_topic_;
            int sensor_rate_;
            std::string sensor_lidar_topic_;
            std::string sensor_imu_topic_;
            std::string sensor_gps_topic_;
            std::string sensor_battery_topic_;
            std::string sensor_temperature_topic_;

            std::string navigation_topic_;
            int navigation_rate_;
            std::string navigation_velocity_topic_;
            std::string navigation_slam_pose_topic_;
            std::string navigation_plan_topic_;

        public:
            explicit Parameter() = default;
            virtual ~Parameter() = default;

        public:
            using SharedPtr = std::shared_ptr<Parameter>;

        };
    }
}

#endif