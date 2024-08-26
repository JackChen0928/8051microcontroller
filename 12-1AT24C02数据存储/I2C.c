#include <REGX52.H>
#include <INTRINS.H>

sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;

/**
  * @brief  I2C��ʼ
  * @param  ��
  * @retval ��
  */

void I2C_Start()//����I2C��ʱ��ṹͼ��ȷ����
{
		I2C_SDA=1;
		I2C_SCL=1;
		I2C_SDA=0;//��ʼ������SCL�ߵ�ƽ�ڼ䣬SDA�Ӹߵ�ƽ�л����͵�ƽ
		I2C_SCL=0;
}
/**
  * @brief  I2Cֹͣ
  * @param  ��
  * @retval ��
  */
void I2C_Stop()//����I2C��ʱ��ṹͼ��ȷ����
{
		I2C_SDA=0;
		I2C_SCL=1;
		I2C_SDA=1;//��ֹ������SCL�ߵ�ƽ�ڼ䣬SDA�ӵ͵�ƽ�л����ߵ�ƽ
}
/**
  * @brief  I2C����һ���ֽ�
  * @param  ��
  * @retval ��
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA=Byte&(0x80>>i);//���ΰ�����λ����SDA����
		I2C_SCL=1;//����SCL,�ӻ�����SCL�ߵ�ƽ�ڼ��ȡ����λ
		I2C_SCL=0;
	}
}
/**
  * @brief  I2C����һ���ֽ�
  * @param  ��
  * @retval ���յ����ֽ�����
  */
unsigned char I2C_ReceiveByte(void)
{
	unsigned char i,Byte=0x00;//�������յ�
	
	I2C_SDA=1;
	for(i=0;i<8;i++)
	{
		I2C_SCL=1;
		if(I2C_SDA){Byte|=(0x80>>i);}//���SDA��ȡ����1����ô��д��Byte��
		I2C_SCL=0;
	}
	return Byte;
}
/**
  * @brief  I2C����Ӧ��
  * @param  AckBitӦ��λ��0ΪӦ��1Ϊ��Ӧ��
  * @retval ��
  */
void I2C_SendAck(unsigned char AckBit)//����Ӧ��
{
		I2C_SDA=AckBit;//Ӧ��λ
		I2C_SCL=1;//���ߣ�����I2C��ʱ��ṹͼ
		I2C_SCL=0;//���ͣ�����I2C��ʱ��ṹͼ

}
/**
  * @brief  I2C����Ӧ��
  * @param 	��
  * @retval  ���յ���Ӧ��λ��0ΪӦ��1Ϊ��Ӧ��
  */
unsigned char I2C_ReceiveAck(void)//����Ӧ��
{
		unsigned char AckBit;//�洢���յ���Ӧ��
		I2C_SDA=1;
		I2C_SCL=1;
		AckBit=I2C_SDA;
		I2C_SCL=0;
		return AckBit;
}




