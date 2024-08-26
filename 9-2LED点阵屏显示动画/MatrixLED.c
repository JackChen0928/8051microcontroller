#include <REGX52.H>
#include "Delay.h"

#define MATRIX_LED_PORT   P0

sbit RCK=P3^5;		//RCLK
sbit SCK=P3^6;		//SRCLK
sbit SER=P3^4;		//SER



/**
  * @brief  74HC595д��һ���ֽ�
  * @param  Ҫд����ֽ�
  * @retval ��
  */
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned int i;
	for(i=0;i<8;i++)
	{
			SER=Byte&(0x80>>i);//��������ǰ�Ҫд�������һλһλ�Ľ�ջ��0x80=1000 0000 ��Byte�еĵ�һλȡ������ʣ�¶���0,>>i����iλ�����ǰ�1������
			SCK=1;//��������λ ����1
			SCK=0;//��0 ���ر���������λ
	}
	RCK=1;//�������������棬��ջ������ݰᵽ
	RCK=0;//�ر�����������
}

/**
  * @brief  ��������ʼ��
  * @param  ��
  * @retval ��
  */
void MatrixLED_Init()
{
	SCK=0;
	RCK=0;
}


/**
  * @brief  LED��������ʾһ������
  * @param  Column Ҫѡ����У���Χ��0~7��0�������
  * @param  data��ʾ����ʾ�����ݣ���λ���ϣ�1����0��
  * @retval 
  */
void MatrixLED_ShowColumn(unsigned char Column,Data)//Column�ǵڼ��У�data�Ǵ��ϵ���1�ʹ�����0������
{
	_74HC595_WriteByte(Data);
	MATRIX_LED_PORT=~(0x80>>Column);//�൱��λѡ,Ҫ
	Delay(1);
	MATRIX_LED_PORT=0xFF;//0xFF==1111 1111  Ҫ��Ӱ
}
