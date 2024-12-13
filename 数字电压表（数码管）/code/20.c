/***************   ���ֵ�ѹ��   ******************/
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
 	uint u = d*100/51; //��0-255�������0.00-5.00�ĵ�ѹ��ֵ
	uchar dis[3];
	dis[0]=u/100;
	dis[1]=u/10%10;
	dis[2]=u%10;

	P2 = 0xf7; //�ұߵ�һλ
	P0 = LEDData[dis[2]];
	DelayMS(3);
	P2 = 0xfb; //�ڶ�λ
	P0 = LEDData[dis[1]];
	DelayMS(3);
	P2 = 0xfd; //����λ
	P0 = LEDData[dis[0]] ;
	DP = 1;	   //С������ʾ
	DelayMS(2);
}

void main()
{
 	TMOD = 0x02;
	TH0  = 256-1;
	TL0  = 256-1; //��ʱ5us��ADC0809ʱ��Ϊ100KHz

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