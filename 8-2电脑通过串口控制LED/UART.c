#include <REGX52.H>
/**
  * @brief  ���ڳ�ʼ��  4800bps@11.0592MHz
  * @param  ��
  * @retval ��
  */
void UartInit(void)		
{
	PCON |= 0x80;		//ʹ�ܲ����ʱ���λSMOD
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xF4;		//�趨��ʱ��ֵ
	TH1 = 0xF4;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
	EA=1;
	ES=1;
}
/**
  * @brief  ���ڷ���һ���ֽ�����
  * @param  Byte��Ҫ���͵�һ���ֽ�����
  * @retval ��
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}

//�����жϺ���ģ��
//void UART_Routine() interrupt 4//4��ʾ�����ж�
//{
//	if(RI==1)//�ж�����ǽ����ж� ��Ϊ����(TI)Ҳ���ж�
//	{
//		///////////////P2=~SBUF;//SBUF�Ƕ�����������
//		///////////////UART_SendByte(SBUF);//д���ж����棬����ͬʱ��д��������
//		RI=0;
//	}
//}