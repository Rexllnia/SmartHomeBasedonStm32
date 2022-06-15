#include "module_clock.h"
#include "ds1302.h"
#include "cmsis_os.h"
#include "string.h"
#include "module_wifi.h"
#include "ssd1306.h"
extern char oled_buf[255];
extern UART_HandleTypeDef huart3;
extern osMessageQId myQueue02Handle;
extern osMessageQId myQueue01Handle;
extern osMailQId myQueue04Handle;
extern char USART_buf[50];
void module_clock()
{
	  osEvent timeEvent;
		osEvent keyEvent;
		char enter[25]="";
		char update_str[50];
		int i=1;
		uint8_t press_counter=0;
		OLED_Fill(0x00);
		osMessagePut(myQueue01Handle,0,osWaitForever);
	while(1){
		timeEvent=osMessageGet(myQueue02Handle,osWaitForever);
		keyEvent=osMessageGet(myQueue01Handle,osWaitForever);
	/***********????*******/
		if(timeEvent.status==osEventMessage)
		{
			sprintf(oled_buf,"%d",timeEvent.value.v);
			if(timeEvent.value.v<=9)
			{
				OLED_ShowString(54,1,"  ");
			}
			OLED_ShowString(50,1,oled_buf);
			OLED_ShowString(80,1,"s");
		}
		sprintf(oled_buf,"%d",TimeData.minute);
		OLED_ShowString(50,2,oled_buf);
			if(TimeData.minute<=9)
			{
				OLED_ShowString(57,2,"  ");
			}
		OLED_ShowString(80,2,"min");
		sprintf(oled_buf,"%d",TimeData.hour);
		OLED_ShowString(50,3,oled_buf);
		
		OLED_ShowString(80,3,"h");
		sprintf(oled_buf,"%d",TimeData.day);
		OLED_ShowString(50,4,oled_buf);
		
		OLED_ShowString(80,4,"day");
		sprintf(oled_buf,"%d",TimeData.month);
		OLED_ShowString(50,5,oled_buf);
		OLED_ShowString(80,5,"month");
		sprintf(oled_buf,"%d",TimeData.year);
		OLED_ShowString(50,6,oled_buf);
		OLED_ShowString(80,6,"year");

		/*******???*******/
		if(keyEvent.status==osEventMessage&&keyEvent.value.v==11)
		{
			if(strlen(enter)<4){
				strcat(enter,"1");
				OLED_ShowString(10,0,enter);
			}
			
		}
		if(keyEvent.status==osEventMessage&&keyEvent.value.v==12)
		{
			if(strlen(enter)<4){
				strcat(enter,"2");
				OLED_ShowString(10,0,enter);
			}
		}
			if(keyEvent.status==osEventMessage&&keyEvent.value.v==13)
		{
			if(strlen(enter)<4){
				strcat(enter,"3");
				OLED_ShowString(10,0,enter);
			}
		}
		if(keyEvent.status==osEventMessage&&keyEvent.value.v==21)
		{
			if(strlen(enter)<4){
				strcat(enter,"4");
				OLED_ShowString(10,0,enter);
			}
		}
			if(keyEvent.status==osEventMessage&&keyEvent.value.v==22)
		{
			if(strlen(enter)<4){
				strcat(enter,"5");
				OLED_ShowString(10,0,enter);
			}
		}
			if(keyEvent.status==osEventMessage&&keyEvent.value.v==23)
		{
			if(strlen(enter)<4){
				strcat(enter,"6");
				OLED_ShowString(10,0,enter);
			}
		}
			if(keyEvent.status==osEventMessage&&keyEvent.value.v==31)
		{
			if(strlen(enter)<4){
				strcat(enter,"7");
				OLED_ShowString(10,0,enter);
			}
		}
			if(keyEvent.status==osEventMessage&&keyEvent.value.v==32)
		{
			if(strlen(enter)<4){
				strcat(enter,"8");
				OLED_ShowString(10,0,enter);
			}
		}
			if(keyEvent.status==osEventMessage&&keyEvent.value.v==33)
		{
			if(strlen(enter)<4){
				strcat(enter,"9");
				OLED_ShowString(10,0,enter);
			}
		}
				if(keyEvent.status==osEventMessage&&keyEvent.value.v==41)
		{
			if(strlen(enter)<4){
				strcat(enter,"0");
				OLED_ShowString(10,0,enter);
			}
		}
//		
		//??
		if(keyEvent.status==osEventMessage&&keyEvent.value.v==42)
		{
			strcpy(update_str,"{\"device\":\"stm32f103c8t6\",\"time\":1}\n");
			osMailPut(myQueue04Handle,update_str);
  		
			

		}
		if(keyEvent.status==osEventMessage&&keyEvent.value.v==43) //????
		{
				OLED_Fill(0x00);
				return ;
		}
		if(keyEvent.status==osEventMessage&&keyEvent.value.v==44)
		{
			
			
			press_counter=!press_counter;
		}
		
		/*******??????******/
		if(press_counter==1)
		{
			OLED_ShowString(30,1," ");
			OLED_ShowString(30,2," ");
			OLED_ShowString(30,3," ");
			OLED_ShowString(30,4," ");
			OLED_ShowString(30,5," ");
			OLED_ShowString(30,6," ");
			OLED_ShowString(30,i,"*");
					if(keyEvent.status==osEventMessage&&keyEvent.value.v == 24)
			{

				i++;
				if(i > 6)
					i = 1;
			}
			else if(keyEvent.status==osEventMessage&&keyEvent.value.v == 14)
			{
				i--;
				if(i < 1)
					i = 6;
			}
			else if(keyEvent.status==osEventMessage&&keyEvent.value.v == 34)
			{
				switch(i)
				{
					case 1:
								 if(atoi(enter)<60)
								 {
										
										ds1302_wirte_rig(0x8e,0x00);//关闭写保护 
										ds1302_wirte_rig(0x80,dtoh(atoi(enter)));//seconds10秒
										ds1302_wirte_rig(0x8e,0x80);//关闭写保护
//										OLED_ShowString(50,1,"    ");
								 }
					break;
					case 2:
								 if(atoi(enter)<60)
								 {
									 
										ds1302_wirte_rig(0x8e,0x00);//关闭写保护 
										ds1302_wirte_rig(0x82,dtoh(atoi(enter)));
										ds1302_wirte_rig(0x8e,0x80);//关闭写保护
//										OLED_ShowString(50,2,"    ");
								 }
					break;
					case 3: 
					break;
					case 4:
					break;
					default:break;
				
				}
					strcpy(enter, "");
				OLED_ShowString(10,0,enter);
				OLED_ShowString(10,0,"    ");
			}
		}
		else
		{
			OLED_ShowString(30,1," ");
			OLED_ShowString(30,2," ");
			OLED_ShowString(30,3," ");
			OLED_ShowString(30,4," ");
			OLED_ShowString(30,5," ");
			OLED_ShowString(30,6," ");
			OLED_ShowString(30,7," ");
		}
//		/***???***/
//			OLED_Fill(0x00);
			OLED_Refresh();
		}
	
}