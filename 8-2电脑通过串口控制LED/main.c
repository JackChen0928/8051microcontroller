#include <REGX52.H>
#include "Delay.h"
#include "UART.h"



void main()
{
	UartInit();
	
	while(1)
	{
		
	}
}

void UART_Routine() interrupt 4//4��ʾ�����ж�
{
	if(RI==1)//�ж�����ǽ����ж� ��Ϊ����(TI)Ҳ���ж�
	{
		P2=~SBUF;//SBUF�����ڴ���������д�ķ�����Ϣ  ��Ȼ�����������������
		UART_SendByte(SBUF);//���������������ַ��ͳ������ҽ��� ��    ����������д���ж����棬����ͬʱ��д��������
		RI=0;
	}
}