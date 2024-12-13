#include<reg51.h>
sbit INT_1=P1^0;
sbit LED1=P1^1;
sbit INT_2=P1^2;
sbit LED2=P1^3;
sbit INT_3=P1^4;
sbit LED3=P1^5;
sbit INT_4=P1^6;
sbit LED4=P1^7;
void  main()
{
	P1=0x55;		//P1.0,P1.2,P1.4,P1.6为输入，其他引脚输出
	EX0=1;			//允许外部中断0中断
	IT0=1;			//选择边沿触发方式
	EA=1;			//CPU开中断
	while (1);		//等待中断
}
void int0_server( ) interrupt 0
{	
	P1=0x55;
	if (INT_1) LED1=0;		//故障1为高电平，则LED1点亮
	if (INT_2) LED2=0;
	if (INT_3) LED3=0;
	if (INT_4) LED4=0;
}
