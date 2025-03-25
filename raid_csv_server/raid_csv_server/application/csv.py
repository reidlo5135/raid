import os
import pandas as pd
from typing import Any

DIRECTORY: str = "raid_csv_server/resource"

class CSV:

    def __init__(self) -> None:
        self.header_columns_: Any = []

    @property
    def header_columns(self) -> Any:
        return self.header_columns_

    @header_columns.setter
    def header_columns(self, header_columns: Any) -> None:
        self.header_columns_ = header_columns

    def write(self, csv_name: str, data: Any) -> None:
        file_path = f"{DIRECTORY}/{csv_name}"
        file_exists = os.path.exists(file_path)

        data_frame: pd.DataFrame = pd.DataFrame([data], columns=self.header_columns)

        if not file_exists:
            data_frame.to_csv(file_path, mode="w", header=True, index=False)
        else:
            data_frame.to_csv(file_path, mode="a", header=False, index=False)


__all__: list[str] = ["Csv"]
