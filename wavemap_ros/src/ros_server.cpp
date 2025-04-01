#include "wavemap_ros/ros_server.hpp"

#include <memory>
#include <utility>

#include <std_srvs/srv/trigger.hpp>
#include <wavemap/core/map/map_factory.h>
#include <wavemap/io/map/file_conversions.h>
#include <wavemap/pipeline/map_operations/map_operation_factory.h>
#include <wavemap_msgs/srv/file_path.hpp>
// #include <wavemap_ros_conversions/config_conversions.h>

#include "wavemap_ros/inputs/ros_input_factory.h"
#include "wavemap_ros/map_operations/map_ros_operation_factory.h"