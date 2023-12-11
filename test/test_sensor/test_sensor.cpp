/*
Copyright (c) 2023 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#include <unity.h>

#include <HADiscovery.h>

void setUp() {}
void tearDown() {}

void test_binarysensor() {
  HADiscovery::BinarySensor device("myuniqueid");
  const char* expectedTopic = "homeassistant/binary_sensor/myuniqueid/config";
  const char* expectedPayload = R"foo({"~":"basetopic/myuniqueid","name":null,"uniq_id":"myuniqueid","opt":false,"avty":[{"t":"~/$system/status","pl_avail":"online","pl_not_avail":"offline"}],"avty_mode":"latest","dev":{"ids":["myuniqueid"]},"stat_t":"~/sensorname","pl_on":1,"pl_off":0})foo";

  TEST_ASSERT_TRUE(device.create("sensorname"));
  TEST_ASSERT_EQUAL_STRING (expectedTopic, device.topic());
  TEST_ASSERT_EQUAL_STRING (expectedPayload, device.payload());
}

void test_sensor() {
  HADiscovery::Sensor device("myuniqueid");
  const char* expectedTopic = "homeassistant/sensor/myuniqueid/config";
  const char* expectedPayload = R"foo({"~":"basetopic/myuniqueid","name":null,"uniq_id":"myuniqueid","opt":false,"avty":[{"t":"~/$system/status","pl_avail":"online","pl_not_avail":"offline"}],"avty_mode":"latest","dev":{"ids":["myuniqueid"]},"stat_t":"~/sensorname"})foo";

  TEST_ASSERT_TRUE(device.create("sensorname"));
  TEST_ASSERT_EQUAL_STRING (expectedTopic, device.topic());
  TEST_ASSERT_EQUAL_STRING (expectedPayload, device.payload());
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_binarysensor);
  RUN_TEST(test_sensor);
  return UNITY_END();
}
