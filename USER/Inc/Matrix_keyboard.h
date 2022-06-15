#ifndef __MATRIX_KEYBOARD_H
#define __MATRIX_KEYBOARD_H
#include "main.h"

#include "sys.h" 
#include <stdio.h>
//#include <stdlib.h>
//#include "ssd1306.h"
//#include "ds18b20.h"
//extern UART_HandleTypeDef huart3;
int checkkey();
int keyscan();
void test();
//void key_init()
//{
//int i=0;
//GPIO_InitTypeDef GPIO_InitStructure;
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4; 
//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//????

//	
//GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//GPIOA->ODR=0x0f;

//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;//????
//	GPIO_Init(GPIOB, &GPIO_InitStructure);

//}
#endif
