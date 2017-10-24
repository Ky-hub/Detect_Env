#ifndef _DHT11_H_
#define _DHT11_H_
#include "stm32f10x.h"
#define VCC_H   GPIO_SetBits( GPIOB,GPIO_Pin_9)
#define VCC_L   GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define RD_DHT11_DATA   GPIO_ReadInputDataBit( GPIOB, GPIO_Pin_9)//读取数据寄存器的值
void DHT11_OUT(void);
void DHT11_IN(void);
void RED_Data(void);
void DTH11_Config(void);
void DHT_Echo(void);
u8 Check(void);
#endif

