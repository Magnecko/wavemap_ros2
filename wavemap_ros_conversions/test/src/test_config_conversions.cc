#include <gtest/gtest.h>
#include <xmlrpcpp/XmlRpcValue.h>
#include "wavemap_ros_conversions/config_conversions.h"

using namespace wavemap::param::convert;

TEST(ConfigConversionsTest, ToParamMap_InvalidTypeReturnsEmptyMap) {
  // Create an XmlRpcValue of type int (not a struct)
  XmlRpc::XmlRpcValue val = 42;
  param::Map result = toParamMap(val);
  EXPECT_TRUE(result.empty());
}

TEST(ConfigConversionsTest, ToParamArray_InvalidTypeReturnsEmptyArray) {
  // Create an XmlRpcValue of type string (not an array)
  XmlRpc::XmlRpcValue val("hello");
  param::Array result = toParamArray(val);
  EXPECT_TRUE(result.empty());
}

TEST(ConfigConversionsTest, ToParamValue_Boolean) {
  XmlRpc::XmlRpcValue val(true);
  param::Value result = toParamValue(val);
  // Assuming that param::Value can be extracted to bool:
  EXPECT_EQ(result.get<bool>(), true);
}

TEST(ConfigConversionsTest, ToParamValue_Int) {
  XmlRpc::XmlRpcValue val(123);
  param::Value result = toParamValue(val);
  EXPECT_EQ(result.get<int>(), 123);
}

TEST(ConfigConversionsTest, ToParamValue_Double) {
  XmlRpc::XmlRpcValue val(3.14);
  param::Value result = toParamValue(val);
  EXPECT_NEAR(result.get<double>(), 3.14, 1e-6);
}

TEST(ConfigConversionsTest, ToParamValue_String) {
  XmlRpc::XmlRpcValue val("test");
  param::Value result = toParamValue(val);
  EXPECT_EQ(result.get<std::string>(), "test");
}

TEST(ConfigConversionsTest, ToParamValue_ArrayConversion) {
  // Create an XmlRpcValue as an array of ints.
  XmlRpc::XmlRpcValue array(XmlRpc::XmlRpcValue::TypeArray);
  array[0] = 1;
  array[1] = 2;
  array[2] = 3;
  
  param::Value result = toParamValue(array);
  // Assume that result holds a param::Array and that we can extract it.
  auto arr = result.get<param::Array>();
  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr[0].get<int>(), 1);
  EXPECT_EQ(arr[1].get<int>(), 2);
  EXPECT_EQ(arr[2].get<int>(), 3);
}

TEST(ConfigConversionsTest, ToParamValue_StructConversion) {
  // Create an XmlRpcValue as a struct.
  XmlRpc::XmlRpcValue str(XmlRpc::XmlRpcValue::TypeStruct);
  str["a"] = 10;
  str["b"] = "hello";
  
  param::Value result = toParamValue(str);
  auto m = result.get<param::Map>();
  EXPECT_EQ(m.size(), 2);
  EXPECT_EQ(m["a"].get<int>(), 10);
  EXPECT_EQ(m["b"].get<std::string>(), "hello");
}

// Base64 unsupported types results in an error log and an empty array:
TEST(ConfigConversionsTest, ToParamValue_UnsupportedBase64ReturnsEmptyArray) {
  XmlRpc::XmlRpcValue val;
  val.setType(XmlRpc::XmlRpcValue::TypeBase64);
  param::Value result = toParamValue(val);
  auto arr = result.get<param::Array>();
  EXPECT_TRUE(arr.empty());
}
