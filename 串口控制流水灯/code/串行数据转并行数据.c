//��������ת�������ݣ�����8ֻLED����������2017.11.13
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

void Delay(uint x)	 //��ʱ�ӳ���
{
 	uchar i;
	while(x--)
	 	for(i=0;i<120;i++);
}

void main()
{
 	uchar c = 0x80;
	SCON = 0x00; //��ʽ0
	TI = 0;
	while(1)
	{
	 	c = _crol_(c,1); //c����һλ
		SBUF = c; while(TI==0);	TI = 0;	 //����c
		Delay(200);	 //��ʱ0.2��
	}
}