/*
 * Copyright (c) 2016 by Stefano Speretta <s.speretta@tudelft.nl>
 *
 * PCA9550: a library to provide high level APIs to interface with the 
 * NXP PCA9550 LED driver. It is possible to use this library in Energia 
 * (the Arduino port for MSP microcontrollers) or in other toolchains.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License 
 * version 3, both as published by the Free Software Foundation.
 *
 */
 
#ifndef __PCA9550_H__
#define __PCA9550_H__

#include <DWire.h>

#define REG_INPUT		0x00
#define REG_PSC0		0x01
#define REG_PWM0		0x02
#define REG_PSC1		0x03
#define REG_PWM1		0x04
#define REG_LS0			0x05

#define LED1_OFF		0x04
#define LED0_OFF		0x01
#define LED0_BLINK		0x02
#define LED0_ON			0x00
#define LED0_MASK		0x03

class PCA9550
{
public:
    PCA9550(DWire&, unsigned char);
    virtual ~PCA9550() {};
    
    void setPeriod(float);
    float getPeriod();
    void setDC(unsigned char);
    unsigned char getDC();
    void setLED( unsigned char);
    unsigned char getInput();
    void blinkLED();
 
    unsigned char readRegister(unsigned char);
    void writeRegister(unsigned char, unsigned char);
    
private:
    DWire &wire;
    unsigned char address;
};

#endif // __PCA9550_H__ 
