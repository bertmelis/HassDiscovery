/*
Copyright (c) 2023 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#include "light.h"

namespace HassDiscovery {

Light::Light(const char* deviceId, const char* deviceName)
: Device(deviceId, deviceName)
, _topicBuffer(nullptr)
, _rgb(false)
, _brightness(false)
, _effects(false) {
  // empty
}

Light::~Light() {
  free(_topicBuffer);
}

void Light::addRGB() {
  _rgb = true;
}

void Light::addBrightness() {
  _brightness = true;
}

void Light::addEffect(const char* effect) {
  _effects = true;
  if (!_json[HADISCOVERY_EFFECT_LIST]) {
    JsonArray effects = _json[HADISCOVERY_EFFECT_LIST].to<JsonArray>();
    effects.add(effect);
  } else {
    _json[HADISCOVERY_EFFECT_LIST].add(effect);
  }
}

void Light::addEffects(const char** effectList, size_t nrEffects) {
  _effects = true;
  JsonArray effects = _json[HADISCOVERY_EFFECT_LIST].to<JsonArray>();
  for (size_t i = 0; i < nrEffects; ++i) {
    effects.add(effectList[i]);
  }
}

bool Light::create(const char* lightId, const char* lightName) {
  if (!_buildTopic("light/", lightId) ||
      !_buildStandardPayload(lightId, lightName) ||
      !_buildPayload(lightId) ||
      !_serializePayload()) {
    return false;
  }
  return true;
}

bool Light::_buildPayload(const char* id) {
  if (_rgb && !_addRGB(id)) return false;
  if (_brightness && !_addBrightness(id)) return false;
  if (_effects && !_addEffects(id)) return false;
  if (!_generateTopic(id, "/state")) return false;
  _json[HADISCOVERY_STATE_TOPIC] = _topicBuffer;
  if (!_generateTopic(id, "/state/set")) return false;
  _json[HADISCOVERY_COMMAND_TOPIC] = _topicBuffer;
  _json[HADISCOVERY_PAYLOAD_ON] = 1;
  _json[HADISCOVERY_PAYLOAD_OFF] = 0;
  _json["qos"] = 2;
  _json[HADISCOVERY_RETAIN] = true;
  return true;
}

bool Light::_addRGB(const char* id) {
  if (!_generateTopic(id, "/rgb")) return false;
  _json[HADISCOVERY_RGB_STATE_TOPIC] = _topicBuffer;
  if (!_generateTopic(id, "/rgb/set")) return false;
  _json[HADISCOVERY_RGB_COMMAND_TOPIC] = _topicBuffer;
  _json[HADISCOVERY_ON_COMMAND_TYPE] = "last";  // last: style first, state last; first: state first, style last
  return true;
}

bool Light::_addBrightness(const char* id) {
  if (!_generateTopic(id, "/brightness")) return false;
  _json[HADISCOVERY_BRIGHTNESS_STATE_TOPIC] = _topicBuffer;
  if (!_generateTopic(id, "/brightness/set")) return false;
  _json[HADISCOVERY_BRIGHTNESS_COMMAND_TOPIC] = _topicBuffer;
  _json[HADISCOVERY_ON_COMMAND_TYPE] = "last";  // last: style first, state last; first: state first, style last
  return true;
}

bool Light::_addEffects(const char* id) {
  if (!_json[HADISCOVERY_EFFECT_STATE_TOPIC]) {
    if (!_generateTopic(id, "/effect")) return false;
    _json[HADISCOVERY_EFFECT_STATE_TOPIC] = _topicBuffer;
    if (!_generateTopic(id, "/effect/set")) return false;
    _json[HADISCOVERY_EFFECT_COMMAND_TOPIC] = _topicBuffer;
    _json[HADISCOVERY_ON_COMMAND_TYPE] = "last";  // last: style first, state last; first: state first, style last
  }
  return true;
}

bool Light::_generateTopic(const char* id, const char* suffix) {
  // ~/id/suffix for example ~/lightid/rgb/set
  size_t idLength = strlen(id);
  size_t suffixLength = strlen(suffix);
  if (_topicBuffer) free(_topicBuffer);
  _topicBuffer = reinterpret_cast<char*>(malloc(2 + idLength + suffixLength + 1));
  if (!_topicBuffer) return false;
  size_t index = 0;
  std::memcpy(&_topicBuffer[index], "~/", 2);
  index += 2;
  std::memcpy(&_topicBuffer[index], id, idLength);
  index += idLength;
  std::memcpy(&_topicBuffer[index], suffix, suffixLength);
  index += suffixLength;
  _topicBuffer[index] = '\0';
  return true;
}

}  // end namespace HassDiscovery
