cmake_minimum_required(VERSION 3.8)
project(raid_common)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(
  include
  include/${PROJECT_NAME}
)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)

set(SOURCES
      src/raid_common/message.cpp
)

set(LIB_NAME raid_common)

set(DEPENDS
      rclcpp
      std_msgs
)

add_library(${LIB_NAME} SHARED
  ${SOURCES}
)

ament_target_dependencies(${LIB_NAME}
  ${DEPENDS}
)

install(TARGETS ${LIB_NAME}
  EXPORT raidCommonTargets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY include/
  DESTINATION include/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(include)
ament_export_libraries(${LIB_NAME})

install(EXPORT raidCommonTargets
  FILE raidCommonTargets.cmake
  NAMESPACE ${LIB_NAME}::
  DESTINATION lib/cmake/${LIB_NAME}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "raidCommonConfigVersion.cmake"
  VERSION 1.0
  COMPATIBILITY AnyNewerVersion
)

configure_file(raidCommonConfig.cmake.in raidCommonConfig.cmake @ONLY)
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/raidCommonConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/raidCommonConfigVersion.cmake"
  DESTINATION lib/cmake/r2ps_utils
)

ament_package()
