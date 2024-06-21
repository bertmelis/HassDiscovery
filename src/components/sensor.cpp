/*
Copyright (c) 2023 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#include "sensor.h"

namespace HassDiscovery {

Sensor::Sensor(const char* deviceId, const char* deviceName)
: Device(deviceId, deviceName)
, _isSystem(false) {
  // empty
}

bool Sensor::create(const char* sensorId, const char* sensorName) {
  if (!_buildTopic("sensor/", sensorId) ||
      !_buildStandardPayload(sensorId, sensorName) ||
      !_buildPayload(sensorId) ||
      !_serializePayload()) {
    return false;
  }
  return true;
}

void Sensor::setSystem() {
  _isSystem = true;
}

bool Sensor::_buildPayload(const char* id) {
  size_t length = strlen(id);
  char* topic = nullptr;
  if (_isSystem) {
    topic = reinterpret_cast<char*>(malloc(2 + length + 1 + 8));
  } else {
    topic = reinterpret_cast<char*>(malloc(2 + length + 1));
  }
  if (!topic) return false;
  size_t index = 0;
  std::memcpy(&topic[index], "~/", 2);
  index += 2;
  if (_isSystem) {
    std::memcpy(&topic[index], "$system/", 8);
    index += 8;
  }
  std::memcpy(&topic[index], id, length);
  topic[index + length] = '\0';
  _json[HADISCOVERY_STATE_TOPIC] = topic;
  free(topic);
  return true;
}

}  // end namespace HassDiscovery
