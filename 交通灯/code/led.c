//LED模拟交通灯
//说明：东西向绿灯亮若干秒后，黄灯闪烁5次后红灯亮，
//红灯亮后，南北向由红灯变为绿灯，绿灯亮若干秒后南北向黄灯闪烁，
//闪烁5次后亮红灯，东西向绿灯亮，如此重复。
#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit RED_A=P0^0;   //东西向指示灯
sbit YELLOW_A=P0^1;
sbit GREEN_A=P0^2;
sbit RED_B=P0^3;   //南北向指示灯
sbit YELLOW_B=P0^4;
sbit GREEN_B=P0^5;

uchar Flash_Count = 0;	//闪烁次数
uchar Operation_Type = 1;		//操作类型变量

void DelayMS(uint x)	//延时函数
{
 	uchar t;
	while(x--)
	{
	 	for(t=120;t>0;t--);
	}
}

void Traffic_lignt()  //交通灯切换子程序
{
 	switch(Operation_Type)
	{
	 	case 1:	//东西向绿灯与南北向红灯亮
			RED_A=1;YELLOW_A=1;GREEN_A=0;
			RED_B=0;YELLOW_B=1;GREEN_B=1;
			DelayMS(2000);
			Operation_Type = 2; //下一操作
			break;
		case 2:	 //东西向黄灯开始闪烁，绿灯关闭
			DelayMS(200);
			YELLOW_A=~YELLOW_A;
			if(++Flash_Count !=10) 
				return;
			Flash_Count=0;
			Operation_Type = 3;	//下一操作
			break;
		case 3:	  //东西向红灯与南北向绿灯亮
			RED_A=0;YELLOW_A=1;GREEN_A=1;
			RED_B=1;YELLOW_B=1;GREEN_B=0;
			DelayMS(2000);
			Operation_Type = 4;	 //下一操作
			break;	
		case 4:	   //南北向黄灯开始闪烁
			DelayMS(200);
			YELLOW_B=~YELLOW_B;
			if(++Flash_Count !=10) 
				return;
			Flash_Count=0;
			Operation_Type = 1;	//回到第一种操作
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
