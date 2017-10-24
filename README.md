# Test-environment
Temperature and humidity light intensity

使用BH1750光照强度检测模块
使用IIC通信协议完成传感器与单片机的数据传输

1.数字光强度检测模块概述：

引脚：VCC GND SCL SDA ADDR
供电电压：3-5V
数据范围：0-65535
传感器内置16bitAD转换器，直接数字输出
不区分环境光源，接近于视觉灵敏度的分光特性，可对广泛的亮度进行1lx的高精度测量

2.光强的检测过程

实则是单片机与模块的通过I2C通信，使用GPIO口模拟I2C总线，并实现双向传输，则需一个输入输出口(SDA)，另外还需一个输出口(SCL)，不用stm32的IIC外设，自己模拟时序，但是还用这两个复用引脚PB10(SCL) PB11(SDA) 。
