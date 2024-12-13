#include <reg51.h>
#include <absacc.h>
#include <math.h>
#define DAC0832 XBYTE[0xfeff]
unsigned char flag=1;
void delay(unsigned int t)										/* 延时函数 */
{             
		while(t--); 
} 
void saw(void)																						/* 锯齿波发生函数 */
{                  
	unsigned char i; 
   for (i=0;i<250;i++)
	{
										DAC0832=i; 																//进行D/A转换
										delay(200);															//延时一段时间
	}
} 
void square(void)   																/* 方波发生函数 */ 
{             
	 DAC0832=0x00; 																			//输出低电平
   delay(40000); 																			//延时一段时间
   DAC0832=0xfe; 																			//输出高电平
   delay(40000); 																			//延时一段时间
} 
void sanjiao(void)																		/* 三角波发生函数 */
{                  
unsigned char i; 
   for (i=0;i<250;i++)
	{
			DAC0832=i; 																	//进行D/A转换
			        delay(100);																//延时一段时间
	}
   for (i=250;i>0;i--)
	{
			DAC0832=i; 			
			delay(100);
	}
} 
void zhengxian(void)																/* 正弦波发生函数 */
{                  
	unsigned char i; 
		 for (i=0;i<200;i++)
							DAC0832=125*sin(0.0314*i)+125; //计算函数值并进行转换
} 
void main()
 {
			EX0=1;																												//开外部中断0
			IT0=1; 																											//边沿触发
			EA=1; 
			while(1)																										//根据按键次数控制波形输出
		{ 
									if(flag==1)			
															square();
									if(flag==2)
															saw();
									if(flag==3)
															sanjiao();
									if(flag==4)
															zhengxian(); 
		}
}
void int0() interrupt 0														//外部中断0中断函数
{ 
			flag++;
			if(flag==5)
										flag=1;
}
