#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"MatrixKey:");
		while(1)
		{
				KeyNum=MatrixKey();//先接受扫描回来的数字 然后存起来
				if(KeyNum)//如果数字不为0，必要的判断，不然进入下一个循环，MatrixKey函数会把keynum变成0；导致显示00
				{
					LCD_ShowNum(2,1,KeyNum,2);//在数码管上显示该数字
				}
		}


}