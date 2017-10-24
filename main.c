/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "includes.h"

/**************** ************************************
函数名：
形参：
返回值：
函数功能：
****************************************************/
u16 AD_DATA;
u8 AD[10];
const unsigned char hjzl[]={"环境质量"};
void Delay(u32 time);
int main(void)
{	
	SysTickConfig();
	LCD_Init();
	LCD_Clear(WHITE);
	DTH11_Config();
	Adc_Init();
	BH170_Init();		
	LED_Config();
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
	while(1)
	{	
		//空气质量检测
		AD_DATA=Get_ADC_Data();
		sprintf(AD,"%d",AD_DATA);
		Draw_Text_8_16_Str(80,80,RED,YELLOW,AD);
		Draw_Text_8_16_Str(10,80,YELLOW,BLACK,hjzl);
		
		//光照强度
		Echo_BH170();
			
	}
}





/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
