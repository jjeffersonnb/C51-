//���з�ʽ0����16ֻ��ˮ�ƹ���������2017.11.13
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
 	uchar i,c = 0x80;
	SCON = 0x00; //��ʽ0
	while(1)
	{ 	
		for(i=0;i<8;i++)
		{
			c = _crol_(c,1);  //c����һλ
			SBUF = c; while(TI==0);TI=0;   //����c
			SBUF = 0x00;while(TI==0);TI=0; //����0
			Delay(200);
		}
		for(i=0;i<8;i++)
		{
			c = _crol_(c,1);   //c����һλ
			SBUF = 0x00; while(TI==0); TI=0; //����0
			SBUF = c; while(TI==0);	TI=0; //����c
			Delay(200);
		} 
	 }
}