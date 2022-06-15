#ifndef __MODULE_WIFI_H
#define __MODULE_WIFI_H
#include "main.h"
#include "cmsis_os.h" 
extern uint16_t Uart3_Rx_Cnt;//鎺ユ敹璁℃暟
extern uint8_t aRxBuffer3;//鎺ユ敹缂撳啿
extern char Uart3_RxBuffer[100];//鎺ユ敹鍐呭
extern uint16_t Uart1_Rx_Cnt;
extern uint8_t aRxBuffer1;
extern char Uart1_RxBuffer[100];
static uint8_t *AT_RST = "AT+RST\r\n";	       
static uint8_t *At_CwMode = "AT+CWMODE?\r\n";	        //查询工作模式
static uint8_t *AT_CWLIF = "AT+CWLIF\r\n";
//AT+CIPSTART=2,"TCP","192.168.1.42",3333
static uint8_t *AT_CIPSTART = "AT+CIPSTART=\"TCP\",\"3.106.58.48\",5555\r\n";
//AT+CIPSEND=2,8
static uint8_t *AT_CIPSEND8= "AT+CIPSEND=8\r\n";
static uint8_t *AT_CIPSEND47= "AT+CIPSEND=47\r\n";
static uint8_t *SEND = "12333333\n";
//static uint8_t *AT_CWMODE= = "AT+CWMODE=3\r\n";
static char AT_CWJAP[] = "AT+CWJAP=\"";
//AT+CIPMUX=1
static uint8_t *AT_CIPMUX = "AT+CIPMUX=1\r\n";
//AT+CIFSR
static uint8_t *AT_CIFSR = "AT+CIFSR\r\n";
void wifi_init(UART_HandleTypeDef *huart);
void getvalueForKey(char *keyValue, char *key, char *value);
int dtoh(int hex);
extern void my_printf(const char *fmt, ...);
#endif
