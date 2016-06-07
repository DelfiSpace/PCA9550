#include "PCA9550.h"

/**
 *
 *   PCA9550 class creator function
 *   
 *   Parameters:
 *   DWire *i2c             I2C object pointer
 *
 */
PCA9550:: PCA9550(DWire *i2c, unsigned char addr)
{
    wire = i2c;
    address = addr;
}

void PCA9550::setPeriod(unsigned char channel, float period)
{
    if (channel == 0)
    {
        writeRegister(REG_PSC0, (unsigned  int)((period * 44.0) - 1) & 0xFF);
    }
    else
    {
        writeRegister(REG_PSC1, (unsigned  int)((period * 44.0) - 1) & 0xFF);
    }
}

float PCA9550::getPeriod(unsigned char channel)
{
    if (channel == 0)
    {
        return ((float)readRegister(REG_PSC0) + 1.0) / 44.0;
    }
    else
    {
        return ((float)readRegister(REG_PSC1) + 1.0) / 44.0;
    }
}

void PCA9550::setDC(unsigned char channel, unsigned char dc)
{
    if (channel == 0)
    {
        writeRegister(REG_PWM0, 255 - dc);
    }
    else
    {
        writeRegister(REG_PWM1, 255 - dc);
    }
}

unsigned char PCA9550::getDC(unsigned char channel)
{
    if (channel == 0)
    {
        return 255 - readRegister(REG_PWM0);
    }
    else
    {
        return 255- readRegister(REG_PWM1);
    }
}

void PCA9550::setOutput(unsigned char led, unsigned char status)
{
    unsigned char tmp = readRegister(REG_LS0);
    if (led == 0)
    {
        if (status)
        {
	        writeRegister(REG_LS0, tmp | 0x01);
	    }
	    else
	    {
	    	writeRegister(REG_LS0, tmp & ~0x01);
	    }
	}
	else
	{
	    if (status)
        {
	        writeRegister(REG_LS0, tmp | 0x04);
	    }
	    else
	    {
	    	writeRegister(REG_LS0, tmp & ~0x04);
	    }
	}
}

unsigned char PCA9550::getInput(unsigned char led)
{
    unsigned char tmp = readRegister(REG_INPUT);
    if (led)
    {
        writeRegister(REG_LS0, (tmp >> 1) & 0x01);
    }
    else
    {
    	writeRegister(REG_LS0, tmp & 0x01);
    }
}

void PCA9550::blinkLED(unsigned char led, unsigned char channel)
{
    unsigned char tmp = readRegister(REG_LS0) & 0xF0;
    if (led == 0)
    {
        writeRegister(REG_LS0, tmp | 0x02 | (channel & 0x01));
	}
	else
	{
	    writeRegister(REG_LS0, tmp | (0x02 | (channel & 0x01)) << 2);
	}	
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
unsigned short PCA9550::readRegister(unsigned char reg)
{
    unsigned char ret = -1;
    wire->beginTransmission(address);
    wire->write(reg);
  
    // use the casting to prevent warning on ambiguous conversion
    if (wire->requestFrom(address, (unsigned char)1) == 1)
    {
        ret = wire->read();
    }

    wire->endTransmission(true);
    return ret;
}

/**
 *
 *   Sets the value of the selected internal register
 *   
 *
 *   Parameters:
 *   unsigned char reg     register number
 *   unsigned short        register value
 *
 */
void PCA9550::writeRegister(unsigned char reg, unsigned char val)
{
    wire->beginTransmission(address);
    wire->write(reg);    
    wire->write(val);    

    wire->endTransmission(true);
}