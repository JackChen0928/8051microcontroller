#include <REGX52.H>
#include "Delay.h"
#include "INTRINS.H"

//蜂鸣器端口
sbit Buzzer=P2^5;//把蜂鸣器的地址选好，根据原理图得出


/**
  * @brief  蜂鸣器私有延迟函数，延时500微秒
  * @param  无
  * @retval 无
  */
void Buzzer_Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}

/**
  * @brief  蜂鸣器发声
  * @param  ms 发声的时长
  * @retval 无
  */

void Buzzer_Time(unsigned int ms)
{
			unsigned int i;
			for(i=0;i<ms*2;i++)//响ms毫秒
			{
					Buzzer=!Buzzer;//翻转发出声音,翻转一次不行
					Buzzer_Delay500us();//每隔500微秒翻转一次，一正一反为一个周期得出周期是1毫秒，频率是1000hz
					//Delay(1);//每隔一毫秒翻转一次，一正一反为一个周期得出周期是两毫秒，频率是500hz
			}
}