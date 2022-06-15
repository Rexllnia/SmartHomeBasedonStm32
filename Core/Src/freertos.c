/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdarg.h"
#include "stdio.h"
#include "ssd1306.h"
#include "dht11.h"
//#include "ds18b20.h"
#include "SDdriver.h"
#include "Matrix_keyboard.h"
#include "module_wifi.h"
#include "ds1302.h"
#include "module_option.h"
#include "filedir.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
//struct TIMEData TimeData;
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart1;
extern IWDG_HandleTypeDef hiwdg;
extern ADC_HandleTypeDef hadc2;
uint8_t temp=0,humi=0;
char USART_buf[50],oled_buf[255],enter[4];
char *p;
int cmp=0;
int key=0;
uint8_t cursor=1;
char led;
char clock_state=0;
//uint8_t wifistatue=0;
osMailQId myQueue04Handle;
osMailQId myQueue05Handle;
osMailQId myQueue06Handle;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
uint32_t defaultTaskBuffer[ 128 ];
osStaticThreadDef_t defaultTaskControlBlock;
osThreadId myTask02Handle;
uint32_t myTask02Buffer[ 128 ];
osStaticThreadDef_t myTask02ControlBlock;
osThreadId myTask03Handle;
uint32_t myTask03Buffer[ 128 ];
osStaticThreadDef_t myTask03ControlBlock;
osThreadId myTask04Handle;
uint32_t myTask04Buffer[ 128 ];
osStaticThreadDef_t myTask04ControlBlock;
osThreadId myTask05Handle;
uint32_t myTask05Buffer[ 128 ];
osStaticThreadDef_t myTask05ControlBlock;
osThreadId myTask06Handle;
uint32_t myTask06Buffer[ 128 ];
osStaticThreadDef_t myTask06ControlBlock;
osThreadId myTask08Handle;
uint32_t myTask08Buffer[ 128 ];
osStaticThreadDef_t myTask08ControlBlock;
osThreadId myTask09Handle;
uint32_t myTask09Buffer[ 128 ];
osStaticThreadDef_t myTask09ControlBlock;
osMessageQId myQueue01Handle;
osMessageQId myQueue02Handle;
osMessageQId myQueue03Handle;
osMessageQId wifi_flagHandle;
osMessageQId ADC_VALUEHandle;
osMessageQId wifi_statueHandle;
osSemaphoreId myBinarySem01Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void vprint(const char *fmt, va_list argp) {
	char string[200];
	if (0 < vsprintf(string, fmt, argp)) // build string
			{
		HAL_UART_Transmit_DMA(&huart3, (uint8_t*) string, strlen(string)); // send message via UART
		
	}
}

void my_printf(const char *fmt, ...) // custom printf() function
{
	va_list argp;
	va_start(argp, fmt);
	vprint(fmt, argp);
	va_end(argp);
}
void vprint_UART1(const char *fmt, va_list argp) {
	char string[200];
	if (0 < vsprintf(string, fmt, argp)) // build string
			{
		HAL_UART_Transmit(&huart1, (uint8_t*) string, strlen(string),1000); // send message via UART
		
	}
}

