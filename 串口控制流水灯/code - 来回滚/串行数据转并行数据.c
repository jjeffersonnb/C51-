//��������ת�������ݣ�����8ֻLED���ع�������, 2017.11.13
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

void Delay(uint x) //��ʱ�ӳ���
{
 	uchar i;
	while(x--)
		for(i=0;i<120;i++);
}

void main()
{
 	uchar i,c = 0x01;
	SCON = 0x00; //��ʽ0
	SBUF = c;while(TI==0);TI = 0; //����c
	Delay(200);
	while(1)
	{
	 	for(i=0;i<7;i++)
		{
			c = _crol_(c,1);  //c����һλ
			SBUF = c;while(TI==0);TI = 0; //����c
		    Delay(200);	//��ʱ0.2��
		}
		for(i=0;i<7;i++)
		{
			c = _cror_(c,1);  //c����һλ
			SBUF = c;while(TI==0);TI = 0; //����c
		    Delay(200);	//��ʱ0.2��
		}

	}
}