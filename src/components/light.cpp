/*
Copyright (c) 2023 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#include "light.h"

namespace HassDiscovery {

Light::Light(const char* id)
: Device(id) {
  // empty
}

void Light::addRGB() {
  _json[HADISCOVERY_RGB_STATE_TOPIC] = "~/rgb";
  _json[HADISCOVERY_RGB_COMMAND_TOPIC] = "~/rgb/set";
  _json[HADISCOVERY_ON_COMMAND_TYPE] = "last";  // last: style first, state last; first: state first, style last
}

void Light::addEffect(const char* effect) {
  _prepareEffects();
  if (!_json[HADISCOVERY_EFFECT_LIST]) {
    JsonArray effects = _json.createNestedArray(HADISCOVERY_EFFECT_LIST);
    effects.add(effect);
  } else {
    _json[HADISCOVERY_EFFECT_LIST].add(effect);
  }
}

void Light::addEffects(const char** effectList, size_t nrEffects) {
  _prepareEffects();
  JsonArray effects = _json.createNestedArray(HADISCOVERY_EFFECT_LIST);
  for (size_t i = 0; i < nrEffects; ++i) {
    effects.add(effectList[i]);
  }
}

bool Light::create() {
  if (!_buildTopic("light/") ||
      !_buildBasicPayload() ||
      !_buildPayload() ||
      !_serializePayload()) {
    return false;
  }
  return true;
}

bool Light::_buildPayload() {
  _json[HADISCOVERY_STATE_TOPIC] = "~/state";
  _json[HADISCOVERY_COMMAND_TOPIC] = "~/state/set";
  _json[HADISCOVERY_PAYLOAD_ON] = 1;
  _json[HADISCOVERY_PAYLOAD_OFF] = 0;
  _json["qos"] = 2;
  _json[HADISCOVERY_RETAIN] = true;
  return true;
}

void Light::_prepareEffects() {
  if (!_json[HADISCOVERY_EFFECT_STATE_TOPIC]) {
    _json[HADISCOVERY_EFFECT_STATE_TOPIC] = "~/effect";
    _json[HADISCOVERY_EFFECT_COMMAND_TOPIC] = "~/effect/set";
    _json[HADISCOVERY_ON_COMMAND_TYPE] = "last";  // last: style first, state last; first: state first, style last
  }
}

}  // end namespace HassDiscovery
