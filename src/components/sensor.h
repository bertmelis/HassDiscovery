/*
Copyright (c) 2023 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#pragma once

#include "device.h"

namespace HassDiscovery {

class Sensor : public Device {
 public:
  explicit Sensor(const char* id);
  bool create(const char* name);

 protected:
  bool _buildPayload(const char* name);
};

}  // end namespace HassDiscovery
