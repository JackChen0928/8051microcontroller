#include <REGX52.H>
#include <INTRINS.H>

sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;

/**
  * @brief  I2C开始
  * @param  无
  * @retval 无
  */

void I2C_Start()//根据I2C的时序结构图来确定的
{
		I2C_SDA=1;
		I2C_SCL=1;
		I2C_SDA=0;//起始条件：SCL高电平期间，SDA从高电平切换到低电平
		I2C_SCL=0;
}
/**
  * @brief  I2C停止
  * @param  无
  * @retval 无
  */
void I2C_Stop()//根据I2C的时序结构图来确定的
{
		I2C_SDA=0;
		I2C_SCL=1;
		I2C_SDA=1;//终止条件：SCL高电平期间，SDA从低电平切换到高电平
}
/**
  * @brief  I2C发送一个字节
  * @param  无
  * @retval 无
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA=Byte&(0x80>>i);//依次把数据位放在SDA线上
		I2C_SCL=1;//拉高SCL,从机将在SCL高电平期间读取数据位
		I2C_SCL=0;
	}
}
/**
  * @brief  I2C接收一个字节
  * @param  无
  * @retval 接收到的字节数据
  */
unsigned char I2C_ReceiveByte(void)
{
	unsigned char i,Byte=0x00;//用来接收的
	
	I2C_SDA=1;
	for(i=0;i<8;i++)
	{
		I2C_SCL=1;
		if(I2C_SDA){Byte|=(0x80>>i);}//如果SDA读取到是1，那么就写入Byte中
		I2C_SCL=0;
	}
	return Byte;
}
/**
  * @brief  I2C发送应答
  * @param  AckBit应答位，0为应答，1为非应答
  * @retval 无
  */
void I2C_SendAck(unsigned char AckBit)//发送应答
{
		I2C_SDA=AckBit;//应答位
		I2C_SCL=1;//拉高，根据I2C的时序结构图
		I2C_SCL=0;//拉低，根据I2C的时序结构图

}
/**
  * @brief  I2C接收应答
  * @param 	无
  * @retval  接收到的应答位，0为应答，1为非应答
  */
unsigned char I2C_ReceiveAck(void)//接收应答
{
		unsigned char AckBit;//存储接收到的应答
		I2C_SDA=1;
		I2C_SCL=1;
		AckBit=I2C_SDA;
		I2C_SCL=0;
		return AckBit;
}




