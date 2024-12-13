#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table0[]=		  //������
     { 0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
	   0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
uchar code table2[]={0x01,0x02,0x04,0x08};	//λѡ��
uint count;
sbit K1=P1^0;				   //ʮλ��1��ť
sbit K2=P1^3;				   //��λ��1��ť
sbit K3=P1^6;				   //��ʱ��ʼ��ť
sbit BUZZER=P3^1;			   //������

void delayms(uint x)
{
	uchar t;
	while(x--)
		for(t=0;t<120;t++);
}

void display(uint temp)			//��ʾ�ӳ���
{
	uchar i,buf[4];
	buf[0]=temp/1000;			//����4λ��ֵ��ǧ���١�ʮ����λ
	buf[1]=temp%1000/100;
	buf[2]=temp%100/10;
	buf[3]=temp%10;
	for(i=0;i<4;i++)			//4λ������ʾ
	{
		P2=table2[i];			//��λѡ�ź�
		P0=table0[buf[i]];		//�Ͷ�ѡ�ź�
		delayms(5);				//��ʱһ��ʱ��
		P1=0xff;				//����
	}
}


void KeyScan()						//����ɨ�躯��
{									
	if(K1==0)						//ʮλ��1����
	{								
		while(K1==0);				//�ȴ��û��ͷŰ���
		TR0=0; BUZZER=1;			//�رն�ʱ���������
		if(count<=9999)count+=10;
	}
	if(K2==0)						//��λ��1����
	{
		while(K2==0);
		TR0=0; BUZZER=1;
		if(count<=9999)count+=1;
	}
	if(K3==0)						//��ʼ����
	{
		while(K3==0);
		if(count==0)
		{
			TR0=0; BUZZER=1;
		}
		else
			TR0=1;					//��ʱ��ʼ 
	}
}

void main()						   //������
{
	count = 0;					   //Ĭ�ϳ�ֵΪ0
	BUZZER = 1;					   //������Ĭ�ϲ���
	TMOD=0x01;					   //���ö�ʱ��T0������ʽΪģʽ0
	TH0=(65536-50000)/256;		   //��ʱ50ms
	TL0=(65536-50000)%256;		   //����ʱ��T0�ж�
	EA=1; ET0=1;
	while(1)
	{
		display(count);
		KeyScan();
	}
}
void timer0() interrupt 1			//��ʱ��T0�жϷ�����
{									
	static uchar temp=0;			//�ڲ���̬���������ڼ���
	TH0=(65536-50000)/256;			//��ʱ50ms
	TL0=(65536-50000)%256;
	if(++temp==20)					//20*50ms=1s����ʱ1���
	{
		if(count>0)
		{
			count--;				//count��1
			temp=0;
		}
		else
			BUZZER=0;			   //�򿪷�����	  		
	}
}


	
