#include "filedir.h"
#include "fatfs.h"
void filedir()
{
	FATFS fs;
	FIL file;
	uint8_t res=0;
	UINT Br,Bw;
	char path[4]="0:";
	uint8_t testBuffer[]="SD��д����Ӣ�Ĳ���,SD card Chinese and English reading and writing test!! \r\n";
	uint8_t ReadBuffer[512];
	char success[]="����д�� Ok!\r\n";
	char open[]="�ļ��Ѵ�! \r\n";
  SD_init();
	osDelay(100);
	res=f_mount(&fs,"0:",0);
	if(res!=FR_OK){
		UART1_printf("error!\r\n");
	}else{
		UART1_printf("success,%d\r\n",SD_GetSectorCount());
	}
				f_open(&file,"hello.txt",FA_READ);
		  
        f_read(&file, ReadBuffer,512, &Br);
        

				f_close(&file);
	UART1_printf("%s\n",ReadBuffer);     //??????
}