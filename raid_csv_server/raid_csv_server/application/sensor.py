from rclpy import qos, subscription, callback_groups
from rclpy.node import Node
from rclpy.impl.rcutils_logger import RcutilsLogger
from std_msgs.msg import Header
from sensor_msgs.msg import LaserScan
from sensor_msgs.msg import Imu
from sensor_msgs.msg import NavSatFix
from sensor_msgs.msg import BatteryState
from sensor_msgs.msg import Temperature
from raid_msgs.msg import Sensor as SensorMsg
from rosbridge_library.internal import message_conversion
from raid_csv_server.application.csv import CSV
from typing import Any

CSV_NAME: str = "sensor.csv"
DATA_SENSOR_TOPIC: str = "/raid/data/sensor"


class Sensor:

    def __init__(self, node: Node) -> None:
        self.node_: Node = node
        self.logger_: RcutilsLogger = self.node_.get_logger()

        header_columns: Any = ["time", "scan", "imu", "gps", "battery", "temperature"]
        self.csv_: CSV = CSV()
        self.csv_.header_columns = header_columns

        self.node_.create_subscription(
            topic=DATA_SENSOR_TOPIC,
            msg_type=SensorMsg,
            qos_profile=qos.qos_profile_system_default,
            callback_group=callback_groups.MutuallyExclusiveCallbackGroup(),
            callback=self.sensor_subscription_cb
        )

    def sensor_subscription_cb(self, sensor: SensorMsg) -> None:
        try:
            time: str = ""
            time_sec_nanosec: tuple[Any, Any] = self.node_.get_clock().now().seconds_nanoseconds()

            header: Header = sensor.header
            if header.stamp.sec == 0:
                time = f"{time_sec_nanosec[0]}.{time_sec_nanosec[1]}"
            else:
                time = f"{header.stamp.sec}.{header.stamp.nanosec}"



            self.csv_.write(csv_name=CSV_NAME, data=[time])
        except OSError as ose:
            self.logger_.error(f"{ose}")


__all__: list[str] = ["Sensor"]
