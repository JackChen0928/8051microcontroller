#include <REGX52.H>
/**
  * @brief  串口初始化  4800bps@11.0592MHz
  * @param  无
  * @retval 无
  */
void UartInit(void)		
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xF4;		//设定定时初值
	TH1 = 0xF4;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA=1;
	ES=1;
}
/**
  * @brief  串口发送一个字节数据
  * @param  Byte是要发送的一个字节数据
  * @retval 无
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}

//串口中断函数模板
//void UART_Routine() interrupt 4//4表示串口中断
//{
//	if(RI==1)//判断如果是接受中断 因为发送(TI)也会中断
//	{
//		///////////////P2=~SBUF;//SBUF是读出来的数据
//		///////////////UART_SendByte(SBUF);//写在中断里面，不能同时又写在主函数
//		RI=0;
//	}
//}