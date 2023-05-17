/**
 * @file tm1638_spi.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-17
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "tm1638_spi.h"

TM1638_SPI::TM1638_SPI(uint8_t pinCS)
{
    // Initialize CS pin
    PIN_CS = pinCS;
    pinMode(PIN_CS, OUTPUT);
    digitalWrite(PIN_CS, HIGH);
    SPI.begin();
}

void TM1638_SPI::sendByte(uint8_t b)
{
    SPI.beginTransaction(SPISettings(1000000, LSBFIRST, SPI_MODE0));
    digitalWrite(PIN_CS, LOW);
    SPI.transfer(b);
    digitalWrite(PIN_CS, HIGH);
    SPI.endTransaction();
}

void TM1638_SPI::sendBytes(uint8_t *b, uint8_t nBytes)
{
    SPI.beginTransaction(SPISettings(1000000, LSBFIRST, SPI_MODE0));
    digitalWrite(PIN_CS, LOW);
    for (uint8_t i = 0; i < nBytes; i++)
    {
        SPI.transfer(b[i]);
    }
    digitalWrite(PIN_CS, HIGH);
    SPI.endTransaction();
}

void TM1638_SPI::displayOn(uint8_t dutyCycle)
{
    // Possible values: 1,2,4,10,11,12,13,14
    // Zero as 1, >14 as 14.
    if (dutyCycle > 14)
    {
        dutyCycle = 14;
    }
    switch (dutyCycle)
    {
    case 0:
        sendByte(Commands::CMD_ON_1_16);
        break;
    case 1:
        sendByte(Commands::CMD_ON_1_16);
        break;
    case 2:
        sendByte(Commands::CMD_ON_2_16);
        break;
    case 4:
        sendByte(Commands::CMD_ON_4_16);
        break;
    case 10:
        sendByte(Commands::CMD_ON_10_16);
        break;
    case 11:
        sendByte(Commands::CMD_ON_11_16);
        break;
    case 12:
        sendByte(Commands::CMD_ON_12_16);
        break;
    case 14:
        sendByte(Commands::CMD_ON_14_16);
        break;
    default:
        break;
    }
}

void TM1638_SPI::displayOff()
{
    sendByte(CMD_OFF);
}

void TM1638_SPI::reset()
{
    sendByte(CMD_NORMAL_AUTOADDRESS_WRITE);
    // Send starting address to the beginning of the possible addresses bytes[0]
    // Then send all zeros to clear the memory of the TM1638 bytes[1]-bytes[16]
    uint8_t bytes[17] = {0xc0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    sendBytes(bytes, 17);
}

void TM1638_SPI::setDigit(uint8_t digitIdx, char c)
{
    if (digitIdx > 7)
    {
        return;
    }
    digBuf[digitIdx] = CharMap[c];
}

void TM1638_SPI::setDot(uint8_t digitIdx, bool dotState)
{
    if (digitIdx > 7)
    {
        return;
    }
    // 0b10000000 (will be OR-ed with the char to set the dot)
    if (dotState)
    {
        dotBuf[digitIdx] = 128;
        // 0b00000000 (will be OR-ed with the char to clear the dot)
    }
    else
    {
        dotBuf[digitIdx] = 0;
    }
}

void TM1638_SPI::writeBuf()
{
    sendByte(CMD_NORMAL_AUTOADDRESS_WRITE);
    // Send starting address to the beginning of the possible addresses bytes[0]
    // Then transfer digit buffer data and dot buffer data
    uint8_t bytes[17] = {0xc0, (digBuf[0] | dotBuf[0]), 0, (digBuf[1] | dotBuf[1]), 0, (digBuf[2] | dotBuf[2]), 0, (digBuf[3] | dotBuf[3]), 0, (digBuf[4] | dotBuf[4]), 0, (digBuf[5] | dotBuf[5]), 0, (digBuf[6] | dotBuf[6]), 0, (digBuf[7] | dotBuf[7]), 0};
    sendBytes(bytes, 17);
}

void TM1638_SPI::setDigits(char *digitChars, bool arrInvert, size_t idxOffset, size_t arrSize)
{
    // If arrSize is equal to 0 the buffer should be considered as a string
    // If string find length (find null terminator)
    if (arrSize == 0)
    {
        do
        {
            arrSize++;
        } while (digitChars[arrSize - 1] != 0);
    }
    // If not inverting the array
    if (!arrInvert)
    {
        for (int i = 0; (i < 8) && (i + idxOffset < arrSize); i++)
        {
            // Map the char to the digit's segment states
            digBuf[i] = CharMap[digitChars[i + idxOffset]];
        }
    }
    // If inverting the array
    else
    {
        int j = arrSize;
        for (int i = 0; (i < 8) && (j > 0); i++)
        {
            // Map the char to the digit's segment states
            // Why -2 don't ask but works
            digBuf[i] = CharMap[digitChars[j + idxOffset - 2]];
            j--;
        }
    }
}

void TM1638_SPI::getKeys(bool* keyStates)
{
    //keyStates[0][0];
    //sendByte(CMD_NORMAL_AUTOADDRESS_READ);
    //SPI.beginTransaction(SPISettings(1000000,LSBFIRST,SPI_MODE0));
    digitalWrite(PIN_CS, LOW);
    shiftOut(11,13,LSBFIRST,CMD_NORMAL_AUTOADDRESS_READ);
    // Bits: row1_col3, row1_col2, row1_col1, null, row2_col3, row2_col2, row2_col1, null
    uint8_t row1 = shiftIn(12,13,LSBFIRST);
    // Bits: row3_col3, row3_col2, row3_col1, null, row4_col3, row4_col2, row4_col1, null
    uint8_t row3 = shiftIn(12,13,LSBFIRST);
    // Bits: row5_col3, row5_col2, row5_col1, null, row6_col3, row6_col2, row6_col1, null
    uint8_t row5 = shiftIn(12,13,LSBFIRST);
    // Bits: row7_col3, row7_col2, row7_col1, null, row8_col3, row8_col2, row8_col1, null
    uint8_t row7 = shiftIn(12,13,LSBFIRST);
    digitalWrite(PIN_CS, HIGH);
    //SPI.endTransaction();
    Serial.println(row1, BIN);
    Serial.println(row3, BIN);
    Serial.println(row5, BIN);
    Serial.println(row7, BIN);
}