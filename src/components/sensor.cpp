/*
Copyright (c) 2023 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#include "sensor.h"

namespace HassDiscovery {

Sensor::Sensor(const char* deviceId, const char* deviceName)
: Device(deviceId, deviceName) {
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

bool Sensor::_buildPayload(const char* id) {
  size_t length = strlen(id);
  char* topic = reinterpret_cast<char*>(malloc(2 + length + 1));
  if (!topic) return false;
  std::memcpy(&topic[0], "~/", 2);
  std::memcpy(&topic[2], id, length);
  topic[2 + length] = '\0';
  _json[HADISCOVERY_STATE_TOPIC] = topic;
  free(topic);
  return true;
}

}  // end namespace HassDiscovery