int UART1_printf(const char *fmt, ...) // custom printf() function
{
	va_list argp;
	va_start(argp, fmt);
	vprint_UART1(fmt, argp);
	va_end(argp);
	return 0;
}
void led_PWM(int cmp)
{       
	int i=0;
				for(i=1;i<100;i++)
          {
							if(i<cmp)
							{
								HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
								delay_us(200);	
							}
							else
							{
								HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
								delay_us(200);
							}
          }  
}
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);
void StartTask04(void const * argument);
void StartTask05(void const * argument);
void StartTask06(void const * argument);
void StartTask08(void const * argument);
void StartTask09(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of myBinarySem01 */
  osSemaphoreDef(myBinarySem01);
  myBinarySem01Handle = osSemaphoreCreate(osSemaphore(myBinarySem01), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of myQueue01 */
  osMessageQDef(myQueue01, 16, uint16_t);
  myQueue01Handle = osMessageCreate(osMessageQ(myQueue01), NULL);

  /* definition and creation of myQueue02 */
  osMessageQDef(myQueue02, 8, uint8_t);
  myQueue02Handle = osMessageCreate(osMessageQ(myQueue02), NULL);

  /* definition and creation of myQueue03 */
  osMessageQDef(myQueue03, 8, uint8_t);
  myQueue03Handle = osMessageCreate(osMessageQ(myQueue03), NULL);

  /* definition and creation of wifi_flag */
  osMessageQDef(wifi_flag, 8, uint8_t);
  wifi_flagHandle = osMessageCreate(osMessageQ(wifi_flag), NULL);

  /* definition and creation of ADC_VALUE */
  osMessageQDef(ADC_VALUE, 16, uint16_t);
  ADC_VALUEHandle = osMessageCreate(osMessageQ(ADC_VALUE), NULL);

  /* definition and creation of wifi_statue */
  osMessageQDef(wifi_statue, 8, uint8_t);
  wifi_statueHandle = osMessageCreate(osMessageQ(wifi_statue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
	osMailQDef(myQueue04,16,uint16_t);
	myQueue04Handle=osMailCreate(osMailQ(myQueue04),NULL);
	
	osMailQDef(myQueue05,16,uint16_t);
	myQueue05Handle=osMailCreate(osMailQ(myQueue05),NULL);
	
	osMailQDef(myQueue06,16,uint16_t);
	myQueue06Handle=osMailCreate(osMailQ(myQueue06),NULL);
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadStaticDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128, defaultTaskBuffer, &defaultTaskControlBlock);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadStaticDef(myTask02, StartTask02, osPriorityNormal, 0, 128, myTask02Buffer, &myTask02ControlBlock);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadStaticDef(myTask03, StartTask03, osPriorityNormal, 0, 128, myTask03Buffer, &myTask03ControlBlock);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* definition and creation of myTask04 */
  osThreadStaticDef(myTask04, StartTask04, osPriorityNormal, 0, 128, myTask04Buffer, &myTask04ControlBlock);
  myTask04Handle = osThreadCreate(osThread(myTask04), NULL);

  /* definition and creation of myTask05 */
  osThreadStaticDef(myTask05, StartTask05, osPriorityNormal, 0, 128, myTask05Buffer, &myTask05ControlBlock);
  myTask05Handle = osThreadCreate(osThread(myTask05), NULL);

  /* definition and creation of myTask06 */
  osThreadStaticDef(myTask06, StartTask06, osPriorityNormal, 0, 128, myTask06Buffer, &myTask06ControlBlock);
  myTask06Handle = osThreadCreate(osThread(myTask06), NULL);

  /* definition and creation of myTask08 */
  osThreadStaticDef(myTask08, StartTask08, osPriorityNormal, 0, 128, myTask08Buffer, &myTask08ControlBlock);
  myTask08Handle = osThreadCreate(osThread(myTask08), NULL);

  /* definition and creation of myTask09 */
  osThreadStaticDef(myTask09, StartTask09, osPriorityNormal, 0, 128, myTask09Buffer, &myTask09ControlBlock);
  myTask09Handle = osThreadCreate(osThread(myTask09), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	
	OLED_Init(hi2c1);
	char *ssid;
	char *passwd;
	char j=0,k=0;
	osEvent keyEvent,blueteethEvent,UART3Event;
	osEvent wififlag,ADCEvent;
  /* Infinite loop */
  for(;;)
  {
		wififlag=osMessageGet(wifi_flagHandle,osWaitForever);
		if(wififlag.status==osEventMessage)
		{
			if(wififlag.value.v==1)
			{
				
				OLED_ShowString(50,5,"success!!!");
			}
			else
			{
				OLED_ShowString(50,5,"sending...");
			}
		}
		ADCEvent=osMessageGet(ADC_VALUEHandle,osWaitForever);
		if(ADCEvent.status==osEventMessage)
		{
			if(ADCEvent.value.v<9)
			{
				sprintf(oled_buf,"ADC:   %d",ADCEvent.value.v);//*(3.3/255)
			}
			if(ADCEvent.value.v>=9&&ADCEvent.value.v<=99)
			{
				sprintf(oled_buf,"ADC:  %d",ADCEvent.value.v);
			}
			if(ADCEvent.value.v>99&&ADCEvent.value.v<=999)
			{
				sprintf(oled_buf,"ADC: %d",ADCEvent.value.v);
			}
			if(ADCEvent.value.v>999&&ADCEvent.value.v<=9999)
			{
				sprintf(oled_buf,"ADC:%d",ADCEvent.value.v);
			}
			OLED_ShowString(10,6,oled_buf);
		}
		keyEvent=osMessageGet(myQueue01Handle,osWaitForever);
		sprintf(oled_buf,"%d",temp);
		OLED_ShowString(50,0,"temp=");
		OLED_ShowString(84,0,oled_buf);
		OLED_ShowString(108,0,"  ");
		OLED_ShowString(50,2,"humi=");
		sprintf(oled_buf,"%d",humi);
		OLED_ShowString(84,2,oled_buf);
		if(keyEvent.status==osEventMessage&&keyEvent.value.v==41)
		{	
		}
		if(keyEvent.status==osEventMessage&&keyEvent.value.v==42)
		{
				module_option(keyEvent);
			
		}
		if(keyEvent.status==osEventMessage&&keyEvent.value.v==43)
		{
			vTaskSuspend(myTask05Handle);
			HAL_UART_Transmit(&huart1,"AT+ROLE=2\r\n", strlen("AT+ROLE=2\r\n"),0xffff);
			my_printf("AT\r\n");
			osDelay(1000);
			my_printf("AT\r\n");
			osDelay(1000);
			my_printf("AT\r\n");
			osDelay(1000);
			OLED_Fill(0x00);
			my_printf("AT+CWJAP?\r\n");
			while(1)
			{
					UART3Event=osMailGet(myQueue06Handle,10);
					if(UART3Event.status==osEventMail)
					{
	          p=strtok(Uart3_RxBuffer,"\r\n");
							OLED_ShowString(0,++j,p);
						if(j==6)
						{
							j=0;
							OLED_Fill(0x00);
						}
					}
				keyEvent=osMessageGet(myQueue01Handle,osWaitForever);
				if(keyEvent.status==osEventMessage&&keyEvent.value.v==43)
				{
					vTaskResume(myTask05Handle);
					my_printf("%s",AT_CWJAP);
					OLED_Fill(0x00);
					OLED_Refresh();
					break;
				}
				OLED_Refresh();
			}
		}
		OLED_Refresh();
    osDelay(100);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
	 //OLED_Init(hi2c1);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
  /* Infinite loop */
  for(;;)
  {
		if(led == 2)//关闭
		{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
		}
		if(led==1)//呼吸模式
		{
			for(cmp=0;cmp<100;cmp+=3)
			{
				led_PWM(cmp);
				//osDelay(20);
			}
		
			for(cmp;cmp>0;cmp-=3)
			{
				led_PWM(cmp);
				//osDelay(20);
			}
		}
		if(led==0)//普�?�模�?
		{
			led_PWM(100);
		}
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
	
  /* Infinite loop */
  for(;;)
  {
		
		
		key=keyscan();
		osMessagePut(myQueue01Handle,key,osWaitForever);
		
	  osDelay(100);
		
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartTask04(void const * argument)
{
  /* USER CODE BEGIN StartTask04 */
	vPortEnterCritical();
	DHT11_Init();
	vPortExitCritical();
  /* Infinite loop */
  for(;;)
  {
		
		//vPortRaiseBASEPRI();
		//__HAL_UART_DISABLE_IT(&huart3,UART_IT_RXNE);
		osDelay(500);
		vPortEnterCritical();
		
		Uart3_Rx_Cnt=0;
		DHT11_Read_Data(&temp, &humi); //读取温湿�?
		
		//DHT11_Read_Data_Float(&temp,&humi);
		//temp=DS18B20_Get_Temp();
		vPortExitCritical();
		
		__HAL_UART_ENABLE_IT(&huart3,UART_IT_RXNE);
		osDelay(500);

  }
  /* USER CODE END StartTask04 */
}

/* USER CODE BEGIN Header_StartTask05 */
/**
* @brief Function implementing the myTask05 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask05 */
void StartTask05(void const * argument)
{
  /* USER CODE BEGIN StartTask05 */
	char *dht11buf;
	osEvent UartEvent,ADCEvent,wifi_statueEvent;
	char len_buf[25];
wifi_init(&huart3);
  /* Infinite loop */
  for(;;)
  { 

		ADCEvent=osMessageGet(ADC_VALUEHandle,osWaitForever);
		if(ADCEvent.status==osEventMessage)
		{
			sprintf(USART_buf,"{\"device\":\"stm32f103c8t6\",\"ADC\":%d,}\n",ADCEvent.value.v);
			sprintf(USART_buf,"AT+CIPSEND=%d\r\n",strlen(USART_buf));
			HAL_UART_Transmit_DMA(&huart3, USART_buf, strlen((char*)USART_buf));
			osDelay(500);
			sprintf(USART_buf,"{\"device\":\"stm32f103c8t6\",\"ADC\":%d,}\n",ADCEvent.value.v);
			HAL_UART_Transmit_DMA(&huart3, USART_buf, strlen((char*)USART_buf));
			osDelay(500);
		}
		sprintf(USART_buf,"{\"device\":\"stm32f103c8t6\",\"humi\":%d,\"temp\":%d,}\n",humi,temp);
		HAL_UART_Transmit_DMA(&huart3, AT_CIPSEND47, strlen((char*) AT_CIPSEND47));
		osDelay(500);
		UartEvent=osMailGet(myQueue04Handle,200);
		if(UartEvent.status==osEventMail)
		{
			strcpy(USART_buf,UartEvent.value.p);
		}
		HAL_UART_Transmit_DMA(&huart3, USART_buf, strlen((char*)USART_buf));
    osDelay(500);
    osDelay(1);
  }
  /* USER CODE END StartTask05 */
}

/* USER CODE BEGIN Header_StartTask06 */
/**
* @brief Function implementing the myTask06 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask06 */
void StartTask06(void const * argument)
{
  /* USER CODE BEGIN StartTask06 */
	
  /* Infinite loop */
  for(;;)
  {
		HAL_IWDG_Refresh(&hiwdg);//喂狗
//    HAL_UART_Receive_DMA(&huart3,(uint8_t *)&aRxBuffer3,1);
    osDelay(1);
  }
  /* USER CODE END StartTask06 */
}

/* USER CODE BEGIN Header_StartTask08 */
/**
* @brief Function implementing the myTask08 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask08 */
void StartTask08(void const * argument)
{
  /* USER CODE BEGIN StartTask08 */
	
  /* Infinite loop */
  for(;;)
  {
		
		ds1032_read_realTime();
    osDelay(1);
  }
  /* USER CODE END StartTask08 */
}

/* USER CODE BEGIN Header_StartTask09 */
/**
* @brief Function implementing the myTask09 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask09 */
void StartTask09(void const * argument)
{
  /* USER CODE BEGIN StartTask09 */
	uint8_t buf[25];
	uint16_t Value[22];
	uint16_t AD_Value,max,min;
	uint16_t ADC_mv;
  /* Infinite loop */
  for(;;)
  {
				for(char n=0;n<22;n++) 
        {//�?22个忼做滤波甿
            HAL_ADC_Start(&hadc2);
            HAL_ADC_PollForConversion(&hadc2, 10);    //等待转换完成，第二个参数表示超时时间，单位ms        
            if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc2), HAL_ADC_STATE_REG_EOC))
            {
                Value[n]=HAL_ADC_GetValue(&hadc2);
                AD_Value += Value[n];
            }                
        }
        max=Value[0];
        min=Value[0];
        for(char n=0;n<22;n++)//取最大忼㿁最小忿
        {
            max=(Value[n]<max)?max:Value[n];    
            min=(min<Value[n])?min:Value[n];
        }
		ADC_mv=((AD_Value -max-min)/20*3300/4096);
		osMessagePut(ADC_VALUEHandle,ADC_mv,osWaitForever);	
		//HAL_UART_Transmit_DMA(&huart3,(uint8_t *)buf,strlen(buf));
    AD_Value=0;
    osDelay(1);
  }
  /* USER CODE END StartTask09 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
