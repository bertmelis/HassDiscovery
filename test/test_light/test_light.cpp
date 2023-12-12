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
  HassDiscovery::Light device("myuniqueid");
  const char* expectedTopic = "homeassistant/light/myuniqueid/config";
  const char* expectedPayload = R"foo({"~":"basetopic/myuniqueid","name":null,"uniq_id":"myuniqueid","opt":false,"avty":[{"t":"~/$system/status","pl_avail":"online","pl_not_avail":"offline"}],"avty_mode":"latest","dev":{"ids":["myuniqueid"]},"stat_t":"~/state","cmd_t":"~/state/set","pl_on":1,"pl_off":0,"qos":2,"ret":true})foo";

  TEST_ASSERT_TRUE(device.create());
  TEST_ASSERT_EQUAL_STRING (expectedTopic, device.topic());
  TEST_ASSERT_EQUAL_STRING (expectedPayload, device.payload());
}

void test_rgblight() {
  HassDiscovery::Light device("myuniqueid");
  device.addRGB();
  const char* expectedTopic = "homeassistant/light/myuniqueid/config";
  const char* expectedPayload = R"foo({"rgb_stat_t":"~/rgb","rgb_cmd_t":"~/rgb/set","on_cmd_type":"last","~":"basetopic/myuniqueid","name":null,"uniq_id":"myuniqueid","opt":false,"avty":[{"t":"~/$system/status","pl_avail":"online","pl_not_avail":"offline"}],"avty_mode":"latest","dev":{"ids":["myuniqueid"]},"stat_t":"~/state","cmd_t":"~/state/set","pl_on":1,"pl_off":0,"qos":2,"ret":true})foo";

  TEST_ASSERT_TRUE(device.create());
  TEST_ASSERT_EQUAL_STRING (expectedTopic, device.topic());
  TEST_ASSERT_EQUAL_STRING (expectedPayload, device.payload());
}

void test_effect1light() {
  HassDiscovery::Light device("myuniqueid");
  const char* effects[] = {
    "rainbow",
    "snake",
    "blink"
  };
  device.addEffects(effects, 3);
  const char* expectedTopic = "homeassistant/light/myuniqueid/config";
  const char* expectedPayload = R"foo({"fx_stat_t":"~/effect","fx_cmd_t":"~/effect/set","on_cmd_type":"last","fx_list":["rainbow","snake","blink"],"~":"basetopic/myuniqueid","name":null,"uniq_id":"myuniqueid","opt":false,"avty":[{"t":"~/$system/status","pl_avail":"online","pl_not_avail":"offline"}],"avty_mode":"latest","dev":{"ids":["myuniqueid"]},"stat_t":"~/state","cmd_t":"~/state/set","pl_on":1,"pl_off":0,"qos":2,"ret":true})foo";

  TEST_ASSERT_TRUE(device.create());
  TEST_ASSERT_EQUAL_STRING (expectedTopic, device.topic());
  TEST_ASSERT_EQUAL_STRING (expectedPayload, device.payload());
}

void test_effect2light() {
  HassDiscovery::Light device("myuniqueid");
  device.addEffect("rainbow");
  device.addEffect("snake");
  device.addEffect("blink");
  const char* expectedTopic = "homeassistant/light/myuniqueid/config";
  const char* expectedPayload = R"foo({"fx_stat_t":"~/effect","fx_cmd_t":"~/effect/set","on_cmd_type":"last","fx_list":["rainbow","snake","blink"],"~":"basetopic/myuniqueid","name":null,"uniq_id":"myuniqueid","opt":false,"avty":[{"t":"~/$system/status","pl_avail":"online","pl_not_avail":"offline"}],"avty_mode":"latest","dev":{"ids":["myuniqueid"]},"stat_t":"~/state","cmd_t":"~/state/set","pl_on":1,"pl_off":0,"qos":2,"ret":true})foo";

  TEST_ASSERT_TRUE(device.create());
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