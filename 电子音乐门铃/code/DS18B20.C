/***************   DS18B20.C 温度传感器（-55～125 C）   ******************/
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

sbit DQ = P2^3;

void Delay(uint x)
{ 	while(--x);  }

uchar Init_DS18B20()  //成功返回0，失败返回1
{
 	uchar status;
	DQ = 1;	Delay(8);
	DQ = 0;	Delay(90);
	DQ = 1;	Delay(8);
	status = DQ; Delay(100);
	DQ = 1;
	return status;
}

uchar ReadOneByte()	//读一个字节
{
 	uchar i,dat=0;
	DQ = 1;	_nop_();
	for(i=0;i<8;i++)
	{
	 	DQ = 0;
		dat >>= 1;
		DQ = 1;	_nop_(); _nop_();
		if(DQ)
			dat |= 0X80;
		Delay(30);
		DQ = 1;
	}
	return dat;
}

void WriteOneByte(uchar dat)  //写一个字节
{
 	uchar i;
	for(i=0;i<8;i++)
	{
	 	DQ = 0;
		DQ = dat & 0x01;
		Delay(5);
		DQ = 1;
		dat >>= 1;
	}
}

int Get_Temperature()	 //读取温度
{
 	int t;
	float tt;
	uchar a,b,fh;//fh表示负号
	Init_DS18B20();
	WriteOneByte(0xcc);//跳过读序列号，可加速
	WriteOneByte(0x44);	//启动温度转换
	Init_DS18B20();
	WriteOneByte(0xcc);//跳过读序列号，可加速
	WriteOneByte(0xbe);	//读取温度寄存器（共9个，前两个为温度）
	a = ReadOneByte(); //低位
	b = ReadOneByte(); //高位		
	Delay(100);
	fh = b & 0x80;
	if(fh!=0) //fu的最高位为1，表示负数
	{
		b = ~b;
		a = ~a;
		tt = ((b*256)+a+1)*0.0625;
		t=(int)(tt*10)*(-1);
	}
	else
	{
		tt =((b*256)+a)*0.0625;
		t=(int)(tt*10);
	}				

	return t;
}

								