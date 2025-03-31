#ifndef PRESENTATION_NODE_HPP
#define PRESENTATION_NODE_HPP

#include <rclcpp/rclcpp.hpp>

#include "domain/parameter.hpp"
#include "application/navigation.hpp"
#include "application/sensor.hpp"

#define NODE_NAME "raid_data_controller"

namespace raid
{
    namespace data
    {
        class DataControllerNode final : public rclcpp::Node
        {
        private:
            rclcpp::Node::SharedPtr node_;
            Parameter::SharedPtr parameter_;
            NavigationService::SharedPtr navigation_service_;
            SensorService::SharedPtr sensor_service_;

        private:
            void declare_parameters();

        public:
            explicit DataControllerNode();
            virtual ~DataControllerNode();

        };
    }
}

#endif