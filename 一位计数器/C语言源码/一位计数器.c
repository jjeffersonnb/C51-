#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char

sbit KEY1=P2^0;
sbit KEY2=P2^1;
int num;
uchar code table[]={0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};

void KeyScan();
void Display();
void DelayMS(uint x);

void main()
{
  	num=0;
  	while(1)
  	{
      	KeyScan();	   //ɨ�谴��
	  	Display();	   //��ʾ
  	}
}

void DelayMS(uint x)		 //��ʱ�ӳ���
{
 	uint i;
	while(x--)
	{ 
		for(i=0;i<120;i++);
	}
}

void KeyScan()			//����ɨ���ӳ���
{
	if(KEY1==0)		   //�����1������
	{
     	DelayMS(10);	   //��ʱ����
	 	if(KEY1==0)	   //�水��
	 	{
	     	while(!KEY1);  //�ȴ��ͷ�
			num--;
		 	if(num==-1)num=9;			
	 	}
	}

	if(KEY2==0)		//�����1������
	{
     	DelayMS(10);
	 	if(KEY2==0);
	 	{ 
	   		while(!KEY2);
			num++;
	   		if(num==10)num=0;
	 	}
	}
}

void display()
{
	P1=table[num];
	DelayMS(5);
}