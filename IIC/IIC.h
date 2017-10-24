#ifndef __MYIIC_H
#define __MYIIC_H
#include "stm32f10x.h"


// ���ݶ�д����
#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

#define IIC_SCL(x) x? (GPIOB->ODR |=(1<<10)): (GPIOB->ODR &=~(1<<10)) // SCL
#define IIC_SDA(x) x?    (GPIOB->ODR |=(1<<11)): (GPIOB->ODR &=~(1<<11))  // SDA���	 
#define READ_SDA  (GPIOB->IDR &( 1 << 11) )   // SDA����

void IIC_Init(void);           // IIC��ʼ��			 
void IIC_Start(void);				   // ��ʼ�ź�
void IIC_Stop(void);	  			 // ֹͣ�ź�
void IIC_Send_Byte(u8 TxData); // ����һ�ֽ�
u8 IIC_Read_Byte(unsigned char Ack); // ��ȡһ�ֽ�
u8 IIC_Wait_Ack(void); 				 // �ȴ�Ӧ��
void IIC_Ack(void);					   // ����Ӧ��
void IIC_NAck(void);				   // ����Ӧ��

#endif




