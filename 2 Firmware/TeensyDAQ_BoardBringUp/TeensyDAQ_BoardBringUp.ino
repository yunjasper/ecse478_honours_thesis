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
#include "BSP.h"

#define TIMER_PERIOD_US   100        // timer period in microseconds


IntervalTimer myTimer;

// private function prototypes
void buttonISR();

void setup() {

  for (int i = 0; i < ARRAY_SIZE; i++) {
    adc_values[i] = 0;
  }
  
  analogReadResolution(12);
  BSP_init();
  
//  while (!Serial);
  Serial.print("Initializing..");
  delay(50);
  Serial.println("done");

//  attachInterrupt(digitalPinToInterrupt(FIO_1_PIN), buttonISR, FALLING);
  Serial.println("Attached interrupt");
  
  SPI.begin();
  Serial.println("Finished setup");

  channelNo = 0;
  setLSAINMuxChannel(channelNo);
  setHSAINMuxChannel(channelNo);
  setLSGainMux(1);  // unity gain
  setHSGainMux(100);

//  myTimer.begin(spiread16_callback, TIMER_PERIOD_US);

}


void loop() {
  char buf[100];
  uint8_t gains[] = {1, 10, 50, 100};
  setLSGainMux(1);  // unity gain
//  setHSGainMux(10);
  
  
//  for (uint32_t j = 0; j < 4; j++) {
//    setHSGainMux(gains[j]);
//    delay(1);
//    Serial.print("Gain set to ");
//    Serial.println(gains[j]);
//
//    float measurements[100] = {0};
//    float avg = 0;
//    for (uint32_t i = 0; i < 100; i++) {
//      // read 
//      uint16_t raw = spiread16(CS_HS_ADC);
//      float vadc = ((float) (raw * VOLTAGE_REFERENCE) / (1 << ADC_RESOLUTION));
//      
//      sprintf(buf, "Channel = %d\tVadc = %.10f\r\n", channelNo, vadc);
//      Serial.print(buf);
////      avg += vadc;
//      delay(100);  
//    }
//  
//    avg /= 100;
//    sprintf(buf, "Averaged 100 samples, Vavg = %.10f\r\n", avg);
//    Serial.print(buf);
//    digitalWrite(DEBUG_LED3, !(digitalRead(DEBUG_LED3)));
//    delay(1000);
//  }

//  if (isReadyToPrint) {
//    isReadyToPrint = 0;
//    char buf[1000];
//    sprintf(buf, "%d,%.7f\r\n%d,%.7f\r\n%d,%.7f\r\n%d,%.7f\r\n%d,%.7f\r\n%d,%.7f\r\n%d,%.7f\r\n%d,%.7f\r\n%d,%.7f\r\n%d,%.7f\r\n",
//            0, adc_values[0],
//            0, adc_values[1],
//            0, adc_values[2],
//            0, adc_values[3],
//            0, adc_values[4],
//            0, adc_values[5],
//            0, adc_values[6],
//            0, adc_values[7],
//            0, adc_values[8],
//            0, adc_values[9]);
//    Serial.print(buf);
//    Serial.send_now();
//    
//  }

 
//  uint8_t pins[] = {
//    FIO_1_PIN,
//    FIO_2_PIN,
//    FIO_3_PIN,
//    FIO_4_PIN,
//    FIO_5_PIN,
//    FIO_6_PIN,
//    FIO_7_PIN,
//    FIO_8_PIN,
//    FIO_9_PIN,
//    FIO_10_PIN,
//  };
//
//  for (int i = 0; i < 10; i++) {
//    digitalWrite(pins[i], !digitalRead(pins[i]));
//    delay(100);
//    float temperature = readBoardTemperature();
//    Serial.print("Temperature = ");
//    Serial.println(temperature);
//    
//  }

}


void buttonISR() {
  uint8_t gains[] = {1, 10, 50, 100};
  channelNo += 1;
  if (channelNo > 3) {
    channelNo = 0;
  }
  Serial.print("Changed DE channel to ");
  Serial.println(channelNo);
//  setLSGainMux(gains[channelNo]);
//  setLSAINMuxChannel(channelNo);
//  setHSAINMuxChannel(channelNo);
  setHSGainMux(gains[channelNo]);
}
