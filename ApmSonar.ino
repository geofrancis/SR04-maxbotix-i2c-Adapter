// sr04 to apm I2c sonar
// by panxu mail: pxzleo@126.com
// Created 2014
#include <Wire.h>
#include "SR04.h"
#define TRIG_PIN 2
#define ECHO_PIN 3
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
uint16_t reading_cm;
uint16_t tempread;
void setup()
{
  reading_cm=0; 
  Wire.begin(0x70);                // join i2c bus with address #2
  Wire.onRequest(requestEvent); // register event
}

void loop()
{
  tempread=sr04.DistanceAvg(25,1);
  if (tempread<1500)  
       reading_cm=tempread;  
}
void requestEvent()
{
  byte sendhi;
  byte sendli;
  byte sendbyte[2];
  uint16_t tempreading_cm;
  tempreading_cm=reading_cm;
  sendhi=tempreading_cm>>8;
  sendli=tempreading_cm&0xff;
  sendbyte[0]=sendhi;
  sendbyte[1]=sendli;
  Wire.write(sendbyte,2); 
}
