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

#define SCROLL_DELAY 100

TM1638_SPI tm1638(10);

void setup()
{
  Serial.begin(9600);
  tm1638.displayOn();
  tm1638.reset();
}

void loop()
{

  char str[] = {'1', '2', '3', '4', '5', '6', '7', '8', 0};

  // Left scrolling text
  for (size_t i = 0; i < sizeof(str); i++)
  {
    tm1638.setDigits(str, false, i);
    tm1638.writeBuf();
    delay(SCROLL_DELAY);
  }
  delay(SCROLL_DELAY);
  tm1638.displayOff();
  delay(500);
  tm1638.displayOn();

  // Right scrolling text
  for (size_t j = 0; j < sizeof(str); j++)
  {
    tm1638.setDigits(str, true, j);
    tm1638.writeBuf();
    delay(SCROLL_DELAY);
  }
  delay(SCROLL_DELAY);
  tm1638.displayOff();
  delay(500);
  tm1638.displayOn();
  /*
  for (size_t i = sizeof(str); i == 0; i--)
  {
    tm1638.setDigits(str, true, i);
    tm1638.writeBuf();
    delay(300);
  }
  delay(200);
  tm1638.displayOff();
  delay(500);
  tm1638.displayOn();*/

  // Blinking first dot
  /*tm1638.setDot(0, 1);
  tm1638.writeBuf();
  delay(500);
  tm1638.setDot(0, 0);
  tm1638.writeBuf();*/
  bool keystates[1];
  tm1638.getKeys(keystates);
}