cmake_minimum_required(VERSION 3.8)
project(wavemap_ros)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
set(THIS_PACKAGE_INCLUDE_DEPENDS
  rclcpp
  rclcpp_components
  wavemap
  wavemap_msgs
  wavemap_ros_conversions
  Eigen3
  Boost
  glog
  tf2
  tf2_ros
  OpenCV
  cv_bridge
  std_srvs
  sensor_msgs
  image_transport
  rosgraph_msgs
  geometry_msgs
  visualization_msgs
)

find_package(ament_cmake REQUIRED)
foreach(THIS_PACKAGE_INCLUDE_DEPEND ${THIS_PACKAGE_INCLUDE_DEPENDS})
  find_package(${THIS_PACKAGE_INCLUDE_DEPEND} REQUIRED)
endforeach()

# Libraries
add_library(${PROJECT_NAME}
  src/inputs/depth_image_topic_input.cc
  src/inputs/pointcloud_topic_input.cc
  src/inputs/ros_input_base.cc
  src/inputs/ros_input_factory.cc
  src/map_operations/crop_map_operation.cc
  src/map_operations/map_ros_operation_factory.cc
  src/map_operations/publish_map_operation.cc
  src/map_operations/publish_pointcloud_operation.cc
  src/utils/pointcloud_undistorter.cc
  src/utils/ros_logging_level.cc
  # src/utils/rosbag_processor.cc
  src/utils/tf_transformer.cc
  src/ros_server.cpp
  )
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
ament_target_dependencies(${PROJECT_NAME}
  ${THIS_PACKAGE_INCLUDE_DEPENDS}
)

# Executables
add_executable(ros_server app/ros_server.cpp)
target_link_libraries(ros_server ${PROJECT_NAME})

# add_executable(rosbag_processor src/rosbag_processor.cpp)
# target_link_libraries(rosbag_processor ${PROJECT_NAME})

# Mark Targets for Installation
install(TARGETS ${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME}
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
