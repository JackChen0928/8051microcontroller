#include <REGX52.H>
#include "I2C.h"

#define AT24C52_ADDRESS 0xA0

/**
  * @brief  AT24C52写入一个字节
  * @param  WordAddress要写入字节的地址
	 * @param  Data要写入字节的数据
  * @retval 
  */

void AT24C02_WriteByte(unsigned char WordAddress,Data)//根据AT24C02数据帧的流程来确定
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
  * @brief  AT24C52读取一个字节
  * @param  WordAddress要读出字节的地址
  * @retval 读出的数据
  */

unsigned char AT24C02_ReadByte(unsigned char WordAddress)//根据AT24C02数据帧的流程来确定
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
	I2C_SendAck(1);//不应答
	I2C_Stop();
	return Data;
}
