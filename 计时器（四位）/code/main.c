#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table0[]=		  //共阳码
     { 0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
	   0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
uchar code table2[]={0x01,0x02,0x04,0x08};	//位选码
uint count;
sbit K1=P1^0;				   //十位加1按钮
sbit K2=P1^3;				   //个位加1按钮
sbit K3=P1^6;				   //计时开始按钮
sbit BUZZER=P3^1;			   //蜂鸣器

void delayms(uint x)
{
	uchar t;
	while(x--)
		for(t=0;t<120;t++);
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
	if(K1==0)						//十位加1按键
	{								
		while(K1==0);				//等待用户释放按键
		TR0=0; BUZZER=1;			//关闭定时器与蜂鸣器
		if(count<=9999)count+=10;
	}
	if(K2==0)						//个位加1按键
	{
		while(K2==0);
		TR0=0; BUZZER=1;
		if(count<=9999)count+=1;
	}
	if(K3==0)						//开始按键
	{
		while(K3==0);
		if(count==0)
		{
			TR0=0; BUZZER=1;
		}
		else
			TR0=1;					//计时开始 
	}
}

void main()						   //主函数
{
	count = 0;					   //默认初值为0
	BUZZER = 1;					   //蜂鸣器默认不响
	TMOD=0x01;					   //设置定时器T0工作方式为模式0
	TH0=(65536-50000)/256;		   //定时50ms
	TL0=(65536-50000)%256;		   //开定时器T0中断
	EA=1; ET0=1;
	while(1)
	{
		display(count);
		KeyScan();
	}
}
void timer0() interrupt 1			//定时器T0中断服务函数
{									
	static uchar temp=0;			//内部静态变量，用于计数
	TH0=(65536-50000)/256;			//定时50ms
	TL0=(65536-50000)%256;
	if(++temp==20)					//20*50ms=1s，定时1秒后
	{
		if(count>0)
		{
			count--;				//count减1
			temp=0;
		}
		else
			BUZZER=0;			   //打开蜂鸣器	  		
	}
}


	
