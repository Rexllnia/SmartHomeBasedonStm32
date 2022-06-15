#include "module_DAC.h"
void module_DAC()
{
		
	  char buf[255],enter[32];
		int i=1,key=0;
	  int count=0;
		OLED_Fill(0x00);
				
	while(1){
		key=keyscan();
	/***********????*******/
		
		OLED_ShowString(50,1,"Sinwave");
		OLED_ShowString(50,2,"Triwave");
		OLED_ShowString(50,3,"Sawwave");
		OLED_ShowString(50,4,"Squwave");
	


		/*******??????******/

		OLED_ShowString(30,1," ");
		OLED_ShowString(30,2," ");
		OLED_ShowString(30,3," ");
		OLED_ShowString(30,4," ");
		OLED_ShowString(30,5," ");
		OLED_ShowString(30,6," ");
		OLED_ShowString(30,i,"*");
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
		if(key==44)
		{
			
				strcpy(enter, "");
				OLED_ShowString(10,0,enter);
				OLED_ShowString(10,0,"    ");
			
		}
		
		if(key==43) //????
		{
			OLED_Fill(0x00);
			return ;
		}
		
		/***???***/
		if(key == 24)
			{

				i++;
				if(i > 4)
					i = 1;
			}
			else if(key == 14)
			{
				i--;
				if(i < 1)
					i = 4;
			}
			else if(key == 34)
			{
				switch(i)
				{
					case 1: 
						while(1)
						{
										key=keyscan();
									if(key==43) //????
									{
										OLED_Fill(0x00);
										break ;
									}
							for(count=0;count<sizeof(Sinwave);count++)
									{
							
										DACconversion(0x90,0x40,  Sinwave[count]/2);
										delay_us(100);
									}
									
						}
					break;
					case 2: 
												while(1)
						{
										key=keyscan();
									if(key==43) //????
									{
										OLED_Fill(0x00);
										break ;
									}
							for(count=0;count<sizeof(Triwave);count++)
									{
							
										DACconversion(0x90,0x40,  Triwave[count]/2);
									
									}
									
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
				switch(i)
				{
					case 1: 
						  OLED_ShowString(0,6,"                  ");
							OLED_ShowString(0,6,"f=");
		          OLED_ShowString(32,6,"V=");
					break;
					case 2: 
						   OLED_ShowString(0,6,"                  ");
							 OLED_ShowString(0,6,"f=");
		           OLED_ShowString(32,6,"V=");
					break;
					case 3:
               OLED_ShowString(0,6,"                  ");						
						   OLED_ShowString(0,6,"f=");
		           OLED_ShowString(32,6,"V=");
						   OLED_ShowString(64,6,"PWM=");
					break;
					case 4:
						   OLED_ShowString(0,6,"                  ");						
						   OLED_ShowString(0,6,"f=");
		           OLED_ShowString(32,6,"V=");
					break;

					default:break;
				}
			OLED_Refresh();
		}
	
}