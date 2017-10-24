#include "includes.h"

u8 data0;//��У��
u8 data1;//ʪ�ȵ�����
u8 data2;//ʪ�ȵ�С��
u8 data3;//�¶ȵ�����
u8 data4;//�¶ȵ�С��
u8 i=0;
u8 wendu[]="�¶�";
u8 shidu[]="ʪ��";
char dd[10];
/*
DHT11���ùܽ�����
PB9--VCC
���ģʽ
*/

void DHT11_OUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʱ��PBʱ��
	
	GPIO_InitStruct.GPIO_Pin =GPIO_Pin_9;//PB9�ܽ�
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_Out_PP;//�������
	GPIO_InitStruct.GPIO_Speed =GPIO_Speed_50MHz;//����ٶ�
	GPIO_Init(GPIOB, &GPIO_InitStruct);//GPIOB�ĳ�ʼ��
	VCC_H;//��������
}
/*
����ģʽ
*/
void DHT11_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʱ��PBʱ��
	
	GPIO_InitStruct.GPIO_Pin =GPIO_Pin_9;//PB9�ܽ�
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOB, &GPIO_InitStruct);//GPIOB�ĳ�ʼ��
}
void DTH11_Config(void)
{
	DHT11_OUT();
	DHT11_IN();
}
/*
��ȡDHT11��ֵ
*/
void RED_Data(void)
{
	DHT11_OUT();//���ģʽ
	VCC_L;
	Delay_ms(20);
	VCC_H;
	Delay_us(30);
	
	DHT11_IN();//����ģʽ
	while(RD_DHT11_DATA);//��Ӧ�ź� �ȴ�����
	while(!RD_DHT11_DATA);//�ȴ�����
	while(RD_DHT11_DATA);//�ȴ���ƽ��϶
	//��������
	for(i=0;i<40;i++)
	{
		while(!RD_DHT11_DATA);//�ȴ���ƽ���� ��������
		Delay_us(50);//��ʱ50 �ж��߼�ֵ
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
	DHT11_OUT();//���ģʽ
	Delay_us(50);
	VCC_H;//��������
}
/*
У�麯��
*/
u8 Check(void)
{
	u8 j=0xff;//У���־λ
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
LCD��ʾ��ʪ��ֵ
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
