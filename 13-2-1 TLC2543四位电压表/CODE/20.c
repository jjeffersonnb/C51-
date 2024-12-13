#include<reg52.h>
#include<intrins.h>
sbit CS=P3^5;
sbit CLK=P3^6;
sbit DIN=P3^4;
sbit DOUT=P3^3;
sbit DP  = P0^7;
unsigned char code LEDData[]=
{
 	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f
};
unsigned int tmp;
unsigned int vot; //定义函数，输入参数为命令字，输出为转换结果
void Display_Result(unsigned int d);

void DelayMS(unsigned int ms)
{
 	unsigned char i;
	while(ms--)
	{
	 	for(i=0;i<120;i++);
	}
}

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
		vot=(int)tmp*(float)5000/4096;	//结果换算为对应的电压值
		Display_Result(vot);
	}
}

void Display_Result(unsigned int d)
{
 	unsigned char dis[4];
	dis[0]=d/1000;	  //千位
	dis[1]=d/100%10;  //百位
	dis[2]=(d%100)/10; //十位
	dis[3]=d%10;  //个位
	P2 = 0xf7; //右边第一位	  1111 0111
	P0 = LEDData[dis[3]];
	DelayMS(3);
	P2 = 0xfb; //第二位		  1111 1011
	P0 = LEDData[dis[2]];
	DelayMS(3);
	P2 = 0xfd; //第三位		  1111 1101
	P0 = LEDData[dis[1]] ;
	DelayMS(3);
	P2 = 0xfe; //第三位		  1111 1110
	P0 = LEDData[dis[0]] ;
	DP=1;	   //小数点点亮
	DelayMS(3);
}

