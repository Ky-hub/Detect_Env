#include "includes.h"

u8 BH_Data[2]={0};
const unsigned char beam[]={"光照强度"};
//const unsigned char hjzl[]={"环境质量"};
void BH170_Init(void)
{
	IIC_Init();
	BH170_Write();
}
/*启动BH170*/
void BH170_Start(void)
{
	IIC_Start();
	IIC_Send_Byte(BH170_ADDR+0);//
	IIC_Wait_Ack();
	IIC_Send_Byte(BH170_ON );//通电
	IIC_Wait_Ack();
	IIC_Stop();
	
	
	IIC_Start();
	IIC_Send_Byte(BH170_ADDR+0);//
	IIC_Wait_Ack();
	IIC_Send_Byte(BH170_ONE);//单次H模式//通电
	IIC_Wait_Ack();
	IIC_Stop();
	
}
/*写指令*/
void BH170_Write(void)
{
	IIC_Start();
	IIC_Send_Byte(BH170_ADDR+0);
	IIC_Wait_Ack();
	IIC_Send_Byte(BH170_ONE);
	IIC_Wait_Ack();
	IIC_Stop();
		
}
/*读数据*/
void BH170_Read(void)
{
	
	IIC_Start();
	IIC_Send_Byte(BH170_ADDR+1);
	IIC_Wait_Ack();
	BH_Data[0]=IIC_Read_Byte(1);//高字节
	//IIC_Ack();
	BH_Data[1]=IIC_Read_Byte(0);//低字节
	//IIC_NAck();
	IIC_Stop();	
}
/*数据处理*/
u16 Dispose_Data(void)
{
	
	return (u16)(((BH_Data[0]<<8)+BH_Data[1])/1.2f);
}

/*显示数据*/
void Echo_BH170(void)
{
	float nn;
	char BH[10];
	BH170_Start();//开始
	Delay_ms(180);
	BH170_Read();//读取数据
	sprintf(BH,"%05d",Dispose_Data());
	nn=atoi(BH);
	Draw_Text_8_16_Str(10,100,YELLOW,BLACK,beam);
	Draw_Text_8_16_Str(80,100,YELLOW,BLACK,BH);
	//printf("BH170: %d",Dispose_Data());//发送到串口
}


