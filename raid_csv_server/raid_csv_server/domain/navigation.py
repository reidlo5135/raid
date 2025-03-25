from nav_msgs.msg import Path

class Navigation:
    path_: Path

    def __init__(self) -> None:
        pass

    @property
    def path(self) -> Path:
        return self.path_

    @path.setter
    def path(self, path: Path) -> None:
        self.path_ = path


__all__: list[str] = ["Navigation"]
