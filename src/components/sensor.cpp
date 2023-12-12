/*
Copyright (c) 2023 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#include "sensor.h"

namespace HassDiscovery {

Sensor::Sensor(const char* id)
: Device(id) {
  // empty
}

bool Sensor::create(const char* name) {
  if (!_buildTopic("sensor/") ||
      !_buildBasicPayload() ||
      !_buildPayload(name) ||
      !_serializePayload()) {
    return false;
  }
  return true;
}

bool Sensor::_buildPayload(const char* name) {
  size_t length = strlen(name);
  char* topic = reinterpret_cast<char*>(malloc(2 + length + 1));
  if (!topic) return false;
  std::memcpy(&topic[0], "~/", 2);
  std::memcpy(&topic[2], name, length);
  topic[2 + length] = '\0';
  _json[HADISCOVERY_STATE_TOPIC] = topic;
  free(topic);
  return true;
}

}  // end namespace HassDiscovery
