#include <REGX52.H>
#include "I2C.h"

#define AT24C52_ADDRESS 0xA0

/**
  * @brief  AT24C52д��һ���ֽ�
  * @param  WordAddressҪд���ֽڵĵ�ַ
	 * @param  DataҪд���ֽڵ�����
  * @retval 
  */

void AT24C02_WriteByte(unsigned char WordAddress,Data)//����AT24C02����֡��������ȷ��
{
	I2C_Start();
	I2C_SendByte(AT24C52_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();
	
}

/**
  * @brief  AT24C52��ȡһ���ֽ�
  * @param  WordAddressҪ�����ֽڵĵ�ַ
  * @retval ����������
  */

unsigned char AT24C02_ReadByte(unsigned char WordAddress)//����AT24C02����֡��������ȷ��
{
	unsigned char Data;
	I2C_Start();
	I2C_SendByte(AT24C52_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	
	I2C_Start();
	I2C_SendByte(AT24C52_ADDRESS|0x01);
	I2C_ReceiveAck();
	Data=I2C_ReceiveByte();
	I2C_SendAck(1);//��Ӧ��
	I2C_Stop();
	return Data;
}
