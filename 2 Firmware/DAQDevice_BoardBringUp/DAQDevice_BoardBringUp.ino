/**
 * Teensy DAQ V0.1 -- TeensyDAQ_BoardBringUp.ino
 * 
 * Firmware for board bringup of the Teensy DAQ prototype.
 *    
 * Author: Jasper Yun
 */

#include <SPI.h>
#include <string.h>
#include <stdio.h>
#include "src/ADCmcp33151.hpp"
#include "src/AnalogMux.hpp"
#include "src/bringup_testing.hpp"
#include "src/BSP.hpp"
#include "src/pinDefs.h"
#include "src/RelayDrivers.hpp"

#define TIMER_PERIOD_US   100        // timer period in microseconds
IntervalTimer myTimer;

// private function prototypes
void buttonISR();

void setup() {
  bringup_testing::init();
  SPI.begin();
//  bringup_testing::blinky_onboardLED(250, 0);
//  bringup_testing::blinky_FIOs(250, 0);
//  bringup_testing::blinky_DIOs(250, 0);
//  bringup_testing::relays_all_toggle(500);

  bringup_testing::ain_LS_SE_cycle_through(250, 20);
  
}


void loop() {


}


void buttonISR() {
//  uint8_t gains[] = {1, 10, 50, 100};
//  channelNo += 1;
//  if (channelNo > 3) {
//    channelNo = 0;
//  }
//  Serial.print("Changed DE channel to ");
//  Serial.println(channelNo);
//  setLSGainMux(gains[channelNo]);
//  setLSAINMuxChannel(channelNo);
//  setHSAINMuxChannel(channelNo);
//  setHSGainMux(gains[channelNo]);
}
