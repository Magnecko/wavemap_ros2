#include "wavemap_ros/ros_server.hpp"

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);

//   rclcpp::spin(std::make_shared<MinimalPublisher>());

    auto node = std::make_shared<rclcpp::Node>("wavemap_ros_server");
    auto nh_private = std::make_shared<rclcpp::Node>("~");

    wavemap::RosServer wavemap_server(node, nh_private);

  rclcpp::shutdown();
  return 0;
}