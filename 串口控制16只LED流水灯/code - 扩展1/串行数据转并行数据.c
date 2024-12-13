//串行方式0控制16只流水灯滚动点亮，2017.11.13
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

void Delay(uint x) //延时子程序
{
 	uchar i;
	while(x--)
	   for(i=0;i<120;i++);
}

void main()
{
 	uchar i,c = 0x80;
	SCON = 0x00; //方式0
	while(1)
	{ 	
		for(i=0;i<8;i++)
		{
			c = _crol_(c,1);  //c左移一位
			SBUF = c; while(TI==0);TI=0;   //发送c
			SBUF = 0x00;while(TI==0);TI=0; //发送0
			Delay(200);
		}
		for(i=0;i<8;i++)
		{
			c = _crol_(c,1);   //c左移一位
			SBUF = 0x00; while(TI==0); TI=0; //发送0
			SBUF = c; while(TI==0);	TI=0; //发送c
			Delay(200);
		} 
	 }
}