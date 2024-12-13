//串行数据转并行数据，控制8只LED来回滚动点亮, 2017.11.13
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
 	uchar i,c = 0x01;
	SCON = 0x00; //方式0
	SBUF = c;while(TI==0);TI = 0; //发送c
	Delay(200);
	while(1)
	{
	 	for(i=0;i<7;i++)
		{
			c = _crol_(c,1);  //c左移一位
			SBUF = c;while(TI==0);TI = 0; //发送c
		    Delay(200);	//延时0.2秒
		}
		for(i=0;i<7;i++)
		{
			c = _cror_(c,1);  //c左移一位
			SBUF = c;while(TI==0);TI = 0; //发送c
		    Delay(200);	//延时0.2秒
		}

	}
}