#include <reg52.h>
unsigned char code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};

void main()
{
	SCON=0x00;
	SBUF=table[6];
	while(!TI);
	TI=0;
	SBUF=table[5];
	while(!TI);
	TI=0;
	while(1);
}


	
