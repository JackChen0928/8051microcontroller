#include <REGX52.H>
#include "Delay.h"

#define MATRIX_LED_PORT   P0

sbit RCK=P3^5;		//RCLK
sbit SCK=P3^6;		//SRCLK
sbit SER=P3^4;		//SER



/**
  * @brief  74HC595写入一个字节
  * @param  要写入的字节
  * @retval 无
  */
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned int i;
	for(i=0;i<8;i++)
	{
			SER=Byte&(0x80>>i);//这个步骤是把要写入的数据一位一位的进栈，0x80=1000 0000 把Byte中的第一位取出来，剩下都是0,>>i向右i位，就是把1向右移
			SCK=1;//上升沿移位 ，置1
			SCK=0;//置0 ，关闭上升沿移位
	}
	RCK=1;//开启上升沿锁存，把栈里的数据搬到
	RCK=0;//关闭上升沿锁存
}

/**
  * @brief  点阵屏初始化
  * @param  无
  * @retval 无
  */
void MatrixLED_Init()
{
	SCK=0;
	RCK=0;
}


/**
  * @brief  LED点阵屏显示一列数据
  * @param  Column 要选择的列，范围：0~7，0在最左边
  * @param  data显示列显示的数据，高位在上，1亮，0灭
  * @retval 
  */
void MatrixLED_ShowColumn(unsigned char Column,Data)//Column是第几列，data是从上到下1就代表亮0代表不亮
{
	_74HC595_WriteByte(Data);
	MATRIX_LED_PORT=~(0x80>>Column);//相当于位选,要
	Delay(1);
	MATRIX_LED_PORT=0xFF;//0xFF==1111 1111  要消影
}
