#include <reg52.h>    	//52ϵ�е�Ƭ��ͷ�ļ�
#include <absacc.h>    	//�ⲿ�ڴ����ͷ�ļ�
#include <math.h>
#define uchar unsigned char
#define uint unsigned int 
#define DAC XBYTE[0x7fff] //DAC0832�ĵ�ַ

uchar KeyNo;  //������

void delayms(uint t)				
{
	uchar i;
	while(t--) 
		for(i=0;i<12;i++);	  //����ʱԼ0.t����
}

void fangbo()	//����
{
	DAC=0x00;
	delayms(20);
	DAC=0xff;
	delayms(20);
}

void juchibo()	//��ݲ�
{
 	uchar value = 0xff; 
	while(value > 0x00)
		DAC=value--;
}

void sanjiaobo()   //���ǲ�
{
	uchar value = 0x00;
	while(value < 0xff)
		DAC=value++;
	while(value > 0x00)
		DAC=value--;
}

void tixingbao()   //���β�
{
	uchar value = 150;
	while(value > 0)
 		DAC=value--;
	delayms(30);
	while(value < 150)
 		DAC=value++;
	delayms(30);
}

void zhengxianbo()	  //���Ҳ�
{
	uchar i;
	for(i=0;i<200;i++)
		DAC=125*sin(0.0314*i)+125;	
}

void main()
{
	KeyNo=0;   //��ֵΪ0����ʾû�а���
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

