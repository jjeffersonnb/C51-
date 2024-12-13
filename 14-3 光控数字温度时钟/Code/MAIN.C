		 /***************  光控数字温度时钟 优化版2019.12.26  ******************/
#include <reg52.h>
#include <intrins.h>
#include <string.h>
#define uint unsigned int
#define uchar unsigned char

sbit dot = P0^7;
sbit DS1 = P2^0;
sbit DS2 = P2^1;
sbit DS3 = P2^2;
sbit DS4 = P2^3;
sbit K1 = P2^4;
sbit K2 = P2^5;
sbit BUZZER = P2^6;

uchar code LEDData1 [ ] = {  0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff }; //正0-9LED数值
uchar code LEDData2 [ ] = {  0xc0,0xcf,0xA4,0x86,0x8B,0x92,0x90,0xc7,0x80,0x82,0xff }; //反0-9LED数值

uchar DateTime[7]; //日期与时间 [1]分钟，[2]小时
uchar Time[4];  //当前时间 0 1小时 2 3 分钟
uchar second;
uchar k1push;
uint T,L;  //温度，光照
uchar alart,aH,aM; //闹钟指示 小时、分钟
char mode=0;//显示模式：0正常 1小时调节，2分钟调节，3闹钟小时，4闹钟分钟

void GetTime(uchar *DateTime );
void SET_DS1302(uchar *DateTime);
uint readAD(uchar port);

void Delayms(uint ms)
{
 	uchar i;
	while(ms--)
	{
	 	for(i=0;i<120;i++);
	}
} 

void Key_Scan()
{
	if(K2==0) //选择调节对象
	{
		while(K2==0);
		TR0=0;
		mode++;
		if(mode==3 && k1push)SET_DS1302(DateTime);
		if(mode==5){mode=0;k1push=0;TR0=1;}
	} 
	if(K1==0)
	{
		while(K1==0);
		k1push=1;
		switch(mode)
		{
			case 4: //调节闹钟分钟
				aM=(++DateTime[1])%60;
				aH=DateTime[2];
				alart=1;
				break;
			case 3: //调节闹钟小时
				aH=(++DateTime[2])%24;
				aM=DateTime[1];
				alart=1;
				break;
			case 2: //调节 分钟
				DateTime[1]=(++DateTime[1])%60;
				break;
			case 1: //调节 小时
				DateTime[2]=(++DateTime[2])%24;
				break;
		}
	} 
}



void V_Scan() //温度扫描
{
	T=readAD(0x00)*5*0.9814;
	Delayms(5);
	L=readAD(0x10)*5*0.9814;
	
/*	if(L>3180)P3=180; //弱光 10流明以下
	else if(L>2030)P3=210; //中光 10～30流明
	else P3=240;  //强光 30流明以上
*/
	P3=(5000-L)/20;
	Delayms(5);
}

void TIME_Display0()//正常显示时间
{
	Time[0]=DateTime[2]/10; //小时十位
	Time[1]=DateTime[2]%10;	//小时个位
	Time[2]=DateTime[1]/10; //分钟十位
	Time[3]=DateTime[1]%10; //分钟个位 

	DS1=0;DS2=1;DS3=1;DS4=1;
	P0=LEDData1[Time[0]];
	dot=1;	Delayms(5);
	 
	DS1=1;DS2=0;DS3=1;DS4=1;
	P0=LEDData1[Time[1]]-0x80;
	Delayms(5);

	DS1=1;DS2=1;DS3=0;DS4=1;
	P0=LEDData2[Time[2]]-0x80;//第3个数码管，采用反码
	Delayms(5);

	DS1=1;DS2=1;DS3=1;DS4=0;
	P0=LEDData1[Time[3]];
	if(alart){TR1=0;dot=0;}	
	Delayms(5);TR1=1;
}

