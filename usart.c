//https://cloud.tencent.com/developer/article/1563163

#include <reg52.h>
#include<intrins.h>
#include"usart.h"
 //串口1的波特率=定时器2的溢出率/4 
 //定时器2的溢出率=sysclk/12/(65536-[T2H,T2L]) //12T模式下
 //所以，串口1的波特率=sysclk/12/4/(65536-[T2H,T2L])
void Uart_Init(void)
{
	TMOD=0x20;	  //定时器工作方式，选择了定时器1，工作方式2 八位初值自动重装的8位定时器。		 
	TH1=0xfd;	  //定时器1初值	,设置波特率为9600 晶振11.0529MHZ?
	TL1=0xfd;
	TR1=1;		  //开启定时器1
 
	SM0=0;
	SM1=1;		  //10位异步接收，（8位数据）波特率可变
    REN=1;		  //允许串行口接收位
	EA=1;	      //允许中断（总闸）
	ES=1;		  //允许串口中断
}

void Sendc(unsigned char * pd)
{
	 while((*pd)!='\0') //字符'\0' : ASCII码为0，表示一个字符串结束的标志。这是转义字符。
	 {
	  SBUF=*pd; //发送一个字符
	  while(!TI);
		TI=0;
	  pd++;  //移动到下一个字符
	 }
}

