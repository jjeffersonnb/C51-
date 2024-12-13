#include <reg52.h>
#include <absacc.h> 

void delay()		//延时100毫秒左右
{
	unsigned int j,k;
	for(j=100;j>0;j--)
		for(k=120;k>0;k--);
}

void main()
{
	unsigned char i,m;
	while(1)
	{
		m=11;
		for (i=0;i<10;i++)	//向6264的10H单元开始写入10个数据
		{
			XBYTE[0x10+i]=m;
			m++;
			delay();
		}
  }
}
