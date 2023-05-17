/**
 * @file tm1638.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-17
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef TM1638_H
#define TM1638_H
#include <Arduino.h>

class TM1638
{
public:
    uint8_t digBuf[8] = {0};
    uint8_t dotBuf[8] = {0};
public:
    enum Commands
    {   
        /*Display on, 1/16 duty cycle*/
        CMD_ON_1_16 = 0b10001000,
        /*Display on, 2/16 duty cycle*/
        CMD_ON_2_16 = 0b10001001,
        /*Display on, 4/16 duty cycle*/
        CMD_ON_4_16 = 0b10001010,
        /*Display on, 10/16 duty cycle*/
        CMD_ON_10_16 = 0b10001011,
        /*Display on, 11/16 duty cycle*/
        CMD_ON_11_16 = 0b10001100,
        /*Display on, 12/16 duty cycle*/
        CMD_ON_12_16 = 0b10001101,
        /*Display on, 13/16 duty cycle*/
        CMD_ON_13_16 = 0b10001110,
        /*Display on, 14/16 duty cycle*/
        CMD_ON_14_16 = 0b10001111,
        /*Display off*/
        CMD_OFF = 0b10000000,
        /*Normal mode, automatic address increment, read key data*/
        CMD_NORMAL_AUTOADDRESS_READ = 0b01000010,
        /*Normal mode, fixed address, read key data*/
        CMD_NORMAL_FIXEDADDRESS_READ = 0b01000110,
        /*Test mode, automatic address increment, read key data*/
        CMD_TEST_AUTOADDRESS_READ = 0b01001010,
        /*Test mode, fixed address, read key data*/
        CMD_TEST_FIXEDADDRESS_READ = 0b01001110,
        /*Normal mode, automatic address increment, write display data*/
        CMD_NORMAL_AUTOADDRESS_WRITE = 0b01000000,
        /*Normal mode, fixed address, write display data*/
        CMD_NORMAL_FIXEDADDRESS_WRITE = 0b01000100,
        /*Test mode, automatic address increment, write display data*/
        CMD_TEST_AUTOADDRESS_WRITE = 0b01001000,
        /*Test mode, fixed address, write display data*/
        CMD_TEST_FIXEDADDRESS_WRITE = 0b01001100
    };
    // Index corresponds to char, and contents at index represent the segments
    const uint8_t CharMap[128] = {
        /*OFFSET OF ONE*/
        0,
        /*NULL*/
        0,
        /*SOH*/
        0,
        /*SOT*/
        0,
        /*EOT*/
        0,
        /*ENQ*/
        0,
        /*ACK*/
        0,
        /*BELL*/
        0,
        /*BSP*/
        0,
        /*HOR*/
        0,
        /*LF*/
        0,
        /*VER*/
        0,
        /*FF*/
        0,
        /*CR*/
        0,
        /*SO*/
        0,
        /*SI*/
        0,
        /*DLE*/
        0,
        /*DC1*/
        0,
        /*DC2*/
        0,
        /*DC3*/
        0,
        /*DC4*/
        0,
        /*NACK*/
        0,
        /*SYNC*/
        0,
        /*EOTB*/
        0,
        /*CANC*/
        0,
        /*EOM*/
        0,
        /*SUB*/
        0,
        /*ESC*/
        0,
        /*FSEP*/
        0,
        /*GSEP*/
        0,
        /*RSEP*/
        0,
        /*USEP*/
        0,
        /*SPACE*/
        0,
        /*!*/
        0,
        /*"*/
        0,
        /*#*/
        0,
        /*$*/
        0,
        /*%*/
        0,
        /*&*/
        0,
        /*'*/
        0,
        /*(*/
        0,
        /*)*/
        0,
        /***/
        0,
        /*+*/
        0,
        /*,*/
        0,
        /*-*/
        0,
        /*.*/
        0,
        /*/*/
        0,
        /*0*/
        0x3F,
        /*1*/
        0x06,
        /*2*/
        0x5B,
        /*3*/
        0x4F,
        /*4*/
        0x66,
        /*5*/
        0x6D,
        /*6*/
        0x7D,
        /*7*/
        0x07,
        /*8*/
        0x7F,
        /*9*/
        0x6F,
        /*:*/
        0,
        /*;*/
        0,
        /*<*/
        0,
        /*=*/
        0,
        /*>*/
        0,
        /*?*/
        0,
        /*@*/
        0,
        /*A*/
        0,
        /*B*/
        0,
        /*C*/
        0,
        /*D*/
        0,
        /*E*/
        0,
        /*F*/
        0,
        /*G*/
        0,
        /*H*/
        0,
        /*I*/
        0,
        /*J*/
        0,
        /*K*/
        0,
        /*L*/
        0,
        /*M*/
        0,
        /*N*/
        0,
        /*O*/
        0,
        /*P*/
        0,
        /*Q*/
        0,
        /*R*/
        0,
        /*S*/
        0,
        /*T*/
        0,
        /*U*/
        0,
        /*V*/
        0,
        /*W*/
        0,
        /*X*/
        0,
        /*Y*/
        0,
        /*Z*/
        0,
        /*[*/
        0,
        /*\*/
        0,
        /*]*/
        0,
        /*^*/
        0,
        /*_*/
        0,
        /*weird quote*/
        0,
        /*a*/
        0,
        /*b*/
        0,
        /*c*/
        0,
        /*d*/
        0,
        /*e*/
        0,
        /*f*/
        0,
        /*g*/
        0,
        /*h*/
        0,
        /*i*/
        0,
        /*j*/
        0,
        /*k*/
        0,
        /*l*/
        0,
        /*m*/
        0,
        /*n*/
        0,
        /*o*/
        0,
        /*p*/
        0,
        /*q*/
        0,
        /*r*/
        0,
        /*s*/
        0,
        /*t*/
        0,
        /*u*/
        0,
        /*v*/
        0,
        /*w*/
        0,
        /*x*/
        0,
        /*y*/
        0,
        /*z*/
        0,
        /*{*/
        0,
        /*|*/
        0,
        /*}*/
        0,
        /*~*/
        0,
        /*DEL*/
        0};
};

#endif