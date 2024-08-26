#include <REGX52.H>
#include "Delay.h"
#include "INTRINS.H"

//�������˿�
sbit Buzzer=P2^5;//�ѷ������ĵ�ַѡ�ã�����ԭ��ͼ�ó�


/**
  * @brief  ������˽���ӳٺ�������ʱ500΢��
  * @param  ��
  * @retval ��
  */
void Buzzer_Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}

/**
  * @brief  ����������
  * @param  ms ������ʱ��
  * @retval ��
  */

void Buzzer_Time(unsigned int ms)
{
			unsigned int i;
			for(i=0;i<ms*2;i++)//��ms����
			{
					Buzzer=!Buzzer;//��ת��������,��תһ�β���
					Buzzer_Delay500us();//ÿ��500΢�뷭תһ�Σ�һ��һ��Ϊһ�����ڵó�������1���룬Ƶ����1000hz
					//Delay(1);//ÿ��һ���뷭תһ�Σ�һ��һ��Ϊһ�����ڵó������������룬Ƶ����500hz
			}
}