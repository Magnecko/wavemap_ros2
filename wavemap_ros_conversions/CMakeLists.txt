cmake_minimum_required(VERSION 3.8)
project(wavemap_ros_conversions)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(xmlrpcpp REQUIRED)
find_package(wavemap)
find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED)
find_package(tf2_eigen REQUIRED)
find_package(wavemap_msgs REQUIRED)

add_library(${PROJECT_NAME} SHARED
  src/config_conversions.cc
  src/map_msg_conversions.cc
  src/time_conversions.cc
  )
# set_wavemap_target_properties(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  xmlrpcpp
  wavemap
  Eigen3
  Boost
  tf2_eigen
  wavemap_msgs
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
