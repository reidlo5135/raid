#ifndef APPLICATION_NAVIGATION_HPP
#define APPLICATION_NAVIGATION_HPP

#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/path.hpp>
#include <nav_msgs/msg/odometry.hpp>

namespace raid
{
    class Navigation final
    {
    private:
        rclcpp::Node::SharedPtr node_;

        

    public:
        explicit Navigation(const rclcpp::Node::SharedPtr &node = nullptr);
        virtual ~Navigation();

    public:
        using SharedPtr = std::shared_ptr<Navigation>;

    };
}

#endif // APPLICATION_NAVIGATION_HPP
