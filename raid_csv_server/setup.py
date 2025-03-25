import os
from setuptools import find_packages, setup
from glob import glob

package_name: str = "raid_csv_server"

setup(
    name=package_name,
    version="0.0.1",
    packages=find_packages(include=[package_name, f"{package_name}.*"], exclude=["test"]),
    data_files=[
        ("share/ament_index/resource_index/packages", ["resource/" + package_name]),
        ("share/" + package_name, ["package.xml"]),
        (os.path.join("share", package_name, "config"), glob("config/*.yaml")),
        (os.path.join("share", package_name, "resource"), glob("resource/*")),
        (os.path.join("share", package_name), glob("launch/*launch.[pxy][yma]*"))
    ],
    install_requires=["setuptools"],
    zip_safe=True,
    maintainer="reidlo",
    maintainer_email="201840103@email.daelim.ac.kr",
    description="TODO: Package description",
    license="TODO: License declaration",
    tests_require=["pytest"],
    entry_points={
        "console_scripts": [
            f"{package_name} = {package_name}.main:main"
        ],
    },
)
