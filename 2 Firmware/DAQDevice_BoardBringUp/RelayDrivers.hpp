/**
 * RelayDrivers.hpp
 * 
 * Author: Jasper Yun
 */

#pragma once
#include <stdint.h>

namespace RelayDrivers {

  // function prototypes
  void init();
  void setRelayActivatedState(uint8_t channel, bool activatedState);
  bool getRelayActivatedState(uint8_t channel);
  
}
