#include<reg52.h>
#include<math.h>
sbit CS=P3^1;
sbit SCLK=P3^0;
sbit DIN=P3^2;
float num=0;
unsigned int j,t;
void DAC(unsigned int adata)
{
	char i;
		adata<<=2;				//10位数据升为12位，低2位无效
	CS=0;					//片选有效
	for(i=11;i>=0;i--)
	{
			SCLK=0;		//时钟低电平
			DIN=adata&(0x001<<i);  	//按位将数据送入
			SCLK=1;				//时钟高电平
	}
	SCLK=0;					//时钟低电平
	CS=1;						//片选高电平,数据送DAC寄存器
}
void main()
{
	CS=1;
	while(1)
	{
		j=300;					//设置y轴零点对应的数字量
		num=num+0.01;			//x轴步长取0.01
		if(num>=6.28)			//x轴角度为0~2π
		num=0;
		t=sin(num)*200;			//计算函数值并扩大200倍
		j=j+t;					//合成函数值与零点数值
		DAC(j);					//调D/A转换程序
	}
}
