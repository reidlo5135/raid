#ifndef RAID_COMMON_MESSAGE_HPP
#define RAID_COMMON_MESSAGE_HPP

#include <memory>
#include <std_msgs/msg/header.hpp>
#include <builtin_interfaces/msg/time.hpp>

namespace raid
{
    namespace common
    {
        class Message final
        {
        public:
            explicit Message();
            virtual ~Message();
            std_msgs::msg::Header build_header(const builtin_interfaces::msg::Time &time, const std::string &frame_id);

        public:
            using SharedPtr = std::shared_ptr<Message>;
            using UniquePtr = std::unique_ptr<Message>;

        };
    }
}

#endif
