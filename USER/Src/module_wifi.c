#include "module_wifi.h"
#include "stdlib.h"
#include "cstring"
#include "ds1302.h"
extern char led;
extern osMessageQId wifi_flagHandle;
extern osMessageQId ADC_VALUEHandle;
extern osMailQId myQueue05Handle;
extern osMailQId myQueue06Handle;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern char clock_state; 
//extern char ok,error;
void wifi_init(UART_HandleTypeDef *huart)
{

	HAL_UART_Receive_DMA(&huart1,(uint8_t *)&aRxBuffer1,1);
//	HAL_UART_Transmit(&huart1,"AT+ROLE=0\r\n", strlen("AT+ROLE=0\r\n"),0xffff);
	osDelay(5000);
	
	__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);
	HAL_UART_Receive_DMA(huart,(uint8_t *)&aRxBuffer3,1);
//	HAL_UART_Transmit_DMA(huart,AT_CWJAP, strlen((char*)AT_CWJAP));
	osDelay(5000);
//	HAL_UART_Transmit_DMA(huart, AT_CIFSR, strlen((char*) AT_CIFSR));
	osDelay(5000);
 HAL_UART_Transmit_DMA(huart, AT_CIPSTART, strlen((char*) AT_CIPSTART));
	osDelay(5000);
	HAL_UART_Transmit_DMA(huart, AT_CIPSEND8, strlen((char*) AT_CIPSEND8));
	osDelay(200);
	HAL_UART_Transmit_DMA(huart, "hi\r\n", strlen((char*) AT_CIPSEND8));
	
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function should not be modified, when the callback is needed,
	
           the HAL_UART_TxHalfCpltCallback could be implemented in the user file
   */
	if(huart->Instance==USART1){
		HAL_UART_Receive_DMA(&huart1,(uint8_t *)&aRxBuffer1,1);
	}
	if(huart->Instance==USART3){
		HAL_UART_Receive_DMA(&huart3,(uint8_t *)&aRxBuffer3,1);
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	char buf[255],enter[32];
	int i=1,temp=0;
	uint8_t data[30]={"\n I have received:OK"};
	char *map;
  char key[25];
	char value[4];
	int year,mon,day,hour,min,sec;
		char *ssid;
	char *passwd;
	char time_data[36];
	UNUSED(huart);
	if(huart->Instance==USART1){
		Uart1_RxBuffer[Uart1_Rx_Cnt++]=aRxBuffer1;
		if((Uart1_RxBuffer[Uart1_Rx_Cnt-1]==0x0A)&&(Uart1_RxBuffer[Uart1_Rx_Cnt-2]==0x0D))
		{
			HAL_UART_Transmit_DMA(&huart1,(uint8_t *)Uart1_RxBuffer, strlen(Uart1_RxBuffer));
			if(strstr(Uart1_RxBuffer,"passwd")!=NULL)
			{
						strtok(Uart1_RxBuffer,":");
						ssid=strtok(NULL,"_");
						strtok(NULL,":");
						passwd=strtok(NULL,"_");
						strcat(AT_CWJAP,ssid);		
						strcat(AT_CWJAP,"\",\"");
						strcat(AT_CWJAP,passwd);
						strcat(AT_CWJAP,"\"\r\n");
						 my_printf("%s",AT_CWJAP);
						strcpy(AT_CWJAP,"AT+CWJAP=\"");
					}
			Uart1_Rx_Cnt=0;
		}
		HAL_UART_Receive_DMA(&huart1,(uint8_t *)&aRxBuffer1,1);
		
	}
	if(huart->Instance==USART3){
		Uart3_RxBuffer[Uart3_Rx_Cnt++]=aRxBuffer3;
	if((Uart3_RxBuffer[Uart3_Rx_Cnt-1]==0x0A)&&(Uart3_RxBuffer[Uart3_Rx_Cnt-2]==0x0D))
	{   
		  osMailPut(myQueue06Handle,Uart3_RxBuffer);
			if(strstr(Uart3_RxBuffer, "led") != NULL)//在a中查找b，如果存在，
			{
				osMessagePut(wifi_flagHandle,1,10);
			}
			else
			{
				osMessagePut(wifi_flagHandle,0,10);
			}
			if(strstr(Uart3_RxBuffer, "led_breath") != NULL)//在a中查找b，如果存在，
			{
					 led=1;
			}
			if(strstr(Uart3_RxBuffer, "led_off") != NULL)//在a中查找b，如果存在，
			{
					 led=0;
			}
			if(strstr(Uart3_RxBuffer, "led_on") != NULL)//在a中查找b，如果存在，
			{
					 led=2;
			}
			if(strstr(Uart3_RxBuffer, "date") != NULL)//在a中查找b，如果存在，
			{
					strcpy(time_data,Uart3_RxBuffer);
					strtok(time_data,"_");
					year=atoi(strtok(NULL,"-"));    
					mon=atoi(strtok(NULL,"-"));    
					day=atoi(strtok(NULL,"_"));          
					hour=atoi(strtok(NULL,":"));
					min=atoi(strtok(NULL,":"));     
					sec=atoi(strtok(NULL,":"));
				  strtok(NULL,"_");
					ds1302_wirte_rig(0x8e,0x00);//关闭写保护
					ds1302_wirte_rig(0x80,dtoh(sec));//seconds10秒
					ds1302_wirte_rig(0x82,dtoh(min));//minutes10分
					ds1302_wirte_rig(0x84,dtoh(hour));//hours10时
					ds1302_wirte_rig(0x86,dtoh(day));//date12日
					ds1302_wirte_rig(0x88,dtoh(mon));//months5月
					ds1302_wirte_rig(0x8c,dtoh(year));//year2021年
					ds1302_wirte_rig(0x8e,0x80);//关闭写保护
			}
	
			if(strstr(Uart3_RxBuffer, "valid") != NULL)//在a中查找b，如果存在，
			{
				HAL_UART_Transmit_DMA(&huart3, AT_CIPSTART, strlen((char*) AT_CIPSTART));
			}
		Uart3_Rx_Cnt=0;
	}
	HAL_UART_Receive_DMA(&huart3,(uint8_t *)&aRxBuffer3,1);
}
	
	
}
int dtoh(int hex)
{
    int temp=0;
    int i=1;
    while(hex) 
    {
        
        temp+=i*(hex%10);
        hex=hex/10;
        i*=16;
    }
    return temp;
}
