#include "raid_common/message.hpp"

using namespace raid::common;

Message::Message() = default;
Message::~Message() = default;

std_msgs::msg::Header
Message::build_header(const builtin_interfaces::msg::Time &time, const std::string &frame_id)
{
    std_msgs::msg::Header::UniquePtr header = std::make_unique<std_msgs::msg::Header>();
    header->set__stamp(time);
    header->set__frame_id(frame_id);

    return std::move(*header);
}
