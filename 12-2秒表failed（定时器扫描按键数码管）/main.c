#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include "Nixie.h"
#include "Delay.h"

unsigned char KeyNum,Temp;

void Timer0_Init(void);

void main()
{
	Timer0_Init();
	while(1)
	{
		KeyNum=Key();
		if(KeyNum)Temp=KeyNum;
		Nixie(1,Temp);
		Delay(100);
	}
}


void Timer0_Routine() interrupt 1
{
	  static unsigned int T0Count;
		TL0 = 0x66;		//设置定时初值
		TH0 = 0xFC;		//设置定时初值
		T0Count++;
		if(T0Count>=20)
		{
			T0Count=0;
			Key_Loop();
		}
}