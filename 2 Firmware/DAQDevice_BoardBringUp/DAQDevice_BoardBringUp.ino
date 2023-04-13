/**
 * Teensy DAQ V0.1 -- TeensyDAQ_BoardBringUp.ino
 * 
 * Firmware for board bringup of the Teensy DAQ prototype.
 *    
 * Author: Jasper Yun
 */

#include <Adafruit_MCP23008.h>
#include <SPI.h>
#include <string.h>
#include <stdio.h>

#include "src/ADCmcp33151.hpp"
#include "src/AnalogInputs.hpp"
#include "src/AnalogMux.hpp"
#include "src/bringup_testing.hpp"
#include "src/BSP.hpp"
#include "src/pinDefs.h"
#include "src/RelayDrivers.hpp"

// TODO: add NativeEthernet and experiment with it

#define BRINGUP_TESTING   1

#define TIMER_PERIOD_US   100        // timer period in microseconds
IntervalTimer myTimer;

// global variables
AnalogInputs ains;
Adafruit_MCP23008 mcp_dio;

// private function prototypes
void buttonISR();

void setup() {
  SPI.begin(); // must call this first! todo: rewrite readChannel into read vs set channel
//  Serial.begin(9600);
  bringup_testing::init();
  ains.init();
  
//  while (!Serial); // do not start program until serial terminal is opened

  #if BRINGUP_TESTING
  
  bringup_testing::blinky_onboardLED(500, 0);
//  bringup_testing::blinky_FIOs(250, 0);
//  bringup_testing::blinky_DIOs(250, 0);
//  bringup_testing::relays_all_toggle(500);

//  bringup_testing::ain_LS_SE_cycle_through(250, 5, gain_1);
//  bringup_testing::ain_HS_SE_cycle_through(250, 10, gain_1);

  ains.hs_se_ain_setGain(gain_1);
  ains.hs_se_ain_readChannel(1);

  ains.hs_de_ain_setGain(gain_100);
  ains.hs_de_ain_readChannel(1);

  while (1);

  while (1) {
    float voltage = ains.ls_se_ain_readChannel(1);
    Serial.println(voltage);
    delay(500);
  }
//  bringup_testing::ain_HS_DE_cycle_through(250, 25, gain_1);
  #endif

  // application logic
  Serial.println("Starting DAQ Device initialization...");
  BSP::initPins();
  ains.init();
  RelayDrivers::init(); // all relays are unpowered after init

  // set FIO pinModes and default states here


  // set DIO pinModes and default states here
  mcp_dio.begin(IO_EXPANSION_4_I2C_ADDR);


  // todo: setup Ethernet (eventually)
  
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
