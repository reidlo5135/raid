from rclpy import qos, subscription, callback_groups
from rclpy.node import Node
from rclpy.impl.rcutils_logger import RcutilsLogger
from std_msgs.msg import Header
from geometry_msgs.msg import Twist
from nav_msgs.msg import Path
from geometry_msgs.msg import PoseStamped
from raid_msgs.msg import Navigation as NavigationMsg
from rosbridge_library.internal import message_conversion
from raid_csv_server.application.csv import CSV
from typing import Any

CSV_NAME: str = "navigation.csv"
DATA_NAVIGATION_TOPIC: str = "/raid/data/navigation"

class Navigation:

    def __init__(self, node: Node) -> None:
        self.node_: Node = node
        self.logger_: RcutilsLogger = self.node_.get_logger()

        header_columns: Any = ["time", "velocity", "slam_pose", "plan"]
        self.csv_: CSV = CSV()
        self.csv_.header_columns = header_columns

        self.node_.create_subscription(
            topic=DATA_NAVIGATION_TOPIC,
            msg_type=NavigationMsg,
            qos_profile=qos.qos_profile_system_default,
            callback_group=callback_groups.MutuallyExclusiveCallbackGroup(),
            callback=self.navigation_subscription_cb
        )

    def navigation_subscription_cb(self, navigation: NavigationMsg) -> None:
        try:
            time: str = ""
            time_sec_nanosec: tuple[Any, Any] = self.node_.get_clock().now().seconds_nanoseconds()

            header: Header = navigation.header
            if header.stamp.sec == 0:
                time = f"{time_sec_nanosec[0]}.{time_sec_nanosec[1]}"
            else:
                time = f"{header.stamp.sec}.{header.stamp.nanosec}"

            velocity: Twist = navigation.velocity
            velocity_list: list[float] = [velocity.linear.x, velocity.angular.z]

            slam_pose: PoseStamped = navigation.slam_pose
            slam_pose_list: list[float] = []
            slam_pose_list.append(slam_pose.pose.position.x)
            slam_pose_list.append(slam_pose.pose.position.y)
            slam_pose_list.append(slam_pose.pose.position.z)
            slam_pose_list.append(slam_pose.pose.orientation.x)
            slam_pose_list.append(slam_pose.pose.orientation.y)
            slam_pose_list.append(slam_pose.pose.orientation.z)
            slam_pose_list.append(slam_pose.pose.orientation.w)

            plan: Path = navigation.plan
            plan_list: list[float] = []

            if plan.poses.__len__() > 0:
                for pose in plan.poses:
                    plan_list.append(pose.pose.position.x)
                    plan_list.append(pose.pose.position.y)
                    plan_list.append(pose.pose.position.z)
                    plan_list.append(pose.pose.orientation.x)
                    plan_list.append(pose.pose.orientation.y)
                    plan_list.append(pose.pose.orientation.z)
                    plan_list.append(pose.pose.orientation.w)
            else:
                pass

            self.csv_.write(csv_name=CSV_NAME, data=[time, velocity_list, slam_pose_list, plan_list])
        except OSError as ose:
            self.logger_.error(f"{ose}")


__all__: list[str] = ["Navigation"]
