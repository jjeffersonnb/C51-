#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char

sbit KEY1=P2^0;
sbit KEY2=P2^1;
int num;
uchar code table[]={0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};

void KeyScan();
void Display();
void DelayMS(uint x);

void main()
{
  	num=0;
  	while(1)
  	{
      	KeyScan();	   //扫描按键
	  	Display();	   //显示
  	}
}

void DelayMS(uint x)		 //延时子程序
{
 	uint i;
	while(x--)
	{ 
		for(i=0;i<120;i++);
	}
}

void KeyScan()			//按键扫描子程序
{
	if(KEY1==0)		   //如果减1键按下
	{
     	DelayMS(10);	   //延时防抖
	 	if(KEY1==0)	   //真按下
	 	{
	     	while(!KEY1);  //等待释放
			num--;
		 	if(num==-1)num=9;			
	 	}
	}

	if(KEY2==0)		//如果加1键按下
	{
     	DelayMS(10);
	 	if(KEY2==0);
	 	{ 
	   		while(!KEY2);
			num++;
	   		if(num==10)num=0;
	 	}
	}
}

void display()
{
	P1=table[num];
	DelayMS(5);
}