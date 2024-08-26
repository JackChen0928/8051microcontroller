#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include <INTRINS.H>

unsigned char KeyNum,LEDMode;

void main()
{
	P2=0xFE;
	Timer0Init();
	while(1)
	{
		KeyNum=Key();
		if(KeyNum)
		{
			if(KeyNum==1)//只读取K1的按键
			{
					LEDMode++;
					if(LEDMode>=2)LEDMode=0;//控制LEDMode只有0和1
			}
		}
	}
}
void Timer0_Routine() interrupt 1
{
	  static unsigned int T0Count;
		TL0 = 0x66;		//设置定时初值
		TH0 = 0xFC;		//设置定时初值
		T0Count++;
		if(T0Count>=500)//500毫秒
		{
			T0Count=0;
			if(LEDMode==0)
					P2=_crol_(P2,1);//往左移一位，不用担心溢出
			if(LEDMode==1)
					P2=_cror_(P2,1);//往右移一位，不用担心溢出
		}
}