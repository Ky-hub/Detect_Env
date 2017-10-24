#ifndef __MYIIC_H
#define __MYIIC_H
#include "stm32f10x.h"


// 数据读写方向
#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

#define IIC_SCL(x) x? (GPIOB->ODR |=(1<<10)): (GPIOB->ODR &=~(1<<10)) // SCL
#define IIC_SDA(x) x?    (GPIOB->ODR |=(1<<11)): (GPIOB->ODR &=~(1<<11))  // SDA输出	 
#define READ_SDA  (GPIOB->IDR &( 1 << 11) )   // SDA输入

void IIC_Init(void);           // IIC初始化			 
void IIC_Start(void);				   // 起始信号
void IIC_Stop(void);	  			 // 停止信号
void IIC_Send_Byte(u8 TxData); // 发送一字节
u8 IIC_Read_Byte(unsigned char Ack); // 读取一字节
u8 IIC_Wait_Ack(void); 				 // 等待应答
void IIC_Ack(void);					   // 发送应答
void IIC_NAck(void);				   // 不给应答

#endif




