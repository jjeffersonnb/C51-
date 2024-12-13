
#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

sbit BEEP = P3^0;
uchar KeyNO = -1; //�����ţ�-1��ʾ�ް���

//0~9��A~F������ܶ���
uchar code DSY_CODE[]=
{
 	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e
};
//������̰��������� 16������
uchar code KeyCodeTable[]=
{
  	0x11,0x12,0x14,0x18,0x21,0x22,0x24,0x28,0x41,0x42,0x44,0x48,0x81,0x82,0x84,0x88
};

uint code Tone_Delay_Table[]=
{	64021, 64103, 64260, 64400, 64524, 64580, 64684, 64777,
	64820, 64898, 64968, 65030, 65058, 65110, 65157, 65178 };

void DelayMS(uint ms)  //��ʱ
{
 	uchar t;
	while(ms--)
	{
	 	for(t=0;t<120;t++);
	}
}


uchar Keys_Scan()   //�������ɨ��
{
 	uchar sCode,kCode,i,k;
	P1 = 0xf0;  //ȫ��ɨ��
	if(P1!=0xf0)  //�м�����
	{
	 	DelayMS(5);  //��ʱ����
		if(P1!=0xf0)  //���м�����
		{
		 	sCode = 0xfe;  //ɨ���0��
			for(k=0;k<4;k++)  //ɨ����
			{
			 	P1 = sCode;
				if((P1 & 0xf0)!=0xf0) // �ڱ���
				{
				 	kCode = ~P1; 
					for(i=0;i<16;i++) //�Ҽ���
					{
					 	if(kCode == KeyCodeTable[i])
						return i; //���ذ�����
					}
				}
				else 
					sCode = _crol_(sCode,1); //ɨ����һ��
			}
		}
	}
	return -1;
}

void Play_Tone() interrupt 1
{
	TH0	= Tone_Delay_Table[KeyNO] / 256;
	TL0 = Tone_Delay_Table[KeyNO] % 256;
	BEEP = ~BEEP;
}

void main()
{
	P0= 0xBF;
	TMOD = 0x01;
	IE = 0x82;	 
	while(1)
	{
	 	KeyNO = Keys_Scan(); //ɨ�����
		if(KeyNO!= -1)   //�м�����
		{
		 	P0 = ~DSY_CODE[KeyNO];
			TR0 =1 ;			
		}
		else
			TR0 = 0;
		DelayMS(2);
	}
}