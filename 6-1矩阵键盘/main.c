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
				KeyNum=MatrixKey();//�Ƚ���ɨ����������� Ȼ�������
				if(KeyNum)//������ֲ�Ϊ0����Ҫ���жϣ���Ȼ������һ��ѭ����MatrixKey�������keynum���0��������ʾ00
				{
					LCD_ShowNum(2,1,KeyNum,2);//�����������ʾ������
				}
		}


}