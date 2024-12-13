#include<reg52.h>
#include<intrins.h>
#define uint unsigned int 
#define uchar unsigned char 
sbit ADout=P1^0;
sbit ADin=P1^1;
sbit CS=P1^2;
sbit CLK=P1^3;
sbit EOC=P1^4;

uint readAD(uchar port)				   
{
 	uchar ch,i,j;
	uint ad;
	ch=port;
	for(j=0;j<3;j++)			//循环三次，确保转换数据准确
	{	
		ad=0;
		ch=port;
		EOC=1;
		CS=1;
		CS=0;
		CLK=0;
		for(i=0;i<10;i++)  //TLC2543可改为12
		{
			if(ADout) ad|=0x01;
			ADin=(bit)(ch&0x80);	
			CLK=1;
			CLK=0;
			ch<<=1;
			ad<<=1;
		}
	}
	CS=1;								   /////////转换和读取数值
	while(!EOC);
	ad>>=1;
	return(ad);
}