void TIME_Display1()//小时调节模式，小时2位闪烁
{
	uchar i;	
	Time[0]=DateTime[2]/10; //小时十位
	Time[1]=DateTime[2]%10;	//小时个位
	Time[2]=DateTime[1]/10; //分钟十位
	Time[3]=DateTime[1]%10; //分钟个位 
	for(i=0;i<12;i++)
	{	
		DS1=0;DS2=1;DS3=1;DS4=1;
		P0=LEDData1[Time[0]];
		Delayms(5);
		 
		DS1=1;DS2=0;DS3=1;DS4=1;
		P0=LEDData1[Time[1]]-0x80;
		Delayms(5);

		DS1=1;DS2=1;DS3=0;DS4=1;
		P0=LEDData2[Time[2]]-0x80;//第3个数码管，采用反码
		Delayms(5);

		DS1=1;DS2=1;DS3=1;DS4=0;
		P0=LEDData1[Time[3]];
		Delayms(5);
	}
	for(i=0;i<6;i++)
	{	
		DS1=0;DS2=1;DS3=1;DS4=1;
		P0=0xff;
		Delayms(5);	//灭
		 
		DS1=1;DS2=0;DS3=1;DS4=1;
		P0=0xff-0x80;
		Delayms(5); //灭

		DS1=1;DS2=1;DS3=0;DS4=1;
		P0=LEDData2[Time[2]]-0x80;//第3个数码管，采用反码
		Delayms(5);

		DS1=1;DS2=1;DS3=1;DS4=0;
		P0=LEDData1[Time[3]];
		Delayms(5);
	} 
}

void TIME_Display2()//分钟调节模式，分钟2位闪烁
{
	uchar i;
	Time[0]=DateTime[2]/10; //小时十位
	Time[1]=DateTime[2]%10;	//小时个位
	Time[2]=DateTime[1]/10; //分钟十位
	Time[3]=DateTime[1]%10; //分钟个位 
	for(i=0;i<12;i++)
	{	
		DS1=0;DS2=1;DS3=1;DS4=1;
		P0=LEDData1[Time[0]];
		Delayms(5);
		 
		DS1=1;DS2=0;DS3=1;DS4=1;
		P0=LEDData1[Time[1]]-0x80;
		Delayms(5);

		DS1=1;DS2=1;DS3=0;DS4=1;
		P0=LEDData2[Time[2]]-0x80;//第3个数码管，采用反码
		Delayms(5);

		DS1=1;DS2=1;DS3=1;DS4=0;
		P0=LEDData1[Time[3]];
		Delayms(5);
	}
	for(i=0;i<6;i++)
	{	
		DS1=0;DS2=1;DS3=1;DS4=1;
		P0=LEDData1[Time[0]];
		Delayms(5);
		 
		DS1=1;DS2=0;DS3=1;DS4=1;
		P0=LEDData1[Time[1]]-0x80;
		Delayms(5);

		DS1=1;DS2=1;DS3=0;DS4=1;
		P0=0xff-0x80;//灭
		Delayms(5);

		DS1=1;DS2=1;DS3=1;DS4=0;
		P0=0xff; //	灭
		Delayms(5);
	} 
}

void TIME_Display3()//闹钟小时调节模式，小时两位闪烁，最后数码管小点亮
{
	uchar i;
	Time[0]=DateTime[2]/10; //小时十位
	Time[1]=DateTime[2]%10;	//小时个位
	Time[2]=DateTime[1]/10; //分钟十位
	Time[3]=DateTime[1]%10; //分钟个位 
	for(i=0;i<12;i++)
	{	
		DS1=0;DS2=1;DS3=1;DS4=1;
		P0=LEDData1[Time[0]];
		Delayms(5);
		 
		DS1=1;DS2=0;DS3=1;DS4=1;
		P0=LEDData1[Time[1]]-0x80;
		Delayms(5);

		DS1=1;DS2=1;DS3=0;DS4=1;
		P0=LEDData2[Time[2]]-0x80;//第3个数码管，采用反码
		Delayms(5);

		DS1=1;DS2=1;DS3=1;DS4=0;TR1=0;
		P0=LEDData1[Time[3]]-0x80;
		Delayms(5);TR1=1;
	}
	for(i=0;i<6;i++)
	{	
		DS1=0;DS2=1;DS3=1;DS4=1;
		P0=0xff;
		Delayms(5);
		 
		DS1=1;DS2=0;DS3=1;DS4=1;
		P0=0xff-0x80;
		Delayms(5); //灭

		DS1=1;DS2=1;DS3=0;DS4=1;
		P0=LEDData2[Time[2]]-0x80;//第3个数码管，采用反码
		Delayms(5);

		DS1=1;DS2=1;DS3=1;DS4=0;TR1=0;
		P0=LEDData1[Time[3]]-0x80;
		Delayms(5);	TR1=1;
	} 
}

