#include <REGX52.H>

sbit LED=P2^0;//LED表示P2的第一个LED灯

void Delay(unsigned int t)
{
	while(t--);
}

void main()
{
	unsigned char Time,i;
	while(1)
	{
		//PWM原理，改变一个周期内，高电平和低电平的时间占比长短
			for(Time=0;Time<=100;Time++)
			{
				for(i=0;i<20;i++)
				{
					LED=0;//开灯
					Delay(Time);//延时开灯的时间
					LED=1;//关灯
					Delay(100-Time);//延时关灯的时间
				}
			}
			for(Time=100;Time>0;Time--)
			{
				for(i=0;i<20;i++)
				{
					LED=0;//开灯
					Delay(Time);//延时开灯的时间
					LED=1;//关灯
					Delay(100-Time);//延时关灯的时间
				}
			}
		}
}