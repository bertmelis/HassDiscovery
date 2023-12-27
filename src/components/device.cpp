/*
Copyright (c) 2023 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#include "device.h"

namespace HassDiscovery {

Device::Device(const char* deviceId, const char* deviceName)
: _topic(nullptr)
, _topicSize(0)
, _payload(nullptr)
, _payloadSize(0)
, _deviceId(deviceId)
, _deviceName(deviceName)
, _json() {
  _topic = reinterpret_cast<char*>(malloc(TOPICSIZE));
  if (_topic) {
    _topicSize = TOPICSIZE;
  }
  _payload = reinterpret_cast<char*>(malloc(PAYLOADSIZE));
  if (_payload) {
    _payloadSize = PAYLOADSIZE;
  }
}

Device::~Device() {
  free(_topic);
  free(_payload);
}

const char* Device::topic() const {
  if (_topicSize == 0) return nullptr;
  return _topic;
}

const char* Device::payload() const {
  if (_payloadSize == 0) return nullptr;
  return _payload;
}

StaticJsonDocument<HAD_JSONDOCSIZE>& Device::json() {
  return _json;
}

bool Device::_buildTopic(const char* componentType, const char* id) {
  // topic: <discovery_prefix>/<component>/<object_id>/config
  // object_id = "deviceId_objectId"
  constexpr const char* suffix = "/config";

  // adjust topic buffer
  size_t neededLen = strlen(DISCOVERYTOPICPREFIX) + strlen(componentType) + strlen(_deviceId) + 1 + strlen(id) + strlen(suffix) + 1;
  if (neededLen > _topicSize) {
    _topicSize = neededLen;
    char* newBuffer = _topic;
    if (newBuffer) {
      newBuffer = reinterpret_cast<char*>(realloc(_topic, _topicSize));
    } else {
      newBuffer = reinterpret_cast<char*>(malloc(_topicSize));
    }
    if (!newBuffer) {
      _topicSize = 0;
      return false;
    }
    _topic = newBuffer;
  }

  // build topic string
  size_t index = 0;
  size_t length = strlen(DISCOVERYTOPICPREFIX);
  std::memcpy(&_topic[index], DISCOVERYTOPICPREFIX, length);

  index += length;
  length = strlen(componentType);
  std::memcpy(&_topic[index], componentType, length);

  index += length;
  length = strlen(_deviceId);
  std::memcpy(&_topic[index], _deviceId, length);

  index += length;
  length = 1;
  std::memcpy(&_topic[index], "_", length);

  index += length;
  length = strlen(id);
  std::memcpy(&_topic[index], id, length);

  index += length;
  length = strlen(suffix);
  std::memcpy(&_topic[index], suffix, length);

  _topic[index + length] = '\0';

  return true;
}

bool Device::_buildStandardPayload(const char* id, const char* name) {
  // build base topic
  size_t baseTopicLength = strlen(BASETOPIC);
  size_t deviceIdLength = strlen(_deviceId);
  char* baseTopic = reinterpret_cast<char*>(malloc(baseTopicLength + deviceIdLength + 1));
  if (!baseTopic) return false;
  std::memcpy(&baseTopic[0], BASETOPIC, baseTopicLength);
  std::memcpy(&baseTopic[baseTopicLength], _deviceId, deviceIdLength);
  baseTopic[baseTopicLength + deviceIdLength] = '\0';
  _json[HADISCOVERY_BASETOPIC] = baseTopic;
  free(baseTopic);

  // fill standard properties
  if (name) {
    _json[HADISCOVERY_NAME] = name;
  }

  size_t idLength = strlen(id);
  char* completeId = reinterpret_cast<char*>(malloc(deviceIdLength + 1 + idLength + 1));
  if (!completeId) return false;
  std::memcpy(&completeId[0], _deviceId, deviceIdLength);
  std::memcpy(&completeId[deviceIdLength], "_", 1);
  std::memcpy(&completeId[deviceIdLength + 1], id, idLength);
  completeId[deviceIdLength + 1 + idLength] = '\0';
  _json[HADISCOVERY_UNIQUE_ID] = completeId;
  free(completeId);

  _json[HADISCOVERY_OPTIMISTIC] = false;
  JsonObject availability0  = _json[HADISCOVERY_AVAILABILITY].createNestedObject();
  availability0[HADISCOVERY_TOPIC] = "~/$system/status";
  availability0[HADISCOVERY_PAYLOAD_AVAILABLE] = "online";
  availability0[HADISCOVERY_PAYLOAD_NOT_AVAILABLE] = "offline";
  _json[HADISCOVERY_AVAILABILITY_MODE] = "latest";
  JsonObject device = _json.createNestedObject(HADISCOVERY_DEVICE);
  device[HADISCOVERY_DEVICE_IDENTIFIERS][0] = _deviceId;
  if (_deviceName) {
    device[HADISCOVERY_NAME] = _deviceName;
  }
  return true;
}

bool Device::_serializePayload() {
  // adjust buffer
  size_t neededLen = measureJson(_json) + 1;
  if (neededLen > _payloadSize) {
    _payloadSize = neededLen;
    char* newBuffer = _payload;
    if (newBuffer) {
      newBuffer = reinterpret_cast<char*>(realloc(_payload, _payloadSize));
    } else {
      newBuffer = reinterpret_cast<char*>(malloc(_payloadSize));
    }
    if (!newBuffer) {
      _payloadSize = 0;
      return false;
    }
  }

  // serialize
  serializeJson(_json, _payload, _payloadSize);

  // final check
  if (_json.overflowed()) {
    return false;
  }

  return true;
}

}  // end namespace HassDiscovery
