#ifndef __HCSR04_H__
#define __HCSR04_H__

#include <intrins.h>		//包含_nop_( )空函数指令的头文件
#define uchar unsigned char
#define uint unsigned int

void delay_50us(uint t);
void Delay12us(void);

//传感器信号
sbit Trig    = P1^0;		// 超声波模块的Trig管脚
sbit Echo    = P1^1;		// 超声波模块的Echo管脚


float gSpeedL;				// 保存超声波的速度值
uint distL;					
uint olddistL;
unsigned int  timeL=0;

uint GetDistanceL(void)
{	

	uint ss;					// 用于记录测得的距离
	
	for(ss=0;ss<8;ss++)//发4个周期的波
	{    
		Trig=1;    		
		Delay12us();    //确保频率在40kHz左右
		
		Trig=0;    
		Delay12us();    

	} 
	
	TR0=1;//立即开启   
	while(!Echo); //刚发射，有衍射波到达接受端，RX会变成低电平，这个不算。
	while((Echo==1)&&(TF0==0));  //如果没收到，且T1没有中断(超时)，等待
	TR0=0; //否则结束测量

	if(TF0==1)  
	{       
		TF0=0; 
  		return 999;//超出范围  
	}  
	else
	{ 
		timeL=TH0*256+TL0;
	  TH0=0;
	  TL0=0;
	  ss=timeL *0.017; //(timeL*gSpeedL/1000)/2+8;		// 距离cm=（时间us * 速度cm/us）/2    340m/s = 34 000 cm/1000 000 us
	} 
	return ss;


}

void Delay12us(void)		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 33;
	while (--i);
}
#endif