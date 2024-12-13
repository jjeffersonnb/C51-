//LEDģ�⽻ͨ��
//˵�����������̵���������󣬻Ƶ���˸5�κ�������
//��������ϱ����ɺ�Ʊ�Ϊ�̵ƣ��̵�����������ϱ���Ƶ���˸��
//��˸5�κ�����ƣ��������̵���������ظ���
#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit RED_A=P0^0;   //������ָʾ��
sbit YELLOW_A=P0^1;
sbit GREEN_A=P0^2;
sbit RED_B=P0^3;   //�ϱ���ָʾ��
sbit YELLOW_B=P0^4;
sbit GREEN_B=P0^5;

uchar Flash_Count = 0;	//��˸����
uchar Operation_Type = 1;		//�������ͱ���

void DelayMS(uint x)	//��ʱ����
{
 	uchar t;
	while(x--)
	{
	 	for(t=120;t>0;t--);
	}
}

void Traffic_lignt()  //��ͨ���л��ӳ���
{
 	switch(Operation_Type)
	{
	 	case 1:	//�������̵����ϱ�������
			RED_A=1;YELLOW_A=1;GREEN_A=0;
			RED_B=0;YELLOW_B=1;GREEN_B=1;
			DelayMS(2000);
			Operation_Type = 2; //��һ����
			break;
		case 2:	 //������Ƶƿ�ʼ��˸���̵ƹر�
			DelayMS(200);
			YELLOW_A=~YELLOW_A;
			if(++Flash_Count !=10) 
				return;
			Flash_Count=0;
			Operation_Type = 3;	//��һ����
			break;
		case 3:	  //�����������ϱ����̵���
			RED_A=0;YELLOW_A=1;GREEN_A=1;
			RED_B=1;YELLOW_B=1;GREEN_B=0;
			DelayMS(2000);
			Operation_Type = 4;	 //��һ����
			break;	
		case 4:	   //�ϱ���Ƶƿ�ʼ��˸
			DelayMS(200);
			YELLOW_B=~YELLOW_B;
			if(++Flash_Count !=10) 
				return;
			Flash_Count=0;
			Operation_Type = 1;	//�ص���һ�ֲ���
			break;	
	}
}

void main()
{
 	while(1)
	{
	 	Traffic_lignt();	
	}
}
