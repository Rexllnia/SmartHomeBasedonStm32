
/*************************�˲���ΪI2C���ߵ���������*************************************/

#include <myI2C.h>

#define  SCL     PBout(3)
#define  SDA_out PBout(4)
#define  SDA_in  PBin(4)

uint8_t ack;                 /*Ӧ���־λ*/
void iic_receive()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = myI2C_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void iic_send()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = myI2C_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP ;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/*******************************************************************
                     �����ߺ���               
����ԭ��: void  Start_I2c();  
����:     ����I2C����,������I2C��ʼ����.  
********************************************************************/
void Start_I2c()
{
 SDA_out=1;         /*������ʼ�����������ź�*/
 delay_us(1);
  SCL=1;
 delay_us(1);        /*��ʼ��������ʱ�����4.7us,��ʱ*/
 delay_us(1);
 delay_us(1);
 delay_us(1);
 delay_us(1);    
 SDA_out=0;         /*������ʼ�ź�*/
 delay_us(1);        /* ��ʼ��������ʱ�����4��s*/
 delay_us(1);
 delay_us(1);
 delay_us(1);
 delay_us(1);       
  SCL=0;       /*ǯסI2C���ߣ�׼�����ͻ�������� */
 delay_us(1);
 delay_us(1);
}

/*******************************************************************
                      �������ߺ���               
����ԭ��: void  Stop_I2c();  
����:     ����I2C����,������I2C��������.  
********************************************************************/
void Stop_I2c()
{
 SDA_out=0;      /*���ͽ��������������ź�*/
 delay_us(1);       /*���ͽ���������ʱ���ź�*/
  SCL=1;      /*������������ʱ�����4��s*/
 delay_us(1);
 delay_us(1);
 delay_us(1);
 delay_us(1);
 delay_us(1);
 SDA_out=1;      /*����I2C���߽����ź�*/
 delay_us(1);
 delay_us(1);
 delay_us(1);
 delay_us(1);
}

/*******************************************************************
                 �ֽ����ݷ��ͺ���               
����ԭ��: void  SendByte(UCHAR c);
����:     ������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������,�����ȴ�Ӧ��,����
          ��״̬λ���в���.(��Ӧ����Ӧ��ʹack=0)     
           ��������������ack=1; ack=0��ʾ��������Ӧ����𻵡�
********************************************************************/
void  SendByte(unsigned char  c)
{
 unsigned char  uint8_tCnt;
 
 for(uint8_tCnt=0;uint8_tCnt<8;uint8_tCnt++)  /*Ҫ���͵����ݳ���Ϊ8λ*/
    {
     if((c<<uint8_tCnt)&0x80)SDA_out=1;   /*�жϷ���λ*/
       else SDA_out=0;                
    delay_us(1);
     SCL=1;               /*��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ*/
     delay_us(1); 
     delay_us(1);             /*��֤ʱ�Ӹߵ�ƽ���ڴ���4��s*/
     delay_us(1);
     delay_us(1);
     delay_us(1);         
     SCL=0; 
    }
    
   delay_us(1);
   delay_us(1);
   SDA_out=1;                /*8λ��������ͷ������ߣ�׼������Ӧ��λ*/
   delay_us(1);
   delay_us(1);   
    SCL=1;
   delay_us(1);
   delay_us(1);
   delay_us(1);
   iic_receive();
    if(SDA_in==1)ack=0;     
       else ack=1;        /*�ж��Ƿ���յ�Ӧ���ź�*/
       iic_send();
    SCL=0;
   delay_us(1);
   delay_us(1);
}

/*******************************************************************
                 �ֽ����ݽ��պ���               
����ԭ��: UCHAR  RcvByte();
����:        �������մ���������������,���ж����ߴ���(����Ӧ���ź�)��
          ���������Ӧ����Ӧ��ӻ���  
********************************************************************/    
unsigned char   RcvByte()
{
  unsigned char  retc;
  unsigned char  uint8_tCnt;
  
  retc=0; 
 SDA_out=1;                     /*��������Ϊ���뷽ʽ*/
  for(uint8_tCnt=0;uint8_tCnt<8;uint8_tCnt++)
      {
       delay_us(1);           
        SCL=0;                  /*��ʱ����Ϊ�ͣ�׼����������λ*/
       delay_us(1);
       delay_us(1);                 /*ʱ�ӵ͵�ƽ���ڴ���4.7��s*/
       delay_us(1);
       delay_us(1);
       delay_us(1);
        SCL=1;                  /*��ʱ����Ϊ��ʹ��������������Ч*/
       delay_us(1);
       delay_us(1);
        retc=retc<<1;
        iic_receive();
        if(SDA_in==1)retc=retc+1;  /*������λ,���յ�����λ����retc�� */
        iic_send();
       delay_us(1);
       delay_us(1); 
       
      }
  SCL=0;    
 delay_us(1);
 delay_us(1);
  return(retc);
}

/********************************************************************
                     Ӧ���Ӻ���
����ԭ��:  void Ack_I2c(uint8_t a);
����:      ����������Ӧ���ź�(������Ӧ����Ӧ���źţ���λ����a����)
********************************************************************/
void Ack_I2c(uint8_t a)
{
  
  if(a==0)SDA_out=0;              /*�ڴ˷���Ӧ����Ӧ���ź� */
  else SDA_out=1;
 delay_us(1);
 delay_us(1);
 delay_us(1);      
  SCL=1;
 delay_us(1);
 delay_us(1);                    /*ʱ�ӵ͵�ƽ���ڴ���4��s*/
 delay_us(1);
 delay_us(1);
 delay_us(1);  
  SCL=0;                     /*��ʱ���ߣ�ǯסI2C�����Ա��������*/
 delay_us(1);
 delay_us(1);    
}




