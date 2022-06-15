#ifndef __pcf8591_H__
#define __pcf8591_H__

#include "main.h"
#include "myI2C.h"

uint8_t DACconversion(unsigned char sla,unsigned char c,  unsigned char Val);
//u8 ISendByte(unsigned char sla,unsigned char c);
//u8 IRcvByte(unsigned char sla); 

#endif