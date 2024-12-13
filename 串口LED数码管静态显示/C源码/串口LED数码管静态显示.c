#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};

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
	SCON=0x00;
	while(1)
	{
		for(i=0;i<16;i++)
		{	
			SBUF = table[i];
			while(!TI);
			TI = 0;
			delayms(500);
		}
	}
}


	
