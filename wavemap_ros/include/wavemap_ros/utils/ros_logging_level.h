#ifndef WAVEMAP_ROS_UTILS_ROS_LOGGING_LEVEL_H_
#define WAVEMAP_ROS_UTILS_ROS_LOGGING_LEVEL_H_

#include <string>

// #include <ros/console.h>
#include <wavemap/core/config/type_selector.h>
#include <wavemap/core/utils/logging_level.h>

#include <rclcpp/logging.hpp>

namespace wavemap {
struct RosLoggingLevel : public TypeSelector<RosLoggingLevel> {
  using TypeSelector<RosLoggingLevel>::TypeSelector;

  enum Id : TypeId { kDebug, kInfo, kWarning, kError, kFatal };

  static constexpr std::array names = {"debug", "info", "warning", "error",
                                       "fatal"};
  static constexpr std::array ros_levels = {
      rclcpp::Logger::Level::Debug, rclcpp::Logger::Level::Info,
      rclcpp::Logger::Level::Warn, rclcpp::Logger::Level::Error,
      rclcpp::Logger::Level::Fatal};

  // Conversion to general LoggingLevel (from the C++ Library)
  operator LoggingLevel() const;  // NOLINT

  // Apply the logger level to a given output
  void applyToGlog() const;
  bool applyToRosConsole(const std::string& name = "rclcpp")
      const;  // TODO: Check this. Ros1 version was ROSCONSOLE_DEFAULT_NAME
};
}  // namespace wavemap

#endif  // WAVEMAP_ROS_UTILS_ROS_LOGGING_LEVEL_H_
