/*  正反转可调速电机系统 2014.12.3 */
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit K1 = P3^0;	//正转按钮
sbit K2 = P3^1;	//反转按钮
sbit K3 = P3^2;	//停止按钮
sbit K4 = P3^3;	//加速按钮
sbit K5 = P3^4;	//减速按钮
sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;
sbit MA   = P1^0; //A点
sbit MB   = P1^1; //B点

uchar DS; //DS代表电机状态 0停止 1正转 2反转
uchar SPEED; //SPEED代表转速级别，1～10
uchar count;  //PWM占空比控制 0 ～ 9

void zhengzhuan()  //正转
{
	LED1 = 0;
	LED2 = 1;
	LED3 = 1;
	DS   = 1;
}
void fanzhuan()	 //反转
{
	LED1 = 1;
	LED2 = 0;
	LED3 = 1;
	DS   = 2;
}
void stop()		 //停止
{
	LED1 = 1;
	LED2 = 1;
	LED3 = 0;
	DS   = 0;
}

void Key_Scan()
{
	 	if(K1 == 0)	 //正转
		{
		 	while(K1 == 0);
			zhengzhuan();
		}
		if(K2 == 0)	 //反转
		{
		 	while(K2 == 0);
			fanzhuan();
		}
		if(K3 == 0)	 //停止
		{
		 	while(K3 == 0);
			stop();
		}
		if(K4 == 0)	 //加速
		{
			while(K4 == 0);
			if(SPEED<10)SPEED++;
		}
		if(K5 == 0)	 //减速
		{
			while(K5 == 0);
			if(SPEED>1)SPEED--;
		}

} 	

void main(void)
{
	LED1 = 1;
	LED2 = 1;
	LED3 = 0;
	DS = 0;
	SPEED = 5; //代表中速
	count = 0;

	TMOD = 0x02; //T0 方式2 自动重载初值
	TH0 = 256-100;
	TL0 = 256-100;  //定时100微秒
	EA = 1;
	ET0 = 1;
	TR0 = 1;

	while(1)
	{
		Key_Scan();
	}
}

void timer0() interrupt 1
{
	if(++count>9)count = 0;
	switch(DS)
	{
		case 0:	MA = 1;  //停止
				MB = 1;
				break;
		case 1: MA = 0;	 //正转
				if(count < SPEED)
					MB = 1;
				else
					MB = 0;
				break;
		case 2: MB = 0;	  //反转
				if(count < SPEED)
					MA = 1;
				else
					MA = 0;
	}	
}
