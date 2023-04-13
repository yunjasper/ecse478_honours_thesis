#include <SPI.h>
#include <string.h>
#include <stdio.h>

#define CS1   9
#define CS2   10

#define VOLTAGE_REFERENCE 5.25
#define ADC_RESOLUTION    14

#define TIMER_PERIOD_US   1.5    // timer period in microseconds

#define ARRAY_SIZE  10
volatile unsigned long time_buffer[ARRAY_SIZE];
volatile float adc_values[ARRAY_SIZE];
volatile uint8_t arr_position = 0;
volatile uint8_t isReadyToPrint = 0;

IntervalTimer myTimer;

// pfp
uint16_t spiread16_1();

void setup() {
  
  for (int i = 0; i < ARRAY_SIZE; i++) {
    adc_values[i] = 0;
  }
  
  while (!Serial);
  Serial.print("Initializing..");
  delay(500);
  Serial.println("done");

  pinMode(CS1, OUTPUT);
  pinMode(CS2, OUTPUT);

  digitalWrite(CS1, HIGH);
  digitalWrite(CS2, HIGH);

  SPI.begin();

  myTimer.begin(spiread16_1, TIMER_PERIOD_US);

}


void loop() {

//  for (uint8_t count = 0; count < 5; count++) {
//    
//    float buffer[10] = {0};
//    unsigned long time_buffer[10];
//    uint16_t raw_buffer[10];
//    for (uint8_t i = 0; i < 10; i++) {
//      uint16_t adc_raw = spiread16(CS1);
//      raw_buffer[i] = adc_raw;
//  
//      adc_raw >>= 2;
//      float adc_v = (float) (((float) adc_raw) * VOLTAGE_REFERENCE / (1 << ADC_RESOLUTION));
//      
//      buffer[i] = adc_v;
//      time_buffer[i] = millis();
//    }
//  //  uint16_t adc_raw = spiread16(CS1);
//  //  float adc_v = (float) (((float) adc_raw) * VOLTAGE_REFERENCE / (1 << ADC_RESOLUTION));
//  
//    char buf[1000];
//  //  sprintf(buf, "ADC raw = %d\tADC voltage = %.7f\r\n", adc_raw, adc_v);
//  //  Serial.print(buf);
//  //  Serial.print(millis());
//  //  Serial.print(",");
//  //  Serial.println(adc_v);
//  //  delay(1);
//  
//    sprintf(buf, "%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n",
//            time_buffer[0],raw_buffer[0], buffer[0],
//            time_buffer[1],raw_buffer[1], buffer[1],
//            time_buffer[2],raw_buffer[2], buffer[2],
//            time_buffer[3],raw_buffer[3], buffer[3],
//            time_buffer[4],raw_buffer[4], buffer[4],
//            time_buffer[5],raw_buffer[5], buffer[5],
//            time_buffer[6],raw_buffer[6], buffer[6],
//            time_buffer[7],raw_buffer[7], buffer[7],
//            time_buffer[8],raw_buffer[8], buffer[8],
//            time_buffer[9],raw_buffer[9], buffer[9]);
//    Serial.print(buf);
//  }
////  while(1);

  if (isReadyToPrint) {
    isReadyToPrint = 0;
    char buf[1000];
    sprintf(buf, "%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n%lu,%d,%.7f\r\n",
            time_buffer[0],0, adc_values[0],
            time_buffer[1],0, adc_values[1],
            time_buffer[2],0, adc_values[2],
            time_buffer[3],0, adc_values[3],
            time_buffer[4],0, adc_values[4],
            time_buffer[5],0, adc_values[5],
            time_buffer[6],0, adc_values[6],
            time_buffer[7],0, adc_values[7],
            time_buffer[8],0, adc_values[8],
            time_buffer[9],0, adc_values[9]);
    Serial.print(buf);
    Serial.send_now();
    
  }

}

uint16_t spiread16(uint8_t cs) {
  
  uint8_t buf[2] = {0};
  digitalWrite(cs, LOW);
  SPI.endTransaction();
  SPI.beginTransaction(SPISettings(6000000, MSBFIRST, SPI_MODE0));
  for (uint8_t i = 0; i < 2; i++) {
    buf[i] = SPI.transfer(0);
  }
  digitalWrite(cs, HIGH);
  SPI.endTransaction();

  uint16_t res = buf[0];
  res <<= 8;
  res |= buf[1];
//  res >>= 2;

  return res;
  
}


uint16_t spiread16_1() {
  uint8_t cs = CS1;
  noInterrupts();
  
  uint8_t buf[2] = {0};
  digitalWrite(cs, LOW);
  SPI.endTransaction();
  SPI.beginTransaction(SPISettings(60000000, MSBFIRST, SPI_MODE0));
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
