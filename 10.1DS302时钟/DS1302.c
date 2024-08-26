#include <REGX52.H>

sbit DS1302_SCLK=P3^6;//^��ʾ��ַ
sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;

//�궨��  �������   оƬ�е�һ����ַ����һ��ʱ������
#define DS1302_SECOND  0x80
#define DS1302_MINUTE  0x82
#define DS1302_HOUR  0x84
#define DS1302_DATE  0x86
#define DS1302_MONTH  0x88
#define DS1302_DAY		0x8A
#define DS1302_YEAR  0x8C
#define DS1302_WP  0x8E


unsigned char DS1302_TIME[]={19,11,16,12,59,55,6};

void DS1302_Init(void)
{
	DS1302_CE=0;//��ʼ����0
	DS1302_SCLK=0;//��ʼ����0
}

/**
  * @brief  ������д��оƬ�Ĳ���
  * @param  Command����������ݣ�������д�뻹�Ƕ�ȡ�ȵȣ�Data��д�������
  * @retval ��
  */
void DS1302_WriteByte(unsigned char Command,Data)
{
		unsigned char i;
		DS1302_CE=1;//��CE��1�����ݵ����ֽڵ�ʱ����ͼ��ȷ������
	//д�����������
	for(i=0;i<8;i++)
	{
		//����ʱ����ͼ��DS1302��д������ǣ�һ��SCLK���� ��һλ����������SCLK�����ض���һλ
		DS1302_IO=Command&(0x01<<i);//����ѭ��ȡ����0-��7λд��IO�ڣ���оƬ֪������Ҫ��ʲô������0x01=0000 0001 �൱��ֻ���µ�0λ����1-��7λ����0 
		DS1302_SCLK=1;//��SCLK��1��SCLK�����ض���һλ������ʱ����ͼ��ȷ������
		DS1302_SCLK=0;//��SCLK��0����ɶ�ȡ
	}
	//д�����ݲ���
	for(i=0;i<8;i++)
	{
		//����ʱ����ͼ��DS1302��д������ǣ�һ��SCLK���� ��һλ����������SCLK�����ض���һλ
		DS1302_IO=Data&(0x01<<i);//����ѭ��ȡ����0-��7λд��IO�ڣ���оƬ֪������Ҫ��оƬ����д���ÿһλ���ݣ�����0x01=0000 0001 �൱��ֻ���µ�0λ����1-��7λ����0 
		DS1302_SCLK=1;//��SCLK��1��SCLK�����ض���һλ������ʱ����ͼ��ȷ������
		DS1302_SCLK=0;//��SCLK��0����ɶ�ȡ
	}
		DS1302_CE=0;//��CE��0���Ǹ��ݵ����ֽڵ�ʱ����ͼ��ȷ����
	
}

/**
  * @brief  ��оƬ�ж������ݵĲ���
  * @param  Command����������ݣ�������д�뻹�Ƕ�ȡ�ȵ�
  * @retval ����Data�Ƕ�����������
  */

unsigned char DS1302_ReadByte(unsigned char Command)
{
		unsigned char i,Data=0x00;//��Data��ʼ��Ϊ0
		Command|=0x01;
		DS1302_CE=1;//��CE��1���Ǹ��ݵ����ֽڵ�ʱ����ͼ��ȷ����
		//д���������
		for(i=0;i<8;i++)
		{
			DS1302_IO=Command&(0x01<<i);//����ѭ��ȡ����0-��7λ������0x01=0000 0001 �൱��ֻ���µ�0λ����1-��7λ����0 
			DS1302_SCLK=0;//��ΪSCLK��ʱ�������ǹ涨�ģ�������Ҫ�������ʱ���Ҫ�ȸ�0 ���1����Ȼ����
			DS1302_SCLK=1;//��SCLK��1��SCLK�����ض���һλ������ʱ����ͼ��ȷ������
		}
		//�������ݲ���
		for(i=0;i<8;i++)
		{
			DS1302_SCLK=1;//�����ظ���1��û�й�ϵ�������0��1 �ᵼ�����SCLKΪ1����ʱ��ͼ����
			DS1302_SCLK=0;
			if(DS1302_IO){Data=Data|(0x01<<i);}//���io�ڽ��ܵ����ݣ�==1������Ϊ����DS1302_IO=Command&(0x01<<7)������ʱ��ͼ�ǵ���1�ģ�Ȼ��data����һ��������ÿһλ
		}
		DS1302_CE=0;//��CE��0���Ǹ��ݵ����ֽڵ�ʱ����ͼ��ȷ����
		DS1302_IO=0;
		return Data;
}






/**
  * @brief  ����һ�������Լ�Ŀǰ�ĳ�ʼʱ�䣬�������ǰ�ʱ������ֶ�д��������DS1302_TIME[]������д����
  * @param  ��
  * @retval ��
  */
void DS1302_SetTime(void)
{
	DS1302_WriteByte(DS1302_WP,0x00);//�ر�д����
	DS1302_WriteByte(DS1302_YEAR,DS1302_TIME[0]/10*16+DS1302_TIME[0]%10);//����ı��ʽ�ǽ�ʮ����ת��BCD�룬��ΪоƬDS1302����BCD�����������ֵ�
	DS1302_WriteByte(DS1302_MONTH,DS1302_TIME[1]/10*16+DS1302_TIME[1]%10);
	DS1302_WriteByte(DS1302_DATE,DS1302_TIME[2]/10*16+DS1302_TIME[2]%10);
	DS1302_WriteByte(DS1302_HOUR,DS1302_TIME[3]/10*16+DS1302_TIME[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_TIME[4]/10*16+DS1302_TIME[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_TIME[5]/10*16+DS1302_TIME[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_TIME[6]/10*16+DS1302_TIME[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80);//����д����
}


/**
  * @brief  ��ȡͨ��оƬ������ʱ�䣬���ǰѳ�ʼ����ʱ������оƬ��оƬ���Զ�����1s������ʱ�䣬����ֻ��Ҫ�������ݼ���
  * @param  ��
  * @retval ��
  */
void DS1302_ReadTime(void)
{
		unsigned char Temp;
		Temp=DS1302_ReadByte(DS1302_YEAR);//��������������ʱ����Temp�У�����ת��Ϊʮ����
		DS1302_TIME[0]=Temp/16*10+Temp%16;//����ı��ʽ�ǽ�BCD��ת��ʮ���ƣ���ΪоƬDS1302����BCD�����������ֵ�,���Ǵ������������������BCD�룬��Ҫ����ʮ���Ʋ�����ʾ��LCD��
	Temp=DS1302_ReadByte(DS1302_MONTH);
		DS1302_TIME[1]=Temp/16*10+Temp%16;//������������ļ��������֣����¶�������DS1302_TIME[]��
	Temp=DS1302_ReadByte(DS1302_DATE);
		DS1302_TIME[2]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_HOUR);
		DS1302_TIME[3]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_MINUTE);
		DS1302_TIME[4]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_SECOND);
		DS1302_TIME[5]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DAY);
		DS1302_TIME[6]=Temp/16*10+Temp%16;
	
}





