#include <reg51.h>
#include <absacc.h>
#define uchar unsigned char
#define KEY_LED XBYTE[0xFEFF]

void main()
{
	uchar t;
	while(1)
	{
		t=KEY_LED;
		KEY_LED=t;
	}
}
	