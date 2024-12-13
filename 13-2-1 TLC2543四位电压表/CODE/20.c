#include<reg52.h>
#include<intrins.h>
sbit CS=P3^5;
sbit CLK=P3^6;
sbit DIN=P3^4;
sbit DOUT=P3^3;
sbit DP  = P0^7;
unsigned char code LEDData[]=
{
 	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f
};
unsigned int tmp;
unsigned int vot; //���庯�����������Ϊ�����֣����Ϊת�����
void Display_Result(unsigned int d);

void DelayMS(unsigned int ms)
{
 	unsigned char i;
	while(ms--)
	{
	 	for(i=0;i<120;i++);
	}
}

unsigned int TLC2543(unsigned char command)
{
	unsigned char i;
	unsigned int result=0;
	CS=1;							
	CLK=0;
	CS=0;							//Ƭѡ��Ч
	for(i=0;i<12;i++)
	{
		DOUT=1;					//P3.3Ϊ�����
		result<<=1;					//result��������һλ
		result|=DOUT;				//DOUT���ϵ�����д��result�����λ��
		DIN=command&(0x80>>i);	//�������ְ�λ�ͳ�
		CLK=1;		
		nop_();						//�ߵ�ƽ����һ�����
		nop_();
		CLK=0;					
	}
	return  result;					//����ת�����
}

void main()
{	
	while(1)
	{		
		tmp=TLC2543(0x30);		//����TLC2543ת����ͨ��3��12λ�������
		vot=(int)tmp*(float)5000/4096;	//�������Ϊ��Ӧ�ĵ�ѹֵ
		Display_Result(vot);
	}
}

void Display_Result(unsigned int d)
{
 	unsigned char dis[4];
	dis[0]=d/1000;	  //ǧλ
	dis[1]=d/100%10;  //��λ
	dis[2]=(d%100)/10; //ʮλ
	dis[3]=d%10;  //��λ
	P2 = 0xf7; //�ұߵ�һλ	  1111 0111
	P0 = LEDData[dis[3]];
	DelayMS(3);
	P2 = 0xfb; //�ڶ�λ		  1111 1011
	P0 = LEDData[dis[2]];
	DelayMS(3);
	P2 = 0xfd; //����λ		  1111 1101
	P0 = LEDData[dis[1]] ;
	DelayMS(3);
	P2 = 0xfe; //����λ		  1111 1110
	P0 = LEDData[dis[0]] ;
	DP=1;	   //С�������
	DelayMS(3);
}

