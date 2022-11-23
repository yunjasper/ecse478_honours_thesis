/**
 * Teensy DAQ V0.1 -- TeensyDAQ_BoardBringUp.ino
 * 
 * Firmware for board bringup of the Teensy DAQ prototype.
 * 
 * Acronyms
 *    LS    Low speed
 *    HS    High speed
 *    AIN   Analog input
 *    
 * Author: Jasper Yun
 */

#include <SPI.h>
#include <string.h>
#include <stdio.h>

// ADC chip select pins
#define CS_LS_ADC   9
#define CS_HS_ADC   10

// ADC parameters
#define VOLTAGE_REFERENCE 4.980     // Volts
#define ADC_RESOLUTION    14        // bits
#define ADC_SPI_FREQ      50000000  // Hz

// mux pins
#define MUX_HS_AIN_A0     2
#define MUX_HS_AIN_A1     3
#define MUX_HS_GAIN_A0    5
#define MUX_HS_GAIN_A1    4
#define MUX_LS_SELECT_A0  14        // chooses between the two muxes for LS AIN
#define MUX_LS_SELECT_A1  38
#define MUX_LS_AIN_1_A0   35        // LS AIN 1 to 8
#define MUX_LS_AIN_1_A1   36
#define MUX_LS_AIN_1_A2   37
#define MUX_LS_AIN_2_A0   39        // LS AIN 9 to 16
#define MUX_LS_AIN_2_A1   40
#define MUX_LS_AIN_2_A2   41
#define MUX_LS_GAIN_A0    34
#define MUX_LS_GAIN_A1    33

// FIO pins (connected directly to Teensy)
#define FIO_1_PIN         0
#define FIO_2_PIN         1
#define FIO_3_PIN         24
#define FIO_4_PIN         25
#define FIO_5_PIN         26
#define FIO_6_PIN         27
#define FIO_7_PIN         28
#define FIO_8_PIN         29
#define FIO_9_PIN         30
#define FIO_10_PIN        31

#define DEBUG_LED3        32


#define TIMER_PERIOD_US   15000        // timer period in microseconds

#define ARRAY_SIZE  10
volatile unsigned long time_buffer[ARRAY_SIZE];
volatile float adc_values[ARRAY_SIZE];
volatile uint8_t arr_position = 0;
volatile uint8_t isReadyToPrint = 0;


IntervalTimer myTimer;

// private function prototypes
uint16_t spiread16_1();
void buttonISR();
volatile uint8_t channelNo = 0;

void setup() {

  for (int i = 0; i < ARRAY_SIZE; i++) {
    adc_values[i] = 0;
  }
  
  while (!Serial);
  Serial.print("Initializing..");
  delay(50);
  Serial.println("done");

  pinMode(CS_HS_ADC, OUTPUT);
  pinMode(CS_LS_ADC, OUTPUT);
  pinMode(FIO_1_PIN, INPUT);
  pinMode(MUX_HS_AIN_A0, OUTPUT);
  pinMode(MUX_HS_AIN_A1, OUTPUT);
  pinMode(MUX_HS_GAIN_A0, OUTPUT);
  pinMode(MUX_HS_GAIN_A1, OUTPUT);
  pinMode(MUX_LS_SELECT_A0, OUTPUT);
  pinMode(MUX_LS_SELECT_A1, OUTPUT);
  pinMode(MUX_LS_AIN_1_A0, OUTPUT);
  pinMode(MUX_LS_AIN_1_A1, OUTPUT);
  pinMode(MUX_LS_AIN_1_A2, OUTPUT);
  pinMode(MUX_LS_AIN_2_A0, OUTPUT);
  pinMode(MUX_LS_AIN_2_A1, OUTPUT);
  pinMode(MUX_LS_AIN_2_A2, OUTPUT);
  pinMode(MUX_LS_GAIN_A0, OUTPUT);
  pinMode(MUX_LS_GAIN_A1, OUTPUT);

//  attachInterrupt(digitalPinToInterrupt(FIO_1_PIN), buttonISR, FALLING);
  Serial.println("Attached interrupt");
  
  digitalWrite(CS_HS_ADC, HIGH);
  digitalWrite(CS_LS_ADC, HIGH);
  digitalWrite(MUX_HS_AIN_A0, LOW);
  digitalWrite(MUX_HS_AIN_A1, LOW);
  digitalWrite(MUX_HS_GAIN_A0, LOW);
  digitalWrite(MUX_HS_GAIN_A1, LOW);
  digitalWrite(MUX_LS_SELECT_A0, LOW);
  digitalWrite(MUX_LS_SELECT_A1, LOW);
  digitalWrite(MUX_LS_AIN_1_A0, LOW);
  digitalWrite(MUX_LS_AIN_1_A1, LOW);
  digitalWrite(MUX_LS_AIN_1_A2, LOW);
  digitalWrite(MUX_LS_AIN_2_A0, LOW);
  digitalWrite(MUX_LS_AIN_2_A1, LOW);
  digitalWrite(MUX_LS_AIN_2_A2, LOW);
  digitalWrite(MUX_LS_GAIN_A0, LOW);
  digitalWrite(MUX_LS_GAIN_A1, LOW);

  SPI.begin();
  Serial.println("Finished setup");
//  myTimer.begin(spiread16_1, TIMER_PERIOD_US);

  channelNo = 0;

}

