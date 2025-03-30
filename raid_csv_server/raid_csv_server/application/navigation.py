from rclpy import qos, subscription, callback_groups
from rclpy.node import Node
from rclpy.impl.rcutils_logger import RcutilsLogger
from nav_msgs.msg import Path
from geometry_msgs.msg import PoseStamped
from rosbridge_library.internal import message_conversion
from raid_csv_server.domain.navigation import Navigation as Domain
from raid_csv_server.application.csv import CSV
from typing import Any

CSV_NAME: str = "navigation.csv"

class Navigation:

    def __init__(self, node: Node) -> None:
        self.node_: Node = node
        self.logger_: RcutilsLogger = self.node_.get_logger()
        self.domain_: Domain = Domain()

        header_columns: Any = ["time", "path"]
        self.csv_: CSV = CSV()
        self.csv_.header_columns = header_columns

        self.node_.create_subscription(
            topic="/plan",
            msg_type=Path,
            qos_profile=qos.qos_profile_system_default,
            callback_group=callback_groups.MutuallyExclusiveCallbackGroup(),
            callback=self.path_subsription_cb
        )

    def path_subsription_cb(self, path: Path) -> None:
        try:
            time: str = ""
            time_sec_nanosec: tuple[Any, Any] = self.node_.get_clock().now().seconds_nanoseconds()

            if path.header.stamp.sec == 0:
                time = f"{time_sec_nanosec[0]}.{time_sec_nanosec[1]}"
            else:
                time = f"{path.header.stamp.sec}.{path.header.stamp.nanosec}"

            poses: list[float] = []

            if path.poses.__len__() > 0:
                for pose in path.poses:
                    poses.append(pose.pose.position.x)
                    poses.append(pose.pose.position.y)
                    poses.append(pose.pose.position.z)
                    poses.append(pose.pose.orientation.x)
                    poses.append(pose.pose.orientation.y)
                    poses.append(pose.pose.orientation.z)
                    poses.append(pose.pose.orientation.w)
            else:
                pass

            self.csv_.write(csv_name=CSV_NAME, data=[time, poses])
        except OSError as ose:
            self.logger_.error(f"{ose}")


__all__: list[str] = ["Navigation"]
