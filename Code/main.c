#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit K1 = P2^7;	//敲门按钮
sbit SPK = P3^7;
uchar count;  //敲门次数 访问人次
int t;  //温度
uchar sidx;

uchar code HI_LIST[] =
{
 	0,226,229,232,233,236,238,240,241,242,245,246,247,248
};
uchar code LO_LIST[] =
{
 	0,4,13,10,20,3,8,6,2,23,5,26,1,4,3
};
uchar code Song[] =
{
 	1,2,3,1,1,2,3,1,3,4,5,3,4,5
};	

void Initialize_LCD();
void ShowString(uchar x,uchar y,uchar *str);
void Delayms(uint);
uint Get_Temperature();	
uchar Init_DS18B20();

void t_to_str(int x,uchar *p)	 //将温度数据转换为字符串
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

void s_to_str(uchar s, uchar *p) //将速度数据转换为字符串
{
	uchar ws[2];
	s=count;  //获取访问人数
	ws[0]=s/10;
	ws[1]=s%10;
	p[0]=' ';
	p[1]=ws[0]+'0';
	p[2]=ws[1]+'0';
	if(ws[0]==0)p[1]=' ';//十位为零则不显示
}

void KeyScan() //按键扫描
{
	uchar i,j;
	if(K1 == 0)	 //敲门
	{
	 	while(K1 == 0);//等待释放键
		if(count++>99)count=0;
		TR0=1; //启动T0
		for(i=0;i<2;i++)
	 		for(j=0;j<14;j++)
			{
		 		if(TR0==0)break; //如果按了确认键，则提前退出
				ShowString(0,1,"Someone knocking");
				sidx=Song[j];
				Delayms(300);
				ShowString(0,1,"                ");
			}
		TR0=0; //停止T0
		if(SPK)SPK=0; //确保SPK为低电平，省电 
	}
}

void T_Scan() //温度扫描函数
{
	t=Get_Temperature();
	if(t==0)t=Get_Temperature();
	if(t==0)t=Get_Temperature();

}

void Display() //LCD1602显示函数
{
	uchar str1[16]="Tempure:";
	uchar str2[16]="Vistors:";
	t_to_str(t,str1+8);
	ShowString(0,0,str1);	
	s_to_str(count,str2+8); 
	ShowString(0,1,str2);	
}	

void main(void)
{
	SPK=0;
	IE=0x82;  //开EA和ET0
	TMOD=0x00; //T0工作在方式0	
	EX0=1; //开外部中断0
	IT0=1; //跳变触发方式
	TR0=0; //停止T0

	count = 0;
	Initialize_LCD();
	 
	ShowString(0,0,"System Starting ");
	ShowString(0,1,"Please wait.    ");
	Init_DS18B20();
	t=Get_Temperature();
	t=Get_Temperature();
	Delayms(3000); 

	while(1)
	{
		KeyScan(); //扫描按键
		T_Scan();  //扫描温度
		Display(); //显示
		Delayms(100);
	}
}


void T0_INT() interrupt 1
{
 	SPK=!SPK;
	TH0=HI_LIST[sidx];
	TL0=LO_LIST[sidx];
}

void EX0_INT() interrupt 0
{
	if(TR0)TR0=0; //停止T0，停止放音乐
	if(count)count=0; //访问次数清零
}



