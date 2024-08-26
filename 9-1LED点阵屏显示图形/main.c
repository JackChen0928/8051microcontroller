#include <REGX52.H>
#include "Delay.h"
sbit RCK=P3^5;		//RCLK
sbit SCK=P3^6;		//SRCLK
sbit SER=P3^4;		//SER

#define MATRIX_LEC_PORT P0;


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
  * @brief  LED��������ʾһ������
  * @param  Column Ҫѡ����У���Χ��0~7��0�������
  * @param  data��ʾ����ʾ�����ݣ���λ���ϣ�1����0��
  * @retval 
  */
void MatrixLED_ShowColumn(unsigned char Column,Data)//Column�ǵڼ��У�data�Ǵ��ϵ���1�ʹ�����0������
{
	_74HC595_WriteByte(Data);
	MATRIX_LEC_PORT=~(0x80>>Column);//�൱��λѡ,Ҫ
	Delay(1);
	MATRIX_LEC_PORT=0xFF;//0xFF==1111 1111  Ҫ��Ӱ
}

void main()
{
	SCK=0;
	RCK=0;
	while(1)
	{
				MatrixLED_ShowColumn(0,0x3C);
				MatrixLED_ShowColumn(1,0x42);
				MatrixLED_ShowColumn(2,0xA9);
				MatrixLED_ShowColumn(3,0x85);
				MatrixLED_ShowColumn(4,0x85);
				MatrixLED_ShowColumn(5,0xA9);
				MatrixLED_ShowColumn(6,0x42);
				MatrixLED_ShowColumn(7,0x3C);
	}
}