void TIME_Display4()//闹钟分钟调节模式，分钟两位闪烁，最后数码管小点亮
{
	uchar i;
	Time[0]=DateTime[2]/10; //小时十位
	Time[1]=DateTime[2]%10;	//小时个位
	Time[2]=DateTime[1]/10; //分钟十位
	Time[3]=DateTime[1]%10; //分钟个位 
	for(i=0;i<12;i++)
	{	
		DS1=0;DS2=1;DS3=1;DS4=1;
		P0=LEDData1[Time[0]];
		Delayms(5);
		 
		DS1=1;DS2=0;DS3=1;DS4=1;
		P0=LEDData1[Time[1]]-0x80;
		Delayms(5);

		DS1=1;DS2=1;DS3=0;DS4=1;
		P0=LEDData2[Time[2]]-0x80;//第3个数码管，采用反码
		Delayms(5);

		DS1=1;DS2=1;DS3=1;DS4=0;TR1=0;
		P0=LEDData1[Time[3]]-0x80;
		Delayms(5);	TR1=1;
	}
	for(i=0;i<6;i++)
	{	
		DS1=0;DS2=1;DS3=1;DS4=1;
		P0=LEDData1[Time[0]];
		Delayms(5);
		 
		DS1=1;DS2=0;DS3=1;DS4=1;
		P0=LEDData1[Time[1]]-0x80;
		Delayms(5);

		DS1=1;DS2=1;DS3=0;DS4=1;
		P0=0xff-0x80;//第3个数码管，采用反码
		Delayms(5);

		DS1=1;DS2=1;DS3=1;DS4=0;TR1=0;
		P0=0xff-0x80; //灭
		Delayms(5);	TR1=1;
	} 
}


void WD_Display()
{
	
	uchar a,b;
	a=T/1000;
	b=T%1000/100;
	TR1=0; //关闭T1
		DS1=0;DS2=1;DS3=1;DS4=1;
		P0=LEDData1[a];
		dot=1;	Delayms(5);
		 
		DS1=1;DS2=0;DS3=1;DS4=1;
		P0=LEDData1[b];
		Delayms(5);

		DS1=1;DS2=1;DS3=0;DS4=1;
		P0=0xf0;//第3个数码管，C的反码
		dot=0;
		Delayms(5);

		DS1=1;DS2=1;DS3=1;DS4=0;
		P0=0xff;
		dot=1;	Delayms(5);
	TR1=1;	
}


void Alart_Scan()
{
	if(alart && aM==DateTime[1] && aH==DateTime[2] && mode==0 && second==0)//检查闹钟
	{
			BUZZER=0;  //启动蜂鸣器
			Delayms(6000);
			BUZZER=1;  //停止蜂鸣器
			alart=0;   //取消闹钟
	}
    if(DateTime[2]>7 && DateTime[2]<23 && DateTime[1]==0 && DateTime[0]==0) //8：00～22：00整点报时
	{
		BUZZER=0;
		Delayms(3000);
		BUZZER=1;
	}
}

void Display()
{
	switch(mode)
	{
		case 4: //调节闹钟分钟
				TIME_Display4();
				break;
		case 3: //调节闹钟小时
				TIME_Display3();
				break;
		case 2: //调节 分钟
				TIME_Display2();
				break;
		case 1: //调节小时模式
				TIME_Display1();
				break;
		case 0://正常模式
				if((second>5 && second <10)||(second>35 && second <40))
					WD_Display(); 
				else
					TIME_Display0(); 
				break;
		}
}


void main()
{
 	mode = 0;
	alart=0;	k1push=0;
	BUZZER=1;	P3=200;

	TMOD=0x01; //T1方式0，T0方式1
	EA=1;ET1=1;ET0=1;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256; //50ms
	TH1=(8192-100)/32;
	TL1=(8192-100)%32; //0.1ms
	TR0=1;TR1=1;
	while(1)
	{
		Key_Scan();
		Alart_Scan();
		V_Scan();
		Display();
	}
}

void Timer0_INT() interrupt 1
{
	TR0=0;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	if(mode==0)
	{
		GetTime(DateTime);
		second=DateTime[0];
	}
	TR0=1; 
}

void Timer1_INT() interrupt 3
{
	static uint count=0;
	TR1=0;
	TH1=(8192-100)/32;
	TL1=(8192-100)%32; //0.1ms
	if(++count==10000)count=0;
	if((DS2==0||DS3==0) && count<6000 )dot=0;
	else dot=1;
	TR1=1;
}