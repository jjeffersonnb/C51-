#include <reg51.h>
sbit LED = P0^0;
sbit BUTTON = P2^7;
int main()
{
	LED = 1;
	while(1)
	{
		if(BUTTON==0) 			//如果按钮被按下了
		{
			while(BUTTON==0); 	//等待用户释放按钮
			LED = !LED;
		}
	}
	return 0;
}
