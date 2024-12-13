#include <reg52.h>    	//52系列单片机头文件
#include <absacc.h>    	//外部内存访问头文件
#include <math.h>
#define uchar unsigned char
#define uint unsigned int 
#define DAC XBYTE[0x7fff] //DAC0832的地址

uchar KeyNo;  //按键号

void delayms(uint t)				
{
	uchar i;
	while(t--) 
		for(i=0;i<12;i++);	  //即延时约0.t毫秒
}

void fangbo()	//方波
{
	DAC=0x00;
	delayms(20);
	DAC=0xff;
	delayms(20);
}

void juchibo()	//锯齿波
{
 	uchar value = 0xff; 
	while(value > 0x00)
		DAC=value--;
}

void sanjiaobo()   //三角波
{
	uchar value = 0x00;
	while(value < 0xff)
		DAC=value++;
	while(value > 0x00)
		DAC=value--;
}

void tixingbao()   //梯形波
{
	uchar value = 150;
	while(value > 0)
 		DAC=value--;
	delayms(30);
	while(value < 150)
 		DAC=value++;
	delayms(30);
}

void zhengxianbo()	  //正弦波
{
	uchar i;
	for(i=0;i<200;i++)
		DAC=125*sin(0.0314*i)+125;	
}

void main()
{
	KeyNo=0;   //初值为0，表示没有按键
	IT0=1; EA=1; EX0=1;
	while(1) 
	{
		if(KeyNo==1)fangbo();
        if(KeyNo==2)juchibo();
        if(KeyNo==3)sanjiaobo();
        if(KeyNo==4)tixingbao();
		if(KeyNo==5)zhengxianbo();
	}
}

void INT_EX0() interrupt 0
{
	if(++KeyNo==6)KeyNo=1;
}	

