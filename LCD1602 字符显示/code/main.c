/***************   writer:shopping.w   ******************/
#include <reg52.h>
#include <string.h>
#define uchar unsigned char
#define uint unsigned int
void Initialize_LCD();
void ShowString(uchar,uchar,uchar *);
sbit K1 = P3^0;
sbit K2 = P3^1;
sbit K3 = P3^2;
uchar code Prompt[]="PRESS K1--K3 TO START DEMO PROG"; 
void main()
{
	Initialize_LCD();
	ShowString(0,0,Prompt);
	ShowString(0,1,Prompt+16);
	while(1)
	{
	 	if(K1 == 0)
		{
		 	Initialize_LCD();
			ShowString(0,0,"You are pressing");
			ShowString(6,1,"Key 1     ");
			while(K1==0);
			Initialize_LCD();
			ShowString(0,0,Prompt);
			ShowString(0,1,Prompt+16);
			
		}
		if(K2 == 0)
		{
		 	Initialize_LCD();
			ShowString(0,0,"You are pressing");
			ShowString(6,1,"Key 2     ");
			while(K2==0);
			Initialize_LCD();
			ShowString(0,0,Prompt);
			ShowString(0,1,Prompt+16);
		}
		if(K3 == 0)
		{
		 	Initialize_LCD();
			ShowString(0,0,"You are pressing");
			ShowString(6,1,"Key 3     ");
			while(K3==0);
			Initialize_LCD();
			ShowString(0,0,Prompt);
			ShowString(0,1,Prompt+16);
			
		}

	}
}