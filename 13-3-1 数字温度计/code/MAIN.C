
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

void Initialize_LCD();
void ShowString(uchar x,uchar y,uchar *str);
void Delayms(uint);
uint Get_Temperature();	

void to_str(int x,uchar *p)
{
	uchar ws[4];
	uint t;
	if(x<0)
	{ p[0]='-'; t=x*(-1); }
	else
	{ p[0]=' '; t=x; }
	ws[3]=t/1000;
	ws[2]=t%1000/100;
	ws[1]=t%100/10;
	ws[0]=t%10;

	p[1]=ws[3]+'0';
	p[2]=ws[2]+'0';
	p[3]=ws[1]+'0';
	p[4]='.';
	p[5]=ws[0]+'0';
	p[6]=0xdf;
	p[7]='C';

	if(ws[3]==0)p[1]=' ';
	if(ws[3]==0 && ws[2]==0)p[2]=' ';
}

void main()
{
 	int t;
	uchar code str1[16]="  Current Temp: ";
	uchar temp[16]="                ";
	Initialize_LCD();
	ShowString(0,0,str1);
	while(1)
	{
		t=Get_Temperature();
		to_str(t,temp+4);
		ShowString(0,1,temp);
		Delayms(100);		
	}
}




