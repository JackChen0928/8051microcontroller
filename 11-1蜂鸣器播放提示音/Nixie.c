#include <REGX52.H>
#include "Delay.h"

//���ڶ�ѡ ѡ��̬������е�LED����ʾʲô����
unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void Nixie(unsigned char Location,Number)//�ڼ���LED��,��ʾʲô���ֵĺ��� 
{
	//λѡ ѡ��̬���������һ��LED��
	switch(Location)
	{
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=NixieTable[Number];//��ѡ ѡ��LED����ʾʲô����
	Delay(1);//��Ӱ��λѡ ��ѡ��λѡ ��ѡ ��ѡ��λѡ֮�����ݻ���� ��Ҫ�Ѷ�ѡ��������������Ӱ�� 
	//P0=0x00;//��ʾ����

}