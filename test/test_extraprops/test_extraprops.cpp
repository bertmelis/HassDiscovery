/*
Copyright (c) 2023 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#include <unity.h>

#include <HassDiscovery.h>

void setUp() {}
void tearDown() {}

void test_extraProps() {
  HassDiscovery::BinarySensor device("deviceid", "devicename");
  const char* expectedTopic = "homeassistant/binary_sensor/deviceid_sensorid/config";
  const char* expectedPayload = R"foo({"ic":"mdi:lightbulb","~":"basetopic/deviceid","name":"sensorname","uniq_id":"deviceid_sensorid","opt":false,"avty":[{"t":"~/$system/status","pl_avail":"online","pl_not_avail":"offline"}],"avty_mode":"latest","dev":{"ids":["deviceid"],"name":"devicename"},"stat_t":"~/sensorid","pl_on":"1","pl_off":"0"})foo";

  device.json()[HADISCOVERY_ICON] = "mdi:lightbulb";

  TEST_ASSERT_TRUE(device.create("sensorid", "sensorname"));
  TEST_ASSERT_EQUAL_STRING (expectedTopic, device.topic());
  TEST_ASSERT_EQUAL_STRING (expectedPayload, device.payload());
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_extraProps);
  return UNITY_END();
}
