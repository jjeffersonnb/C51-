/***************   数字电压表   ******************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char

uchar code LEDData[]=
{
 	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f
};
sbit OE  = P1^0;
sbit EOC = P1^1;
sbit ST  = P1^2;
sbit CLK = P1^3;
sbit DP  = P0^7;

void DelayMS(uint ms)
{
 	uchar i;
	while(ms--)
	{
	 	for(i=0;i<120;i++);
	}
}

void Display_Result(uchar d)
{
 	uint u = d*100/51; //将0-255级换算成0.00-5.00的电压数值
	uchar dis[3];
	dis[0]=u/100;
	dis[1]=u/10%10;
	dis[2]=u%10;

	P2 = 0xf7; //右边第一位
	P0 = LEDData[dis[2]];
	DelayMS(3);
	P2 = 0xfb; //第二位
	P0 = LEDData[dis[1]];
	DelayMS(3);
	P2 = 0xfd; //第三位
	P0 = LEDData[dis[0]] ;
	DP = 1;	   //小数点显示
	DelayMS(2);
}

void main()
{
 	TMOD = 0x02;
	TH0  = 256-1;
	TL0  = 256-1; //定时5us，ADC0809时钟为100KHz

	IE   = 0x82;
	TR0  = 1;
	P1   = 0x3f;
	while(1)
	{
	 	ST = 0;
		ST = 1;
		ST = 0;
		while(EOC == 0);
		OE = 1;
		Display_Result(P3);
		OE = 0;
	}
}

void Timer0_INT() interrupt 1
{
 	CLK = !CLK;
}