#ifndef __DS18B20_H
#define __DS18B20_H 

#include "main.h"
#include "sys.h"
//IO????
#define DS18B20_IO_IN()  {GPIOB->CRL&=0XFFFFFFF0;GPIOB->CRL|=8<<0;}
#define DS18B20_IO_OUT() {GPIOB->CRL&=0XFFFFFFF0;GPIOB->CRL|=3<<0;}

//IO????
#define	DS18B20_DQ_OUT PBout(0) //????	PA0
#define	DS18B20_DQ_IN  PBin(0)  //????	PA0 
 void delay_us(uint32_t delay); 	
uint8_t DS18B20_Init(void);			//???DS18B20
short DS18B20_Get_Temp(void);		//????
void DS18B20_Start(void);			//??????
void DS18B20_Write_Byte(uint8_t dat);//??????
uint8_t DS18B20_Read_Byte(void);	//??????
uint8_t DS18B20_Read_Bit(void);		//?????
uint8_t DS18B20_Check(void);		//??????DS18B20
void DS18B20_Rst(void);				//??DS18B20
#endif