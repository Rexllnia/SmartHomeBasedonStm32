
#include "main.h"
#include "sys.h"
#include "ds18b20.h"
void iic_receive();
void iic_send();
extern uint8_t ack;
//�����ߺ���
extern void Start_I2c();
//�������ߺ���  
extern void Stop_I2c();
//Ӧ���Ӻ���
extern void Ack_I2c(uint8_t a);
//�ֽ����ݷ��ͺ���
extern void  SendByte(unsigned char  c);
//���ӵ�ַ���Ͷ��ֽ����ݺ���               
extern uint8_t ISendStr(unsigned char sla,unsigned char suba,unsigned char *s,unsigned char no) ;
//���ӵ�ַ���Ͷ��ֽ����ݺ���   
extern uint8_t ISendStrExt(unsigned char sla,unsigned char *s,unsigned char no);
//���ӵ�ַ���ֽ����ݺ���               
extern unsigned char RcvByte();