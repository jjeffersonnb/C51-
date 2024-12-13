#include<reg51.h>
sbit CLOCK=P1^4;
sbit START=P1^5;
sbit EOC=P1^6;
sbit OE=P1^7;
unsigned char adcbuf;			//����������A/Dת�����
void ADC0809( )					//A/Dת���ӳ���
{
			START=0;
			START=1;			//����ADת��
			while(!EOC);		//�ȴ�ת������
			START=0;
			OE=1;				//����̬���������
			P2=0xff;			// P2�ڶ���ǰ��д1��ȷ������׼ȷ
			adcbuf=P2;			//��P2�����ݵ��洢����
}

int main()
{
	TMOD = 0x02;  				//T0�����ڷ�ʽ2
	TH0  = 256-5;
	TL0  = 256-5; 				//��ʱ5us��ADC0809ʱ��100KHz
	IE   = 0x82;
	TR0  = 1;
	while(1)
	{
		ADC0809();
		P0=P2;				   //�ɼ��ĵ�ѹֵ����P0����ʾ
	}
}
	
void Timer0_INT() interrupt 1	//T0�Ķ�ʱ�жϷ�����
{
 	    CLOCK = !CLOCK;   		//ADC0809ʱ���ź�
}
