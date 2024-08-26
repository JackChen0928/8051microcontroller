#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"


void main()
{
	LCD_Init();//��LCDģ���ʼ��
	DS1302_Init();//��DS1302оƬ��ʼ��
	LCD_ShowString(1,1,"  -  -  ");//LCD����ʾ����֮��ķ���
	LCD_ShowString(2,1,"  :  :  ");//LCD����ʾʱ��֮��ķ���
	
	DS1302_SetTime();//����һ����ʼʱ��
	
	while(1)
	{
		DS1302_ReadTime();//����ͨ��оƬ������ʱ��
		LCD_ShowNum(1,1,DS1302_TIME[0],2);//��LCD����ʾͨ��оƬ������ʱ��
		LCD_ShowNum(1,4,DS1302_TIME[1],2);
		LCD_ShowNum(1,7,DS1302_TIME[2],2);
		LCD_ShowNum(2,1,DS1302_TIME[3],2);
		LCD_ShowNum(2,4,DS1302_TIME[4],2);
		LCD_ShowNum(2,7,DS1302_TIME[5],2);

	
	}
}