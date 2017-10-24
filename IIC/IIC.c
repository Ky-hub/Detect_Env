#include "includes.h"

 
// IIC初始化
void IIC_Init(void)
{					     
	// STM32芯片外设的IIC2复用引脚PB10-SCL PB11-SDA
	// 我们不用STM32的IIC外设，自己模拟时序，但是还是用这两个IO
	
 	RCC->APB2ENR|=1<<3;     // PB10 SCL  PB11 SDA
	GPIOB->CRH&=~(0xff);
	GPIOB->CRH|=(0x3<<8)|(0x3<<12);
	GPIOB->ODR|=3<<10;      // 持续输出1 给总线加上拉
}

// 起始信号
void IIC_Start(void)
{
	SDA_OUT();     // 数据线做输出
	IIC_SDA(1);     // 拉高数据线
	IIC_SCL(1);     // 拉高时钟线
	Delay_us(4);   
 	IIC_SDA(0);     // 拉低数据线，在时钟线高电平期间
	Delay_us(4);
	IIC_SCL(0);     // 拉低时钟线 为发送数据做准备
}	

// 停止信号
void IIC_Stop(void)
{
	SDA_OUT();
	IIC_SCL(0);    
	IIC_SDA(0);
 	Delay_us(4);
	IIC_SCL(1);
	IIC_SDA(1); 
	Delay_us(4);							   	
}

// 等待从机应答
u8 IIC_Wait_Ack(void)
{
	u8 TimeOut=0;
	
	SDA_IN(); 
	IIC_SDA(1);
	Delay_us(1);	   
	IIC_SCL(1); 
	Delay_us(1);
	while(READ_SDA)
	{
		TimeOut++;
		if(TimeOut>0xFE)
		{
			IIC_Stop();
			return 1; 
		}
	}
	IIC_SCL(0);
	return 0;  
} 

// 给从机应答
void IIC_Ack(void)
{
	IIC_SCL(0); 
	SDA_OUT(); 
	IIC_SDA(0);
	Delay_us(2);
	IIC_SCL(1); 
	Delay_us(2);
	IIC_SCL(0); 
}

// 不给从机应答    
void IIC_NAck(void)
{
	IIC_SCL(0);
	SDA_OUT();
	IIC_SDA(1); 
	Delay_us(2);  
	IIC_SCL(1); 
	Delay_us(2);  
	IIC_SCL(0); 
}	

// 发送字节			  
void IIC_Send_Byte(u8 data)
{                        

	u8 i;
	SDA_OUT();
	IIC_SCL(0);
	
	Delay_us(2);
	//开始发送数据
	for(i=0;i<8;i++)
	{
		if(data & 0x80)//判断数据是否为1
		{
			IIC_SDA(1);
		}
		else
		{
			IIC_SDA(0);
		}
		data <<= 1;
		Delay_us(2);
		
		IIC_SCL(1);//拉高时钟线 延时
		
		Delay_us(5);
		
		IIC_SCL(0);//拉低时钟线 延时 数据的稳定性
		Delay_us(3);		
	}
	
	IIC_SDA(1);//释放数据线
	Delay_us(1);
	
}
	

// 读字节 参数：1产生应答 0无应答  
u8 IIC_Read_Byte(unsigned char Ack)
{
	u8 i,RxData=0;
	
	SDA_IN(); 
	
  for(i=0;i<8;i++ ) 
	{
      IIC_SCL(0);
      Delay_us(2);     
		  IIC_SCL(1); 
      RxData<<=1; 
      if(READ_SDA)     //读出数据    一个周期读一位   共8位
				RxData++;
		  Delay_us(1);  
   }	
    if (!Ack)
        IIC_NAck();
    else
        IIC_Ack();
    return RxData;
}
