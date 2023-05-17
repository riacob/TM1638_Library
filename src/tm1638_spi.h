/**
 * @file tm1638_spi.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-17
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef TM1638_SPI_H
#define TM1638_SPI_H
#include <Arduino.h>
#include <SPI.h>
#include "tm1638.h"

class TM1638_SPI : public TM1638
{
private:
    uint8_t PIN_CS;
public:
    TM1638_SPI(uint8_t pinCS);
    /**
     * @brief Sends single byte and ignores response.
     *
     * @param b: The byte to be sent.
     */
    void sendByte(uint8_t b);
    /**
     * @brief Sends multiple bytes in one chip select activation.
     *
     * @param b: The byte array to be sent.
     * @param nBytes: The number of bytes in the array.
     */
    void sendBytes(uint8_t *b, uint8_t nBytes);
    /**
     * @brief Turns on the display with the desired duty cycle.
     * @note Values over 14 wil be considered as 14. Zero will be considered 1. Values not listed will be ignored.
     * @note Function called without parameters sets 14/16 as duty cycle.
     *
     * @param dutyCycle: The duty cycle of the display's PWM control. Values: 1,2,4,10,11,12,13,14.
     */
    void displayOn(uint8_t dutyCycle = 16);
    /**
     * @brief Turns off the display.
     */
    void displayOff();
    /**
     * @brief Clears all memory addresses (sets to 0).
     */
    void reset();
    /**
     * @brief Sets the digit to the given char according the internal CharMap[].
     * 
     * @param digitIdx: The digit index, 0-7.
     * @param c: The char to set the digit to.
     */
    void setDigit(uint8_t digitIdx, char c);
    /**
     * @brief Sets all digits according to the char array.
     * @note If the method finds 0 in an array, it gets considered as a string terminator. ONLY in that case not specifying the array size is fine.
     * 
     * @param digitChars: Character array, specifying arrSize, or string, if null-terminated.
     * @param idxOffset: The offset in the array from which to start printing. Useful for scrolling text. Default is null.
     * @param arrSize: The size of the character array. No need to specify this if you're working with a null-terminated string.
     */
    void setDigits(char* digitChars, size_t idxOffset = 0, size_t arrSize = 0);
    /**
     * @brief Sets the dot state of the given digit.
     * 
     * @param digit: The digit index, 0-7.
     * @param dotState: The state of the dot point.
     */
    void setDot(uint8_t digitIdx, bool dotState);
    /**
     * @brief Writes charBuf and dotBuf. Call this when you're done editing the buffers.
     */
    void writeBuf();
};

#endif