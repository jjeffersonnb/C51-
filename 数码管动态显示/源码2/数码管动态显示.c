#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table0[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
uchar code table2[]={0x01,0x02,0x04,0x08};
uchar count,j;

void delayms(uint x)
{
	uchar t;
	while(x--)
	{
		for(t=0;t<120;t++);
	}
}

void main()
{
	uchar i;
	count=0;
	j=0;
	TMOD=0x01;
	EA=1;
	ET0=1;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;  //50ms
	TR0=1;
	while(1)
	{
		for(i=0;i<4;i++)
		{	
			P2=table2[i];
			P0=table0[i+j];
			delayms(5);
		}
	}
}

void timer0() interrupt 1
{
 	TR0=0;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;  //50ms
	if(++count==20)	//20*50ms=1s
	{	
		count=0;
		if(++j==13)j=0;
	}
	TR0=1;
}


	
