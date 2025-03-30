#ifndef PRESENTATION_NODE_HPP
#define PRESENTATION_NODE_HPP

#include <rclcpp/rclcpp.hpp>

#include "application/svm.hpp"

#define NODE_NAME "raid_ai"

namespace raid
{
    namespace ai
    {
        class AINode final : public rclcpp::Node
        {
        private:
            rclcpp::Node::SharedPtr node_;
            SVMLearner::SharedPtr svm_learner_;

        public:
            explicit AINode();
            virtual ~AINode();
        };
    }
}

#endif