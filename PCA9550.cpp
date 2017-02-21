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
 
#include <PCA9550.h>

/**
 *
 *   PCA9550 class creator function
 *   
 *   Parameters:
 *   DWire &i2c             I2C object
 *
 */
PCA9550::PCA9550(DWire &i2c, unsigned char addr): wire(i2c)
{
    address = addr;
}

void PCA9550::setPeriod(float period)
{
    writeRegister(REG_PSC0, (unsigned  int)((period * 44.0) - 1) & 0xFF);
}

float PCA9550::getPeriod()
{
    return ((float)readRegister(REG_PSC0) + 1.0) / 44.0;
}

void PCA9550::setDC(unsigned char dc)
{
    writeRegister(REG_PWM0, 255 - dc);
}

unsigned char PCA9550::getDC()
{
    return 255 - readRegister(REG_PWM0);

}

void PCA9550::setLED(unsigned char status)
{
    if (status)
	{
		writeRegister(REG_LS0, LED1_OFF | LED0_ON);
	}
	else
	{
		writeRegister(REG_LS0, LED1_OFF | LED0_OFF);
	}
}

unsigned char PCA9550::getInput()
{
    return (readRegister(REG_INPUT) & LED0_MASK) == LED0_ON;
}

void PCA9550::blinkLED()
{
    writeRegister(REG_LS0, LED1_OFF | LED0_BLINK);
}

/**
 *
 *   Returns the value of the selected internal register
 *   
 *
 *   Parameters:
 *   unsigned char reg     register number
 *
 *   Returns:
 *   unsigned short        register value
 *
 */
unsigned char PCA9550::readRegister(unsigned char reg)
{
    wire.beginTransmission(address);
    wire.write(reg);

    if ( wire.requestFrom(address, 1) == 1)
    {
        return wire.read();
    }
    
    return -1;
}

/**
 *
 *   Sets the value of the selected internal register
 *   
 *   Parameters:
 *   unsigned char reg     register number
 *   unsigned short        register value
 *
 */
void PCA9550::writeRegister(unsigned char reg, unsigned char val)
{
    wire.beginTransmission(address);
    wire.write(reg);    
    wire.write(val);    
    wire.endTransmission();
}
