#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "stm32f10x.h"
#define BH170_ON     0x01     //
#define BH170_ADDR   (0x23<<1)   
#define BH170_RSET   0x07
#define BH170_CON    0x11
#define BH170_ONE    0x21
void BH170_Init(void);
void BH170_Write(void);
void BH170_Read(void);
u16 Dispose_Data(void);
void Echo_BH170(void);


#endif


