#include<reg52.h>
#include<intrins.h>
sbit CS=P3^5;
sbit CLK=P3^6;
sbit DIN=P3^4;
sbit DOUT=P3^3;
unsigned int tmp;
unsigned int vot;
//定义函数，输入参数为命令字，输出为转换结果
unsigned int TLC2543(unsigned char command)
{
	unsigned char i;
	unsigned int result=0;
	CS=1;							
	CLK=0;
	CS=0;							//片选有效
	for(i=0;i<12;i++)
	{
		DOUT=1;					//P3.3为输入口
		result<<=1;					//result数据左移一位
		result|=DOUT;				//DOUT线上的数据写到result的最低位上
		DIN=command&(0x80>>i);	//将命令字按位送出
		CLK=1;		
		nop_();						//高电平保持一定宽度
		nop_();
		CLK=0;					
	}
	return  result;					//返回转换结果
}

void main()
{	
	while(1)
	{		
		tmp=TLC2543(0x30);		//启动TLC2543转换，通道3，12位数据输出
		vot=(int)tmp*(float)5000/4096;		//结果换算为对应的电压值
		P0=((vot/1000)<<4)|((vot/100)%10);	//取千位和百位的BCD码送P0口
		P2=(((vot%100)/10)<<4)|((vot/10)%10);	//取十位和个位的BCD码送P2口
	}
}
