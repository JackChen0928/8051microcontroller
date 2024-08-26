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

void UART_Routine() interrupt 4//4表示串口中断
{
	if(RI==1)//判断如果是接收中断 因为发送(TI)也会中断
	{
		P2=~SBUF;//SBUF是我在串口助手中写的发送信息  ，然后机器读出来的数据
		UART_SendByte(SBUF);//将读出来的数据又发送出来让我接收 ，    这个函数如果写在中断里面，不能同时又写在主函数
		RI=0;
	}
}