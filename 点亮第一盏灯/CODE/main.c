#include <reg51.h>
sbit LED = P0^0;
sbit BUTTON = P2^7;
int main()
{
	LED = 1;
	while(1)
	{
		if(BUTTON==0) 			//�����ť��������
		{
			while(BUTTON==0); 	//�ȴ��û��ͷŰ�ť
			LED = !LED;
		}
	}
	return 0;
}
