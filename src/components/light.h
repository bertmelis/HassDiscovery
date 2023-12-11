/*
Copyright (c) 2023 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#pragma once

#include "device.h"

namespace HADiscovery {

class Light : public Device {
 public:
  explicit Light(const char* id);
  void addRGB();
  void addEffect(const char* effect);
  void addEffects(const char** effectList, size_t nrEffects);
  bool create();

 protected:
  bool _buildPayload();
  void _prepareEffects();
};

}  // end namespace HADiscovery
