/*
Copyright (c) 2023 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#include "binarysensor.h"

namespace HassDiscovery {

BinarySensor::BinarySensor(const char* deviceId, const char* deviceName)
: Device(deviceId, deviceName) {
  // empty
}

bool BinarySensor::create(const char* sensorId, const char* sensorName) {
  if (!_buildTopic("binary_sensor/", sensorId) ||
      !_buildStandardPayload(sensorId, sensorName) ||
      !_buildPayload(sensorId) ||
      !_serializePayload()) {
    return false;
  }
  return true;
}

bool BinarySensor::_buildPayload(const char* id) {
  size_t length = strlen(id);
  char* topic = reinterpret_cast<char*>(malloc(2 + length + 1));
  if (!topic) return false;
  std::memcpy(&topic[0], "~/", 2);
  std::memcpy(&topic[2], id, length);
  topic[2 + length] = '\0';
  _json[HADISCOVERY_STATE_TOPIC] = topic;
  free(topic);
  _json[HADISCOVERY_PAYLOAD_ON] = "on";
  _json[HADISCOVERY_PAYLOAD_OFF] = "off";
  return true;
}

}  // end namespace HassDiscovery
