#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"


void main()
{
	LCD_Init();//把LCD模块初始化
	DS1302_Init();//把DS1302芯片初始化
	LCD_ShowString(1,1,"  -  -  ");//LCD中显示日期之间的符号
	LCD_ShowString(2,1,"  :  :  ");//LCD中显示时间之间的符号
	
	DS1302_SetTime();//设置一个初始时间
	
	while(1)
	{
		DS1302_ReadTime();//读出通过芯片计算后的时间
		LCD_ShowNum(1,1,DS1302_TIME[0],2);//在LCD中显示通过芯片计算后的时间
		LCD_ShowNum(1,4,DS1302_TIME[1],2);
		LCD_ShowNum(1,7,DS1302_TIME[2],2);
		LCD_ShowNum(2,1,DS1302_TIME[3],2);
		LCD_ShowNum(2,4,DS1302_TIME[4],2);
		LCD_ShowNum(2,7,DS1302_TIME[5],2);

	
	}
}