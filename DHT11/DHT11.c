#include "includes.h"

u8 data0;//和校验
u8 data1;//湿度的整数
u8 data2;//湿度的小数
u8 data3;//温度的整数
u8 data4;//温度的小数
u8 i=0;
u8 wendu[]="温度";
u8 shidu[]="湿度";
char dd[10];
/*
DHT11所用管脚配置
PB9--VCC
输出模式
*/

void DHT11_OUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//时能PB时钟
	
	GPIO_InitStruct.GPIO_Pin =GPIO_Pin_9;//PB9管脚
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStruct.GPIO_Speed =GPIO_Speed_50MHz;//输出速度
	GPIO_Init(GPIOB, &GPIO_InitStruct);//GPIOB的初始化
	VCC_H;//总线拉高
}
/*
输入模式
*/
void DHT11_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//时能PB时钟
	
	GPIO_InitStruct.GPIO_Pin =GPIO_Pin_9;//PB9管脚
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStruct);//GPIOB的初始化
}
void DTH11_Config(void)
{
	DHT11_OUT();
	DHT11_IN();
}
/*
读取DHT11的值
*/
void RED_Data(void)
{
	DHT11_OUT();//输出模式
	VCC_L;
	Delay_ms(20);
	VCC_H;
	Delay_us(30);
	
	DHT11_IN();//输入模式
	while(RD_DHT11_DATA);//响应信号 等待拉低
	while(!RD_DHT11_DATA);//等待拉高
	while(RD_DHT11_DATA);//等待电平间隙
	//接收数据
	for(i=0;i<40;i++)
	{
		while(!RD_DHT11_DATA);//等待电平拉高 接收数据
		Delay_us(50);//延时50 判断逻辑值
		if(RD_DHT11_DATA)
		{
			if(i<8)
			{
				data1 |=( 1<<(8-i-1));
			}
			if(i>=8&&i<16)
			{
				data2 |=(1<<(16-i-1));
			}
			if(i>=16&&i<24)
			{
				data3 |=(1<<(24-i-1));
			}
			if(i>=24&&i<32)
			{
				data4 |=(1<<(32-i-1));
			}
			if(i>=32&&i<40)
			{
				data0 |=(1<<(40-i-1));
			}
			while(RD_DHT11_DATA);
		}
		
	}
	DHT11_OUT();//输出模式
	Delay_us(50);
	VCC_H;//总线拉高
}
/*
校验函数
*/
u8 Check(void)
{
	u8 j=0xff;//校验标志位
	if(data0==(data1+data2+data3+data4))
	{
		j=1;
		return 1;
	}
		
	else 
	{
		j=0;
		return 0;
	}
}
/*
LCD显示温湿度值
*/

void DHT_Echo(void)
{
	Draw_Text_8_16_Str(20,50,RED,YELLOW,shidu);
	Draw_Text_8_16_Str(100,50,RED,YELLOW,wendu);
	sprintf(dd,":%d",data1);
	Draw_Text_8_16_Str(50,50,RED,YELLOW,(unsigned char *)dd);
	sprintf(dd,":%d",data3);
	Draw_Text_8_16_Str(130,50,RED,YELLOW,(unsigned char *)dd);
}
