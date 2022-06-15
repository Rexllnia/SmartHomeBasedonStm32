#include "Matrix_keyboard.h"


int checkkey()
{
	GPIOA->ODR=0x00;
	if(((GPIOB->IDR)&0xf000)==0xf000)
	{return 0;}
	return 1;
	
}
int keyscan()
{
	int i=0,j=0;
	int codevalue=0;
	if(checkkey()==1)
	{
		
		osDelay(50);   //检查按下
		if(checkkey()==1)
		{	
		 //vPortEnterCritical();
		 GPIOA->ODR=~(0x01);
			for(i=0;i<4;i++)
			{
				for(j=0;j<4;j++)
				{
					if(PBin(j+12)==0)//PB口扫描
					{
							codevalue=(i+1)*10+(j+1);
							
							while(PBin(j+12)==0);

							return codevalue;
					}
					
				}
				GPIOA->ODR=~((~(GPIOA->ODR))<<1);//PA口扫描
			}
		}
	}
	return 0;
}
