#include <REGX52.H>

sbit LED=P2^0;//LED��ʾP2�ĵ�һ��LED��

void Delay(unsigned int t)
{
	while(t--);
}

void main()
{
	unsigned char Time,i;
	while(1)
	{
		//PWMԭ���ı�һ�������ڣ��ߵ�ƽ�͵͵�ƽ��ʱ��ռ�ȳ���
			for(Time=0;Time<=100;Time++)
			{
				for(i=0;i<20;i++)
				{
					LED=0;//����
					Delay(Time);//��ʱ���Ƶ�ʱ��
					LED=1;//�ص�
					Delay(100-Time);//��ʱ�صƵ�ʱ��
				}
			}
			for(Time=100;Time>0;Time--)
			{
				for(i=0;i<20;i++)
				{
					LED=0;//����
					Delay(Time);//��ʱ���Ƶ�ʱ��
					LED=1;//�ص�
					Delay(100-Time);//��ʱ�صƵ�ʱ��
				}
			}
		}
}