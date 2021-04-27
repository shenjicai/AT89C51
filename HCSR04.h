#ifndef __HCSR04_H__
#define __HCSR04_H__

#include <intrins.h>		//����_nop_( )�պ���ָ���ͷ�ļ�
#define uchar unsigned char
#define uint unsigned int

void delay_50us(uint t);
void Delay12us(void);

//�������ź�
sbit Trig    = P1^0;		// ������ģ���Trig�ܽ�
sbit Echo    = P1^1;		// ������ģ���Echo�ܽ�


float gSpeedL;				// ���泬�������ٶ�ֵ
uint distL;					
uint olddistL;
unsigned int  timeL=0;

uint GetDistanceL(void)
{	

	uint ss;					// ���ڼ�¼��õľ���
	
	for(ss=0;ss<8;ss++)//��4�����ڵĲ�
	{    
		Trig=1;    		
		Delay12us();    //ȷ��Ƶ����40kHz����
		
		Trig=0;    
		Delay12us();    

	} 
	
	TR0=1;//��������   
	while(!Echo); //�շ��䣬�����䲨������ܶˣ�RX���ɵ͵�ƽ��������㡣
	while((Echo==1)&&(TF0==0));  //���û�յ�����T1û���ж�(��ʱ)���ȴ�
	TR0=0; //�����������

	if(TF0==1)  
	{       
		TF0=0; 
  		return 999;//������Χ  
	}  
	else
	{ 
		timeL=TH0*256+TL0;
	  TH0=0;
	  TL0=0;
	  ss=timeL *0.017; //(timeL*gSpeedL/1000)/2+8;		// ����cm=��ʱ��us * �ٶ�cm/us��/2    340m/s = 34 000 cm/1000 000 us
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