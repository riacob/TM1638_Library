/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-17
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <Arduino.h>
#include "tm1638_spi.h"

TM1638_SPI tm1638(10);

void setup()
{
  Serial.begin(9600);
  tm1638.displayOn();
  tm1638.reset();
}

void loop()
{
  char str[] = {'1','2','3','4',0};
  tm1638.setDigits(str);
  tm1638.writeBuf();
  delay(500);
  tm1638.setDot(0,1);
  tm1638.writeBuf();
  delay(500);
  tm1638.setDot(0,0);
  tm1638.writeBuf();
}