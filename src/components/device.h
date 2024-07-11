/*
Copyright (c) 2023 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#pragma once

#ifndef HAD_TOPICSIZE
#define HAD_TOPICSIZE 128
#endif

#ifndef HAD_PAYLOADSIZE
#define HAD_PAYLOADSIZE 512
#endif

#ifndef HAD_JSONDOCSIZE
#define HAD_JSONDOCSIZE 1024
#endif

#ifndef HAD_BASETOPIC
#define HAD_BASETOPIC "basetopic/"
#endif

#ifndef HAD_DISCOVERYTOPIC
#define HAD_DISCOVERYTOPIC "homeassistant/"
#endif

#include <cstring>
#include <ArduinoJson.h>

#include "HassDAbbreviations.h"

namespace HassDiscovery {

constexpr size_t had_topicSize = HAD_TOPICSIZE;
constexpr size_t had_payloadSize = HAD_PAYLOADSIZE;
constexpr const char* had_baseTopic = HAD_BASETOPIC;
constexpr const char* had_discoveryTopicPrefix = HAD_DISCOVERYTOPIC;

class Device {
 public:
  Device(const char* deviceId, const char* deviceName);
  ~Device();
  Device (const Device&) = delete;
  Device& operator= (const Device&) = delete;

  const char* topic() const;
  const char* payload() const;
  JsonDocument& json();

 protected:
  char* _topic;
  size_t _topicSize;
  char* _payload;
  size_t _payloadSize;
  const char* _deviceId;
  const char* _deviceName;
  JsonDocument _json;

  bool _buildTopic(const char* componentType, const char* id);
  bool _buildStandardPayload(const char* id, const char* name);
  bool _serializePayload();
};

}  // end namespace HassDiscovery
