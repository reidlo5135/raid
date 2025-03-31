cmake_minimum_required(VERSION 3.8)
project(raid_data_controller VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(
        include
        include/${PROJECT_NAME}
)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(raid_msgs REQUIRED)
find_package(raid_common REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(nav2_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

set(SOURCES
        include/domain/parameter.hpp
        src/application/sensor.cpp
        src/application/navigation.cpp
        src/presentation/node.cpp
        src/main.cpp
)

set(DEPENDS
        rclcpp
        raid_msgs
        raid_common
        std_msgs
        sensor_msgs
        nav_msgs
        nav2_msgs
        geometry_msgs
)

set(EXEC_NAME
        raid_data_controller
)

add_executable(${EXEC_NAME}
        ${SOURCES}
)

ament_target_dependencies(${EXEC_NAME}
        ${DEPENDS}
)

target_link_libraries(${EXEC_NAME}
        ${OpenCV_LIBS}
)

install(TARGETS
        ${EXEC_NAME}
        DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
        launch
        DESTINATION share/${PROJECT_NAME}
)
install(DIRECTORY
        config
        DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
