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
#define HAD_BASETOPIC "homeassistant/"
#endif

#ifndef HAD_DISCOVERYTOPIC
#define HAD_DISCOVERYTOPIC "homeassistant/"
#endif

#include <cstring>
#include <ArduinoJson.h>

#include "HassDAbbreviations.h"

namespace HassDiscovery {

constexpr size_t TOPICSIZE = HAD_TOPICSIZE;
constexpr size_t PAYLOADSIZE = HAD_PAYLOADSIZE;
constexpr const char* BASETOPIC = HAD_BASETOPIC;
constexpr const char* DISCOVERYTOPICPREFIX = HAD_DISCOVERYTOPIC;

class Device {
 public:
  explicit Device(const char* id);
  ~Device();
  Device (const Device&) = delete;
  Device& operator= (const Device&) = delete;

  const char* topic() const;
  const char* payload() const;
  StaticJsonDocument<HAD_JSONDOCSIZE>& json();

 protected:
  char* _topic;
  size_t _topicSize;
  char* _payload;
  size_t _payloadSize;
  const char* _id;
  StaticJsonDocument<HAD_JSONDOCSIZE> _json;

  bool _buildTopic(const char* component);
  bool _buildBasicPayload(const char* name);
  bool _serializePayload();
};

}  // end namespace HassDiscovery
