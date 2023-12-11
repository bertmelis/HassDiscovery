/*
Copyright (c) 2023 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#pragma once

#include "device.h"

namespace HADiscovery {

class BinarySensor : public Device {
 public:
  explicit BinarySensor(const char* id);
  bool create(const char* name);

 protected:
  bool _buildPayload(const char* name);
};

}  // end namespace HADiscovery
