#include<reg51.h>
sbit INT_1=P1^0;
sbit LED1=P1^1;
sbit INT_2=P1^2;
sbit LED2=P1^3;
sbit INT_3=P1^4;
sbit LED3=P1^5;
sbit INT_4=P1^6;
sbit LED4=P1^7;
void  main()
{
	P1=0x55;		//P1.0,P1.2,P1.4,P1.6Ϊ���룬�����������
	EX0=1;			//�����ⲿ�ж�0�ж�
	IT0=1;			//ѡ����ش�����ʽ
	EA=1;			//CPU���ж�
	while (1);		//�ȴ��ж�
}
void int0_server( ) interrupt 0
{	
	P1=0x55;
	if (INT_1) LED1=0;		//����1Ϊ�ߵ�ƽ����LED1����
	if (INT_2) LED2=0;
	if (INT_3) LED3=0;
	if (INT_4) LED4=0;
}
