#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
#include <AT24C02.h>
uchar code table0[]=		  //共阳码
                   { 0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
				     0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
uchar code table2[]={0x01,0x02,0x04,0x08};	//位选码
uint count;					   //计数的值
sbit K1=P1^0;				   //加1按钮
sbit K2=P1^3;				   //减1按钮
sbit K3=P1^6;				   //置零按钮

void write_add(uchar address,uchar date);   //调用AT24C02.H中的读写函数
uchar read_add(uchar address);
void initeeprom();

void delayms(uint x)
{
	uchar t;
	while(x--)
		for(t=0;t<120;t++);
}

void AT24c_Read()  //从AT24C02读出count数据
{
	uchar a,b;
	a=read_add(0x00);  //高8位
	delayms(10);
	b=read_add(0x01);  //低8位
	count = a*256+b;
	delayms(10);
}

void AT24c_Write() //把count写入AT24C02
{
	uchar a,b;
	a=count/256;
	b=count%256;
	delayms(10);
	write_add(0x00,a);
	delayms(10);
	write_add(0x01,b);
} 

void display(uint temp)			//显示子程序
{
	uchar i,buf[4];
	buf[0]=temp/1000;			//分离4位数值的千、百、十、个位
	buf[1]=temp%1000/100;
	buf[2]=temp%100/10;
	buf[3]=temp%10;
	for(i=0;i<4;i++)			//4位轮流显示
	{
		P2=table2[i];			//送位选信号
		P0=table0[buf[i]];		//送段选信号
		delayms(5);				//延时一段时间
		P1=0xff;				//消隐
	}
}

void KeyScan()						//按键扫描函数
{									
	if(K1==0)						//加1按键
	{								
		while(K1==0);				//等待用户释放按键
		if(count<9999)count++;		//count加1
		AT24c_Write();			//把count写入AT24C02
	}
	if(K2==0)						//减1按键
	{
		while(K2==0);
		if(count>0)count--;
		AT24c_Write();
	}
	if(K3==0)						//置零按键
	{
		while(K3==0);
		if(count!=0)
		{
			count=0;
			AT24c_Write();
		}
	}
}

void main()						   //主函数
{
	initeeprom();	//读取初始参数
	AT24c_Read();   //从AT24C02中读出count初值
	while(1)
	{
		display(count);
		KeyScan();
	}
}



	
