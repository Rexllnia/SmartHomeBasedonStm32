#ifndef __DHT11_H
#define __DHT11_H

#include "main.h"
#include "sys.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

//IO方向设置
#define DHT11_IO_IN()  {IODHT22_GPIO_Port->CRL &= 0xFFFFFFF0;	IODHT22_GPIO_Port->CRL |= 8 ;}	// PC10 IN  MODE
#define DHT11_IO_OUT() {IODHT22_GPIO_Port->CRL &= 0xFFFFFFF0;	IODHT22_GPIO_Port->CRL |= 3 ;}	// PC10 OUT MODE


#define	DHT11_DQ_OUT PBout(0) //数据端口	PC10
#define	DHT11_DQ_IN  PBin(0)  //数据端口	PC10

u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(u8 *temp, u8 *humi); //读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11
u8 DHT11_Read_Data_Float(float *temp,float *humi);
void delay_us(uint32_t delay);
#endif
