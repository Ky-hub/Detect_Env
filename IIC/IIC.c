#include "includes.h"

 
// IIC��ʼ��
void IIC_Init(void)
{					     
	// STM32оƬ�����IIC2��������PB10-SCL PB11-SDA
	// ���ǲ���STM32��IIC���裬�Լ�ģ��ʱ�򣬵��ǻ�����������IO
	
 	RCC->APB2ENR|=1<<3;     // PB10 SCL  PB11 SDA
	GPIOB->CRH&=~(0xff);
	GPIOB->CRH|=(0x3<<8)|(0x3<<12);
	GPIOB->ODR|=3<<10;      // �������1 �����߼�����
}

// ��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     // �����������
	IIC_SDA(1);     // ����������
	IIC_SCL(1);     // ����ʱ����
	Delay_us(4);   
 	IIC_SDA(0);     // ���������ߣ���ʱ���߸ߵ�ƽ�ڼ�
	Delay_us(4);
	IIC_SCL(0);     // ����ʱ���� Ϊ����������׼��
}	

// ֹͣ�ź�
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

// �ȴ��ӻ�Ӧ��
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

// ���ӻ�Ӧ��
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

// �����ӻ�Ӧ��    
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

// �����ֽ�			  
void IIC_Send_Byte(u8 data)
{                        

	u8 i;
	SDA_OUT();
	IIC_SCL(0);
	
	Delay_us(2);
	//��ʼ��������
	for(i=0;i<8;i++)
	{
		if(data & 0x80)//�ж������Ƿ�Ϊ1
		{
			IIC_SDA(1);
		}
		else
		{
			IIC_SDA(0);
		}
		data <<= 1;
		Delay_us(2);
		
		IIC_SCL(1);//����ʱ���� ��ʱ
		
		Delay_us(5);
		
		IIC_SCL(0);//����ʱ���� ��ʱ ���ݵ��ȶ���
		Delay_us(3);		
	}
	
	IIC_SDA(1);//�ͷ�������
	Delay_us(1);
	
}
	

// ���ֽ� ������1����Ӧ�� 0��Ӧ��  
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
      if(READ_SDA)     //��������    һ�����ڶ�һλ   ��8λ
				RxData++;
		  Delay_us(1);  
   }	
    if (!Ack)
        IIC_NAck();
    else
        IIC_Ack();
    return RxData;
}
