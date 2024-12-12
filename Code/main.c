#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit K1 = P2^7;	//���Ű�ť
sbit SPK = P3^7;
uchar count;  //���Ŵ��� �����˴�
int t;  //�¶�
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

void t_to_str(int x,uchar *p)	 //���¶�����ת��Ϊ�ַ���
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

void s_to_str(uchar s, uchar *p) //���ٶ�����ת��Ϊ�ַ���
{
	uchar ws[2];
	s=count;  //��ȡ��������
	ws[0]=s/10;
	ws[1]=s%10;
	p[0]=' ';
	p[1]=ws[0]+'0';
	p[2]=ws[1]+'0';
	if(ws[0]==0)p[1]=' ';//ʮλΪ������ʾ
}

void KeyScan() //����ɨ��
{
	uchar i,j;
	if(K1 == 0)	 //����
	{
	 	while(K1 == 0);//�ȴ��ͷż�
		if(count++>99)count=0;
		TR0=1; //����T0
		for(i=0;i<2;i++)
	 		for(j=0;j<14;j++)
			{
		 		if(TR0==0)break; //�������ȷ�ϼ�������ǰ�˳�
				ShowString(0,1,"Someone knocking");
				sidx=Song[j];
				Delayms(300);
				ShowString(0,1,"                ");
			}
		TR0=0; //ֹͣT0
		if(SPK)SPK=0; //ȷ��SPKΪ�͵�ƽ��ʡ�� 
	}
}

void T_Scan() //�¶�ɨ�躯��
{
	t=Get_Temperature();
	if(t==0)t=Get_Temperature();
	if(t==0)t=Get_Temperature();

}

void Display() //LCD1602��ʾ����
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
	IE=0x82;  //��EA��ET0
	TMOD=0x00; //T0�����ڷ�ʽ0	
	EX0=1; //���ⲿ�ж�0
	IT0=1; //���䴥����ʽ
	TR0=0; //ֹͣT0

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
		KeyScan(); //ɨ�谴��
		T_Scan();  //ɨ���¶�
		Display(); //��ʾ
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
	if(TR0)TR0=0; //ֹͣT0��ֹͣ������
	if(count)count=0; //���ʴ�������
}



