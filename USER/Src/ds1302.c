#include "ds1302.h"
#include "sys.h"
#include "cmsis_os.h"
extern osMessageQId myQueue02Handle;
struct TIMEData TimeData;
uint8_t read_time[7];
  void delay(int32_t us)
{
	
	while(us--)
	{
		
	}
}
void ds1302_gpio_init()//CE,SCLK端口初始化
{
  GPIO_InitTypeDef GPIO_InitStruct={0};
  HAL_GPIO_WritePin(DATA_GPIO_Port, CE_Pin|SCLK_Pin, GPIO_PIN_RESET);
  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = CE_Pin|SCLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(DATA_GPIO_Port, &GPIO_InitStruct);
}
 
void ds1032_DATAOUT_init()//配置双向I/O端口为输出态
{
  GPIO_InitTypeDef GPIO_InitStruct={0};
  HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_RESET);
  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = DATA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(DATA_GPIO_Port, &GPIO_InitStruct);
}
 
void ds1032_DATAINPUT_init()//配置双向I/O端口为输入态
{
	GPIO_InitTypeDef GPIO_InitStruct={0};
  GPIO_InitStruct.Pin = DATA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(DATA_GPIO_Port, &GPIO_InitStruct);
}
 
 
void ds1302_write_onebyte(uint8_t data)//向DS1302发送一字节数据
{
uint8_t count=0;
ds1032_DATAOUT_init();

SCLK_L;
for(count=0;count<8;count++)
	{	SCLK_L;
		if(data&0x01)
		{DATA_H;}
		else{DATA_L;}//先准备好数据再发送
		SCLK_H;//拉高时钟线，发送数据
		data>>=1;
	}
}
 
void ds1302_wirte_rig(uint8_t address,uint8_t data)//向指定寄存器地址发送数据
{
uint8_t temp1=address;
uint8_t temp2=data;
CE_L;SCLK_L;delay(1);
CE_H;delay(2);
ds1302_write_onebyte(temp1);
ds1302_write_onebyte(temp2);
CE_L;SCLK_L;delay(2);
}
 
uint8_t ds1302_read_rig(uint8_t address)//从指定地址读取一字节数据
{
uint8_t temp3=address;
uint8_t count=0;
uint8_t return_data=0x00;
CE_L;SCLK_L;delay(3);
CE_H;delay(3);
ds1302_write_onebyte(temp3);
ds1032_DATAINPUT_init();//配置I/O口为输入
delay(2);
for(count=0;count<8;count++)
	{
	delay(2);//使电平持续一段时间
	return_data>>=1;
	SCLK_H;delay(4);//使高电平持续一段时间
	SCLK_L;delay(14);//延时14us后再去读取电压，更加准确
	if(HAL_GPIO_ReadPin(DATA_GPIO_Port,DATA_Pin))
	{return_data=return_data|0x80;}
	
	}
delay(2);
CE_L;DATA_L;
return return_data;
}
 
void ds1032_init()
{
ds1302_wirte_rig(0x8e,0x00);//关闭写保护
ds1302_wirte_rig(0x80,0x10);//seconds10秒
ds1302_wirte_rig(0x82,0x10);//minutes10分
ds1302_wirte_rig(0x84,0x10);//hours10时
ds1302_wirte_rig(0x86,0x12);//date12日
ds1302_wirte_rig(0x88,0x05);//months5月
ds1302_wirte_rig(0x8a,0x03);//days星期三
ds1302_wirte_rig(0x8c,0x21);//year2021年
ds1302_wirte_rig(0x8e,0x80);//关闭写保护
}
 
void ds1032_read_time()
{
read_time[0]=ds1302_read_rig(0x81);//读秒
read_time[1]=ds1302_read_rig(0x83);//读分
read_time[2]=ds1302_read_rig(0x85);//读时
read_time[3]=ds1302_read_rig(0x87);//读日
read_time[4]=ds1302_read_rig(0x89);//读月
read_time[5]=ds1302_read_rig(0x8B);//读星期
read_time[6]=ds1302_read_rig(0x8D);//读年
}
 
void ds1032_read_realTime()
{
ds1032_read_time();  //BCD码转换为10进制

TimeData.second=(read_time[0]>>4)*10+(read_time[0]&0x0f);
TimeData.minute=((read_time[1]>>4)&(0x07))*10+(read_time[1]&0x0f);
TimeData.hour=(read_time[2]>>4)*10+(read_time[2]&0x0f);
TimeData.day=(read_time[3]>>4)*10+(read_time[3]&0x0f);
TimeData.month=(read_time[4]>>4)*10+(read_time[4]&0x0f);
TimeData.week=read_time[5];
TimeData.year=(read_time[6]>>4)*10+(read_time[6]&0x0f)+2000;
osMessagePut(myQueue02Handle,TimeData.second,osWaitForever);

}
