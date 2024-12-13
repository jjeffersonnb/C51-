/***************   writer:shopping.w   ******************/
#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
#define delayNOP() {_nop_();_nop_();_nop_();_nop_();}

sbit DQ = P3^3;
uchar Temp_Value[]={0x00,0x00};
bit DS18B20_IS_OK = 1;

void ShowString(uchar x,uchar y,uchar *str);
void Initialize_LCD();


void Delay(uint x)
{
 	while(--x);
}

uchar Init_DS18B20()
{
 	uchar status;
	DQ = 1;
	Delay(8);
	DQ = 0;
	Delay(90);
	DQ = 1;
	Delay(8);
	DQ = 1;
	return status;
}

uchar ReadOneByte()
{
 	uchar i,dat=0;
	DQ = 1;
	_nop_();
	for(i=0;i<8;i++)
	{
	 	DQ = 0;
		dat >>= 1;
		DQ = 1;
		_nop_();
		_nop_();
		if(DQ)
			dat |= 0X80;
		Delay(30);
		DQ = 1;
	}
	return dat;
}

void WriteOneByte(uchar dat)
{
 	uchar i;
	for(i=0;i<8;i++)
	{
	 	DQ = 0;
		DQ = dat& 0x01;
		Delay(5);
		DQ = 1;
		dat >>= 1;
	}
}

void Read_Temperature()
{
 	if(Init_DS18B20()==1)
		DS18B20_IS_OK=0;
	else
	{
		WriteOneByte(0xcc);
		WriteOneByte(0x44);
		Init_DS18B20();
		WriteOneByte(0xcc);
		WriteOneByte(0xbe);
		Temp_Value[0] = ReadOneByte(); 
		Temp_Value[1] = ReadOneByte();
		DS18B20_IS_OK=1;	
	}	
}

void main()
{
	Initialize_LCD();
	Read_Temperature();
	Delay(5000);		
	while(1)
	{
	 	Read_Temperature();
		if(DS18B20_IS_OK) 
		{	
			ShowString(0,0,Temp_Value);
		}
		Delay(5000);		
	}
}