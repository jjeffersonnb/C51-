#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
#include <AT24C02.h>
uchar code table0[]=		  //������
                   { 0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
				     0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
uchar code table2[]={0x01,0x02,0x04,0x08};	//λѡ��
uint count;					   //������ֵ
sbit K1=P1^0;				   //��1��ť
sbit K2=P1^3;				   //��1��ť
sbit K3=P1^6;				   //���㰴ť

void write_add(uchar address,uchar date);   //����AT24C02.H�еĶ�д����
uchar read_add(uchar address);
void initeeprom();

void delayms(uint x)
{
	uchar t;
	while(x--)
		for(t=0;t<120;t++);
}

void AT24c_Read()  //��AT24C02����count����
{
	uchar a,b;
	a=read_add(0x00);  //��8λ
	delayms(10);
	b=read_add(0x01);  //��8λ
	count = a*256+b;
	delayms(10);
}

void AT24c_Write() //��countд��AT24C02
{
	uchar a,b;
	a=count/256;
	b=count%256;
	delayms(10);
	write_add(0x00,a);
	delayms(10);
	write_add(0x01,b);
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
	if(K1==0)						//��1����
	{								
		while(K1==0);				//�ȴ��û��ͷŰ���
		if(count<9999)count++;		//count��1
		AT24c_Write();			//��countд��AT24C02
	}
	if(K2==0)						//��1����
	{
		while(K2==0);
		if(count>0)count--;
		AT24c_Write();
	}
	if(K3==0)						//���㰴��
	{
		while(K3==0);
		if(count!=0)
		{
			count=0;
			AT24c_Write();
		}
	}
}

void main()						   //������
{
	initeeprom();	//��ȡ��ʼ����
	AT24c_Read();   //��AT24C02�ж���count��ֵ
	while(1)
	{
		display(count);
		KeyScan();
	}
}



	
