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

void test_light() {
  HassDiscovery::Light device("deviceid","devicename");
  const char* expectedTopic = "homeassistant/light/deviceid_lightid/config";
  const char* expectedPayload = R"foo({"~":"basetopic/deviceid","name":"lightname","uniq_id":"deviceid_lightid","opt":false,"avty":[{"t":"~/$system/status","pl_avail":"online","pl_not_avail":"offline"}],"avty_mode":"latest","dev":{"ids":["deviceid"],"name":"devicename"},"stat_t":"~/lightid/state","cmd_t":"~/lightid/state/set","pl_on":1,"pl_off":0,"qos":2,"ret":true})foo";

  TEST_ASSERT_TRUE(device.create("lightid", "lightname"));
  TEST_ASSERT_EQUAL_STRING (expectedTopic, device.topic());
  TEST_ASSERT_EQUAL_STRING (expectedPayload, device.payload());
}

void test_rgblight() {
  HassDiscovery::Light device("deviceid","devicename");
  device.addRGB();
  const char* expectedTopic = "homeassistant/light/deviceid_lightid/config";
  const char* expectedPayload = R"foo({"~":"basetopic/deviceid","name":"lightname","uniq_id":"deviceid_lightid","opt":false,"avty":[{"t":"~/$system/status","pl_avail":"online","pl_not_avail":"offline"}],"avty_mode":"latest","dev":{"ids":["deviceid"],"name":"devicename"},"rgb_stat_t":"~/lightid/rgb","rgb_cmd_t":"~/lightid/rgb/set","on_cmd_type":"last","stat_t":"~/lightid/state","cmd_t":"~/lightid/state/set","pl_on":1,"pl_off":0,"qos":2,"ret":true})foo";

  TEST_ASSERT_TRUE(device.create("lightid", "lightname"));
  TEST_ASSERT_EQUAL_STRING (expectedTopic, device.topic());
  TEST_ASSERT_EQUAL_STRING (expectedPayload, device.payload());
}

void test_effect1light() {
  HassDiscovery::Light device("deviceid","devicename");
  const char* effects[] = {
    "rainbow",
    "snake",
    "blink"
  };
  device.addEffects(effects, 3);
  const char* expectedTopic = "homeassistant/light/deviceid_lightid/config";
  const char* expectedPayload = R"foo({"fx_list":["rainbow","snake","blink"],"~":"basetopic/deviceid","name":"lightname","uniq_id":"deviceid_lightid","opt":false,"avty":[{"t":"~/$system/status","pl_avail":"online","pl_not_avail":"offline"}],"avty_mode":"latest","dev":{"ids":["deviceid"],"name":"devicename"},"fx_stat_t":"~/lightid/effect","fx_cmd_t":"~/lightid/effect/set","on_cmd_type":"last","stat_t":"~/lightid/state","cmd_t":"~/lightid/state/set","pl_on":1,"pl_off":0,"qos":2,"ret":true})foo";

  TEST_ASSERT_TRUE(device.create("lightid", "lightname"));
  TEST_ASSERT_EQUAL_STRING (expectedTopic, device.topic());
  TEST_ASSERT_EQUAL_STRING (expectedPayload, device.payload());
}

void test_effect2light() {
  HassDiscovery::Light device("deviceid","devicename");
  device.addEffect("rainbow");
  device.addEffect("snake");
  device.addEffect("blink");
  const char* expectedTopic = "homeassistant/light/deviceid_lightid/config";
  const char* expectedPayload = R"foo({"fx_list":["rainbow","snake","blink"],"~":"basetopic/deviceid","name":"lightname","uniq_id":"deviceid_lightid","opt":false,"avty":[{"t":"~/$system/status","pl_avail":"online","pl_not_avail":"offline"}],"avty_mode":"latest","dev":{"ids":["deviceid"],"name":"devicename"},"fx_stat_t":"~/lightid/effect","fx_cmd_t":"~/lightid/effect/set","on_cmd_type":"last","stat_t":"~/lightid/state","cmd_t":"~/lightid/state/set","pl_on":1,"pl_off":0,"qos":2,"ret":true})foo";

  TEST_ASSERT_TRUE(device.create("lightid", "lightname"));
  TEST_ASSERT_EQUAL_STRING (expectedTopic, device.topic());
  TEST_ASSERT_EQUAL_STRING (expectedPayload, device.payload());
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_light);
  RUN_TEST(test_rgblight);
  RUN_TEST(test_effect1light);
  RUN_TEST(test_effect2light);
  return UNITY_END();
}