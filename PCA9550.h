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

#include "Energia.h"
#include <DWire.h>

#define REG_INPUT		0
#define REG_PSC0		1
#define REG_PWM0		2
#define REG_PSC1		3
#define REG_PWM1		4
#define REG_LS0			5

class PCA9550
{
protected:
    DWire &wire;
    unsigned char address;
    
    unsigned short readRegister(unsigned char);
    void writeRegister(unsigned char, unsigned char); 

public:
    PCA9550(DWire&, unsigned char);
    virtual ~PCA9550() {};
    
    void setPeriod(unsigned char, float);
    float getPeriod(unsigned char);
    void setDC(unsigned char, unsigned char);
    unsigned char getDC(unsigned char);
    void setLED(unsigned char, unsigned char);
    unsigned char getInput(unsigned char);
    void blinkLED(unsigned char, unsigned char);

private:
  
};

#endif // __PCA9550_H__ 