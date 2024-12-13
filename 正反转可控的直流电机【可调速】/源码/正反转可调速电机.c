/*  ����ת�ɵ��ٵ��ϵͳ 2014.12.3 */
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit K1 = P3^0;	//��ת��ť
sbit K2 = P3^1;	//��ת��ť
sbit K3 = P3^2;	//ֹͣ��ť
sbit K4 = P3^3;	//���ٰ�ť
sbit K5 = P3^4;	//���ٰ�ť
sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;
sbit MA   = P1^0; //A��
sbit MB   = P1^1; //B��

uchar DS; //DS������״̬ 0ֹͣ 1��ת 2��ת
uchar SPEED; //SPEED����ת�ټ���1��10
uchar count;  //PWMռ�ձȿ��� 0 �� 9

void zhengzhuan()  //��ת
{
	LED1 = 0;
	LED2 = 1;
	LED3 = 1;
	DS   = 1;
}
void fanzhuan()	 //��ת
{
	LED1 = 1;
	LED2 = 0;
	LED3 = 1;
	DS   = 2;
}
void stop()		 //ֹͣ
{
	LED1 = 1;
	LED2 = 1;
	LED3 = 0;
	DS   = 0;
}

void Key_Scan()
{
	 	if(K1 == 0)	 //��ת
		{
		 	while(K1 == 0);
			zhengzhuan();
		}
		if(K2 == 0)	 //��ת
		{
		 	while(K2 == 0);
			fanzhuan();
		}
		if(K3 == 0)	 //ֹͣ
		{
		 	while(K3 == 0);
			stop();
		}
		if(K4 == 0)	 //����
		{
			while(K4 == 0);
			if(SPEED<10)SPEED++;
		}
		if(K5 == 0)	 //����
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
	SPEED = 5; //��������
	count = 0;

	TMOD = 0x02; //T0 ��ʽ2 �Զ����س�ֵ
	TH0 = 256-100;
	TL0 = 256-100;  //��ʱ100΢��
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
		case 0:	MA = 1;  //ֹͣ
				MB = 1;
				break;
		case 1: MA = 0;	 //��ת
				if(count < SPEED)
					MB = 1;
				else
					MB = 0;
				break;
		case 2: MB = 0;	  //��ת
				if(count < SPEED)
					MA = 1;
				else
					MA = 0;
	}	
}
