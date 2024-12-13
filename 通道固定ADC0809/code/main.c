#include<reg51.h>
sbit CLOCK=P1^4;
sbit START=P1^5;
sbit EOC=P1^6;
sbit OE=P1^7;
unsigned char adcbuf;			//定义变量存放A/D转换结果
void ADC0809( )					//A/D转换子程序
{
			START=0;
			START=1;			//启动AD转换
			while(!EOC);		//等待转换结束
			START=0;
			OE=1;				//打开三态输出锁存器
			P2=0xff;			// P2口读数前先写1，确保读数准确
			adcbuf=P2;			//读P2口数据到存储变量
}

int main()
{
	TMOD = 0x02;  				//T0工作在方式2
	TH0  = 256-5;
	TL0  = 256-5; 				//定时5us，ADC0809时钟100KHz
	IE   = 0x82;
	TR0  = 1;
	while(1)
	{
		ADC0809();
		P0=P2;				   //采集的电压值送至P0口显示
	}
}
	
void Timer0_INT() interrupt 1	//T0的定时中断服务函数
{
 	    CLOCK = !CLOCK;   		//ADC0809时钟信号
}
