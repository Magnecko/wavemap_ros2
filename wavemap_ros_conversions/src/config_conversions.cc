#include "wavemap_ros_conversions/config_conversions.h"

#include <string>

namespace wavemap::param::convert {
param::Map toParamMap(const rclcpp::Node::SharedPtr& node, const std::string& ns) {
  XmlRpc::XmlRpcValue xml_rpc_value;
  if (node->get_parameter(ns, xml_rpc_value)) {
    return toParamMap(xml_rpc_value);
  }

  RCLCPP_WARN_STREAM(node->get_logger(), "Could not load ROS params under namespace "
                  << node->get_namespace());
  return {};
}

param::Array toParamArray(const rclcpp::Node::SharedPtr& node, const std::string& ns) {
  XmlRpc::XmlRpcValue xml_rpc_value;
  if (node->get_parameter(ns, xml_rpc_value)) {
    return toParamArray(xml_rpc_value);
  }

  RCLCPP_WARN_STREAM(node->get_logger(), "Could not load ROS params under namespace "
                  << node->get_namespace());
  return {};
}

param::Value toParamValue(const rclcpp::Node::SharedPtr& node, const std::string& ns) {
  XmlRpc::XmlRpcValue xml_rpc_value;
  if (node->get_parameter(ns, xml_rpc_value)) {
    return toParamValue(xml_rpc_value);
  }

  RCLCPP_WARN_STREAM(node->get_logger(), "Could not load ROS params under namespace "
                  << node->get_namespace());
  return param::Value{param::Map{}};  // Return an empty map
}

param::Map toParamMap(  // NOLINT
    const XmlRpc::XmlRpcValue& xml_rpc_value) {
  if (xml_rpc_value.getType() != XmlRpc::XmlRpcValue::TypeStruct) {
    RCLCPP_WARN(rclcpp::get_logger("wavemap_ros_conversions"), "Expected param map.");
    return {};
  }

  param::Map param_map;
  for (const auto& kv : xml_rpc_value) {
    param_map.emplace(kv.first, toParamValue(kv.second));
  }
  return param_map;
}

param::Array toParamArray(  // NOLINT
    const XmlRpc::XmlRpcValue& xml_rpc_value) {
  if (xml_rpc_value.getType() != XmlRpc::XmlRpcValue::TypeArray) {
    RCLCPP_WARN(rclcpp::get_logger("wavemap_ros_conversions"), "Expected param array.");
    return {};
  }

  param::Array array;
  array.reserve(xml_rpc_value.size());
  for (int idx = 0; idx < xml_rpc_value.size(); ++idx) {  // NOLINT
    array.template emplace_back(toParamValue(xml_rpc_value[idx]));
  }
  return array;
}

param::Value toParamValue(  // NOLINT
    const XmlRpc::XmlRpcValue& xml_rpc_value) {
  switch (xml_rpc_value.getType()) {
    case XmlRpc::XmlRpcValue::TypeBoolean:
      return param::Value(static_cast<bool>(xml_rpc_value));
    case XmlRpc::XmlRpcValue::TypeInt:
      return param::Value(static_cast<int>(xml_rpc_value));
    case XmlRpc::XmlRpcValue::TypeDouble:
      return param::Value(static_cast<double>(xml_rpc_value));
    case XmlRpc::XmlRpcValue::TypeString:
      return param::Value(static_cast<std::string>(xml_rpc_value));
    case XmlRpc::XmlRpcValue::TypeArray:
      return param::Value(toParamArray(xml_rpc_value));
    case XmlRpc::XmlRpcValue::TypeStruct:
      return param::Value(toParamMap(xml_rpc_value));
    case XmlRpc::XmlRpcValue::TypeInvalid:
      RCLCPP_ERROR(rclcpp::get_logger("wavemap_ros_conversions"), 
          "Encountered invalid type while parsing ROS params.");
      break;
    case XmlRpc::XmlRpcValue::TypeDateTime:
      RCLCPP_ERROR(rclcpp::get_logger("wavemap_ros_conversions"), 
          "Encountered a date-time field when parsing ROS params. These "
          "are not yet supported and will be ignored.");
      break;
    case XmlRpc::XmlRpcValue::TypeBase64:
      RCLCPP_ERROR(rclcpp::get_logger("wavemap_ros_conversions"),
          "Encountered a binary data field when parsing ROS paramsThese "
          "are not yet supported and will be ignored.");
      break;
    default:
      RCLCPP_ERROR(rclcpp::get_logger("wavemap_ros_conversions"),
          "Encountered unknown type while parsing ROS params.");
      break;
  }

  // On error, return an empty array
  return param::Value(param::Array{});
}
}  // namespace wavemap::param::convert
