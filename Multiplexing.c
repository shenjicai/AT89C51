#include <reg52.h>
sbit LED1 = P1^2;
sbit LED2 = P1^4;
unsigned char t,s;

void time0_Init()
{
        TMOD = 0x01;
        TH0 = 0x3C;                   //50ms
        TL0 = 0xB0;
        TR0 = 1;
        EA = 1;
        ET0 = 1;
}
void timer0() interrupt        1          //2个分频器
{
        t++;
        s++;
        TH0 = 0x3C;
        TL0 = 0xB0;
        if(s==5)                 //250ms
        {
                s = 0;
                LED1 = !LED1;                 
        }
        if(t==20)                 //1000ms
        {
                t = 0;
                LED2 = !LED2;
        }
}
void main()
{
        time0_Init();
        while(1);

}