#ifndef __PCA9550_H__
#define __PCA9550_H__

#include "Energia.h"
#include <Wire.h>

#define REG_INPUT		0
#define REG_PSC0		1
#define REG_PWM0		2
#define REG_PSC1		3
#define REG_PWM1		4
#define REG_LS0			5

class PCA9550
{
protected:
    unsigned char address;
    
    unsigned short readRegister(unsigned char);
    void writeRegister(unsigned char, unsigned char); 

public:

    PCA9550(unsigned char);
    virtual ~PCA9550() {};
    
    void setPeriod(unsigned char, float);
    float getPeriod(unsigned char);
    void setDC(unsigned char, unsigned char);
    unsigned char getDC(unsigned char);
    void setOutput(unsigned char, unsigned char);
    unsigned char getInput(unsigned char);
    void blinkLED(unsigned char, unsigned char);

private:
  
};

#endif // __PCA9550_H__ 