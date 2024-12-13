//并行数据转串行数据
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
sbit SPL = P2^5;  //Shift and Load

void Delay(uint x)
{
 	uchar i;
	while(x--)
	{
	 	for(i=0;i<120;i++);
	}
}

void main()
{
 	SCON = 0x10;  //模式0，并允许接受
	while(1)
	{
	 	SPL = 0;	//置数（load），读入并行输入的8位数据
		SPL = 1;	//移位（shift），并口输入被封锁，串行转换开始
		while(RI == 0);	//等待接收完所有数据
		RI = 0;
		P0 = SBUF;
		Delay(20);
	}
}