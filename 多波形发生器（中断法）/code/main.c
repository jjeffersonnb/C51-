#include <reg51.h>
#include <absacc.h>
#include <math.h>
#define DAC0832 XBYTE[0xfeff]
unsigned char flag=1;
void delay(unsigned int t)										/* ��ʱ���� */
{             
		while(t--); 
} 
void saw(void)																						/* ��ݲ��������� */
{                  
	unsigned char i; 
   for (i=0;i<250;i++)
	{
										DAC0832=i; 																//����D/Aת��
										delay(200);															//��ʱһ��ʱ��
	}
} 
void square(void)   																/* ������������ */ 
{             
	 DAC0832=0x00; 																			//����͵�ƽ
   delay(40000); 																			//��ʱһ��ʱ��
   DAC0832=0xfe; 																			//����ߵ�ƽ
   delay(40000); 																			//��ʱһ��ʱ��
} 
void sanjiao(void)																		/* ���ǲ��������� */
{                  
unsigned char i; 
   for (i=0;i<250;i++)
	{
			DAC0832=i; 																	//����D/Aת��
			        delay(100);																//��ʱһ��ʱ��
	}
   for (i=250;i>0;i--)
	{
			DAC0832=i; 			
			delay(100);
	}
} 
void zhengxian(void)																/* ���Ҳ��������� */
{                  
	unsigned char i; 
		 for (i=0;i<200;i++)
							DAC0832=125*sin(0.0314*i)+125; //���㺯��ֵ������ת��
} 
void main()
 {
			EX0=1;																												//���ⲿ�ж�0
			IT0=1; 																											//���ش���
			EA=1; 
			while(1)																										//���ݰ����������Ʋ������
		{ 
									if(flag==1)			
															square();
									if(flag==2)
															saw();
									if(flag==3)
															sanjiao();
									if(flag==4)
															zhengxian(); 
		}
}
void int0() interrupt 0														//�ⲿ�ж�0�жϺ���
{ 
			flag++;
			if(flag==5)
										flag=1;
}
