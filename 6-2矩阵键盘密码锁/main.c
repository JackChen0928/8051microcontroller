#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum;
unsigned int Password,Count;//��������Ͷ�ȡ����

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
		while(1)
		{
				KeyNum=MatrixKey();//�Ƚ���ɨ����������� Ȼ�������
				if(KeyNum)//������ֲ�Ϊ0����Ҫ���жϣ���Ȼ������һ��ѭ����MatrixKey�������keynum���0��������ʾ00
				{
					if(KeyNum<=10)//���s1-s10��������ʾ1 2 3 4 5 6 7 8 9 0�����£���������
					{
							if(Count<4)//�����ĸ����ֲŶ��룬���µ�������־Ͳ�����
							{
								Password*=10;//��������һλ�����ǵ���������λ�������Ƕ�ȡ��ʱ����һλһλ�Ķ�ȡ���������Ʊ���
								Password+=KeyNum%10;//�����Ҫ����KeyNum=10��ʱ�� ��10ת����0�� Ҳ�ǻ�ȡһλ����
							}
							Count++;//�ƴμ�һ
					}	
					
					
					//��һ����� ���s11-s16���� ��ʾ11-16 �Ǿ�password����������LCDҲ�Ͳ�����ʾ����
					
					
					if(KeyNum==11)//��s11����������ȷ�ϰ���
					{
						if(Password==2345)//��ȷ������
						{
							LCD_ShowString(1,14,"OK ");//������ȷ����ʾOK
							Password=0;//��������
							Count=0;//�ƴ�����
							LCD_ShowNum(2,1,Password,4);//��ʾ����
						}
						else
						{
							LCD_ShowString(1,14,"ERR");//������ʾERR
							Password=0;//��������
							Count=0;//�ƴ�����
							LCD_ShowNum(2,1,Password,4);//��ʾ����
						}
						
						
					}
					if(KeyNum==12)//��s12����������ȡ������
					{
						
							Password=0;//��������
							Count=0;//�ƴ�����
							LCD_ShowNum(2,1,Password,4);//��ʾ����
					
					}
					
					LCD_ShowNum(2,1,Password,4);//�����������ʾ�����֣�password��
				}
		}


}