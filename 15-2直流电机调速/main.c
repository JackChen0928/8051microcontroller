#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Nixie.h"
#include "Timer0.h"

sbit Motor=P1^0;

unsigned char Counter,Compare;
unsigned char KeyNum,Speed;

void main()
{
	Timer0Init();
	Compare=5;
	while(1)
	{
		KeyNum=Key();
		if(KeyNum==1)
		{
			Speed++;
			Speed%=4;
			if(Speed==0){Compare=0;}
			if(Speed==1){Compare=5;}//Compare��ʾ���ƣ�/��ת����ʱ��ռ�ȣ�Ҳ�������ɿ��ƣ�/��ת�������ȣ�/�ٶȣ�
			if(Speed==2){Compare=50;}
			if(Speed==3){Compare=100;}
		}
		Nixie(1,Speed);
	}
}

void Timer0_Routine() interrupt 1
{
	TL0 = 0xA4;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	Counter++;
	Counter%=100;
	if(Counter<Compare)
	{
		Motor=1;//Compare��ֵ���ʱ�䣬���ƣ�0�ǿ��ƣ�/��ת��1����ת��
	}
	else
	{
		Motor=0;
	}
}