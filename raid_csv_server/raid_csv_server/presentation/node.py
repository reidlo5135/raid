from rclpy.node import Node
from raid_csv_server.application.navigation import Navigation

NODE_NAME: str = "raid_csv_server"

class RaidCsvServer(Node):

    def __init__(self) -> None:
        super().__init__(node_name=NODE_NAME)
        self.get_logger().info(f"[{self.get_name()}] created.")

        Navigation(node=self)

__all__: list[str] = ["RaidCsvServer"]
