#include "module_option.h"

void module_option(osEvent Event)
{
	
		
		OLED_Fill(0x00);
				
	while(1){
	/***********????*******/
    
		OLED_ShowString(50,1,"module_time");
		OLED_ShowString(50,2,"module_DA");
		OLED_ShowString(50,3,"module_3");
		OLED_ShowString(50,4,"module_4");
		OLED_ShowString(50,5,"module_5");
		sprintf(oled_buf,"%d",cursor);
		OLED_ShowString(50,6,oled_buf);
		//OLED_ShowString(50,6,"module_6");

		/*******??????******/
		
		OLED_ShowString(30,1," ");
		OLED_ShowString(30,2," ");
		OLED_ShowString(30,3," ");
		OLED_ShowString(30,4," ");
		OLED_ShowString(30,5," ");
		OLED_ShowString(30,6," ");
		OLED_ShowString(30,cursor,"*");
		
//		/*******???*******/
//		if(key==11)
//		{
//			if(strlen(enter)<4){
//				strcat(enter,"1");
//				OLED_ShowString(10,0,enter);
//			}
//			
//		}
//		if(key==12)
//		{
//			if(strlen(enter)<4){
//				strcat(enter,"2");
//				OLED_ShowString(10,0,enter);
//			}
//		}
//			if(key==13)
//		{
//			if(strlen(enter)<4){
//				strcat(enter,"3");
//				OLED_ShowString(10,0,enter);
//			}
//		}
//		if(key==21)
//		{
//			if(strlen(enter)<4){
//				strcat(enter,"4");
//				OLED_ShowString(10,0,enter);
//			}
//		}
//			if(key==22)
//		{
//			if(strlen(enter)<4){
//				strcat(enter,"5");
//				OLED_ShowString(10,0,enter);
//			}
//		}
//			if(key==23)
//		{
//			if(strlen(enter)<4){
//				strcat(enter,"6");
//				OLED_ShowString(10,0,enter);
//			}
//		}
//			if(key==31)
//		{
//			if(strlen(enter)<4){
//				strcat(enter,"7");
//				OLED_ShowString(10,0,enter);
//			}
//		}
//			if(key==32)
//		{
//			if(strlen(enter)<4){
//				strcat(enter,"8");
//				OLED_ShowString(10,0,enter);
//			}
//		}
//			if(key==33)
//		{
//			if(strlen(enter)<4){
//				strcat(enter,"9");
//				OLED_ShowString(10,0,enter);
//			}
//		}
//				if(key==41)
//		{
//			if(strlen(enter)<4){
//				strcat(enter,"0");
//				OLED_ShowString(10,0,enter);
//			}
//		}
		
		//??
			Event=osMessageGet(myQueue01Handle,osWaitForever);
				if(Event.status==osEventMessage)
		{	
			if(Event.value.v==44)
			{
			
				strcpy(enter, "");
				OLED_ShowString(10,0,enter);
				OLED_ShowString(10,0,"    ");
			
			}
		
			if(Event.value.v==43) //????
			{
				OLED_Fill(0x00);
				return ;
			}
		
		/***???***/

			if(Event.value.v== 24)
			{

				cursor++;
				if(cursor > 6)
					cursor = 1;
			}
		
			else if(Event.value.v == 14)
			{
				cursor--;
				if(cursor < 1)
					cursor = 6;
			}
			else if(Event.value.v == 34)
			{
				switch(cursor)
				{
					case 1:module_clock();
					break;
					case 2: filedir();
					break;
					case 3: 
					break;
					case 4:
					break;
					case 5:
					break;
					case 6:
					break;
					default:break;
				
				}
			}
     }
					strcpy(enter, "");
				OLED_ShowString(10,0,enter);
				OLED_ShowString(10,0,"    ");

			OLED_Refresh();
		}
	
}