void loop() {

  // read 
  uint16_t raw = spiread16(CS_LS_ADC);
  float vadc = ((float) (raw * VOLTAGE_REFERENCE) / (1 << ADC_RESOLUTION));
  char buf[100];
  sprintf(buf, "Channel = %d\tVadc = %.5f\r\n", channelNo, vadc);
  Serial.print(buf);
//  setLSAINMuxChannel(channelNo++);
//  if (channelNo > 15) {
//    channelNo = 0;
//  }
//  Serial.println("Incremented channelNo");
  delay(100);
  
//  if (isReadyToPrint) {
//    isReadyToPrint = 0;
//    char buf[1000];
//    sprintf(buf, "%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n",
//            time_buffer[0],0, adc_values[0],
//            time_buffer[1],0, adc_values[1],
//            time_buffer[2],0, adc_values[2],
//            time_buffer[3],0, adc_values[3],
//            time_buffer[4],0, adc_values[4],
//            time_buffer[5],0, adc_values[5],
//            time_buffer[6],0, adc_values[6],
//            time_buffer[7],0, adc_values[7],
//            time_buffer[8],0, adc_values[8],
//            time_buffer[9],0, adc_values[9]);
//    Serial.print(buf);
//    Serial.send_now();
//    
//  }

}

uint16_t spiread16(uint8_t cs) {
  
  uint8_t buf[2] = {0};
  digitalWrite(cs, LOW);
  SPI.endTransaction();
  SPI.beginTransaction(SPISettings(ADC_SPI_FREQ, MSBFIRST, SPI_MODE0));
  for (uint8_t i = 0; i < 2; i++) {
    buf[i] = SPI.transfer(0);
  }
  digitalWrite(cs, HIGH);
  SPI.endTransaction();

  uint16_t res = buf[0];
  res <<= 8;
  res |= buf[1];
  res >>= 2;

  return res;
  
}


uint16_t spiread16_1() {
  uint8_t cs = CS_HS_ADC;
  noInterrupts();
  
  uint8_t buf[2] = {0};
  digitalWrite(cs, LOW);
  SPI.endTransaction();
  SPI.beginTransaction(SPISettings(ADC_SPI_FREQ, MSBFIRST, SPI_MODE0));
  for (uint8_t i = 0; i < 2; i++) {
    buf[i] = SPI.transfer(0);
  }
  digitalWrite(cs, HIGH);
  SPI.endTransaction();

  uint16_t res = buf[0];
  res <<= 8;
  res |= buf[1];
  res >>= 2;

  adc_values[arr_position] = (float) (res * VOLTAGE_REFERENCE / (1 << ADC_RESOLUTION));
  time_buffer[arr_position++] = millis();
  
  if (arr_position == ARRAY_SIZE) {
    arr_position = 0;
    isReadyToPrint = 1;
  }
  
  interrupts();
  return res;
  
}

// note that channel starts counting from zero!
void setHSAINMuxChannel(uint8_t channel) {
  if (channel < 4) {
    digitalWrite(MUX_HS_AIN_A0, channel % 2);
    digitalWrite(MUX_HS_AIN_A1, channel / 2);  
  }
  else {
    // do nothing, invalid input
    Serial.println("Invalid HS AIN channel requested");
  } 
}

// note that channel starts counting from zero!
void setLSAINMuxChannel(uint8_t channel) {
  if (channel < 8) {
    digitalWrite(MUX_LS_SELECT_A0, 0);
    digitalWrite(MUX_LS_SELECT_A1, 0);

    digitalWrite(MUX_LS_AIN_1_A0, channel % 2);
    digitalWrite(MUX_LS_AIN_1_A1, channel / 2);
    digitalWrite(MUX_LS_AIN_1_A2, channel / 4);  
  }
  else if (channel < 16) {
    digitalWrite(MUX_LS_SELECT_A0, 1);
    digitalWrite(MUX_LS_SELECT_A1, 0);
    
    digitalWrite(MUX_LS_AIN_2_A0, channel % 2);
    digitalWrite(MUX_LS_AIN_2_A1, channel / 2);
    digitalWrite(MUX_LS_AIN_2_A2, channel / 4);  
  }
  else {
    // do nothing, invalid input
    Serial.println("Invalid LS AIN channel requested");
  }
}

void buttonISR() {
  channelNo += 1;
  if (channelNo > 15) {
    channelNo = 0;
  }
  Serial.print("Changed SE channel to ");
  Serial.println(channelNo);
  setHSAINMuxChannel(channelNo);
}
