//��������ת��������
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
sbit SPL = P2^5;  //Shift and Load

void Delay(uint x)
{
 	uchar i;
	while(x--)
	{
	 	for(i=0;i<120;i++);
	}
}

void main()
{
 	SCON = 0x10;  //ģʽ0�����������
	while(1)
	{
	 	SPL = 0;	//������load�������벢�������8λ����
		SPL = 1;	//��λ��shift�����������뱻����������ת����ʼ
		while(RI == 0);	//�ȴ���������������
		RI = 0;
		P0 = SBUF;
		Delay(20);
	}
}