			/***************   DS1302.C   ******************/
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

sbit IO = P1^5;	 //DS1302's I/O
sbit SCLK = P1^6;  //DS1302's clock
sbit RST = P1^7;   //DS1302's Reset


void Write_A_Byte_TO_DS1302(uchar x)
{
 	uchar i;
	for(i=0;i<8;i++)
	{
	 	IO=x&0x01;SCLK=1;SCLK=0;x>>=1;
	}
}

uchar Get_A_Byte_FROM_DS1302()
{
 	uchar i,b=0x00;
	for(i=0;i<8;i++)
	{
	 	b |= _crol_((uchar)IO,i);
		SCLK=1;SCLK=0;
	}
	return b/16*10+b%16; //返回BCD码
}

uchar Read_Data(uchar addr) //从DS1302指定位置读数据
{
 	uchar dat;
	RST = 0;SCLK=0;RST=1;
   	Write_A_Byte_TO_DS1302(addr);
	dat = Get_A_Byte_FROM_DS1302();
   	SCLK=1;RST=0;
	return dat;
}

void Write_DS1302(uchar addr,uchar dat)
{
	SCLK = 0; RST = 1;
	Write_A_Byte_TO_DS1302(addr);
	Write_A_Byte_TO_DS1302(dat);
	SCLK = 0; RST = 0;
}

void GetTime(uchar *DateTime )	//读取当前日期时间
{
 	uchar i,addr = 0x81;
	for(i=0;i<7;i++)
	{
	 	DateTime[i]=Read_Data(addr);addr+=2;
	}
}

void SET_DS1302(uchar *DateTime)
{
	uchar i;
	Write_DS1302(0x8E,0x00);//写控制位，取消保护
	for(i=1;i<7;i++)
		Write_DS1302(0x80+2*i,(DateTime[i]/10<<4)|(DateTime[i]%10));
	Write_DS1302(0x8E,0x80); //加保护 
}




