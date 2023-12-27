/*
Copyright (c) 2023 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#pragma once

#include "device.h"

namespace HassDiscovery {

class Light : public Device {
 public:
  explicit Light(const char* deviceId, const char* deviceName = nullptr);
  ~Light();
  void addRGB();
  void addEffect(const char* effect);
  void addEffects(const char** effectList, size_t nrEffects);
  bool create(const char* lightId, const char* lightName = nullptr);

 protected:
  bool _buildPayload(const char* id);
  bool _addRGB(const char* id);
  bool _addEffects(const char* id);
  bool _generateTopic(const char* id, const char* suffix);

  char* _topicBuffer;
  bool _rgb;
  bool _effects;
};

}  // end namespace HassDiscovery
