#include <reg51.h>
sbit KEY = P1^0;
sbit BEEP = P2^0;
void main()
{
	BEEP = 1; //������Ĭ�ϲ���
	while(1)
	{
		BEEP = KEY;
	}
}