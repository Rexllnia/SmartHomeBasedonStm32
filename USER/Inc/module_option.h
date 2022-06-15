#ifndef __MODULE_OPTION_H
#define __MODULE_OPTION_H
#include "main.h"
#include "cmsis_os.h" 
//#include "FreeRTOS.h"
//#include  "module_wifi.h"
void module_option(osEvent Event);
extern int key ;
extern uint8_t cursor;
extern char oled_buf[255],enter[4];
extern osMessageQId myQueue01Handle;

#endif