#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit LED1 = P0^0;
sbit LED2 = P0^3;
sbit K1 = P1^0;

void Delay(uint x)
{
 	uchar i;
	while(x--)
	{
	 	for(i=0;i<120;i++);
	}
}

void Send(uchar c)
{
 	SBUF = c;
	while(TI == 0);
	TI = 0;
}

void main()
{
 	uchar Operation_NO = 0;
	SCON = 0x40;
	TMOD = 0x20;
	PCON = 0x00;
	TH1 = 0xf4;
	TL1 = 0xf4;
	TI = 0;
	TR1 = 1;
	while(1)
	{
	 	if(K1 == 0)
		{
		 	while(K1==0);
			Operation_NO=(Operation_NO+1)%4;
		}
		switch(Operation_NO)
		{
		 	case 0:
					LED1=LED2=1; break;
			case 1:
					Send('A');
					LED1=~LED1;LED2=1;break;
			case 2:
					Send('B');
					LED2=~LED2;LED1=1;break;
			case 3:
					Send('C');
					LED1=~LED1;LED2=LED1;break;
		}
		Delay(100);
	}
}