#include <REGX52.H>
#include <INTRINS.H>
sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_E=P2^7;
#define LCD_DataPort P0 

void LCD_Delay()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}



//дָ��
void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS=0;//����ʱ��ṹ��д��1Ϊ���ݣ�0Ϊָ����������ż���Ӧ�õ�·�ɲ�
	LCD_RW=0;//1ΪRead��0ΪWrite
	LCD_DataPort=Command;//�������P0�ϣ�LCD_DataPort�궨��P0
	LCD_E=1;//ʹ�ܣ�1Ϊ������Ч���½���ִ������
	LCD_Delay();//�����½�ʱ��̫�죨ns���𣩣���Ƭ����ms����ʶ���ˣ���Ҫ��ʱ
	LCD_E=0;//�½���ִ������
	LCD_Delay();
}



//д����
void LCD_WriteData(unsigned char Data)
{
	LCD_RS=1;//����ʱ��ṹ��д��1Ϊ���ݣ�0Ϊָ����������ż���Ӧ�õ�·�ɲ�
	LCD_RW=0;
	LCD_DataPort=Data;//���ݷ���P0�ϣ�
	LCD_E=1;//ʹ�ܣ�1Ϊ������Ч���½���ִ������
	LCD_Delay();
	LCD_E=0;
	LCD_Delay();
}



//��ʼ��LCD1602�����ݲ�������ȷ��
void LCD_Init(void)
{
	LCD_WriteCommand(0x38);//��λ���ݽӿڣ�������ʾ��5*7����
	LCD_WriteCommand(0x0C);//��ʾ�������أ���˸��
	LCD_WriteCommand(0x06);//���ݶ�д�����󣬹���Զ���һ�����治��
	LCD_WriteCommand(0x01);//����
}



//���ó�ʼ���
void LCD_SetCursor(unsigned char Line,unsigned char Column)
{
if(Line==1)
	{
		//0x80|��ַ
		LCD_WriteCommand(0x80|(Column-1));//(Column-1)�ǵ�ַ�����ù��λ�ã��ɴ洢���ṹDDRAM��������ʾ�����ĵ�ַ��������һ�У����Ǵ�0��ʼ������Ҫʵ������-1
	}
	else
	{
		LCD_WriteCommand(0x80|(Column-1)+0x40);//(Column-1)�ǵ�ַ�����ù��λ�ã��ɴ洢���ṹDDRAM��������ʾ�����ĵ�ַ�������ڶ��еĵ�ַ���һ��ƫ��0x40��Ҫ����0x40
	}
}


//��ʾ�ַ�����������Ϊ��1.���͹��λ�ó�ʼ��ָ�� 2.����Ҫ��ʾ���ַ�����
void LCD_ShowChar(unsigned char Line,unsigned char Column,unsigned char Char)
{
	LCD_SetCursor(Line,Column);
	LCD_WriteData(Char);
}


//��ʾ�ַ�����������Ϊ��1.���͹��λ�ó�ʼ��ָ�� 2.����Ҫ��ʾ���ַ�����
void LCD_ShowString(unsigned char Line,unsigned char Column,unsigned char String[])
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=0;String[i]!='\0';i++)
	{
		LCD_WriteData(String[i]);
	}
}


//�Զ���ĳ˷�����
int LCD_Pow(int X,int Y)
{
	unsigned char i;
	int Result=1;
	for(i=0;i<Y;i++)
	{
			Result*=X;
	}
	return Result;
}


//��ʾ�޺�ʮ�����ַ�����������Ϊ��1.���͹��λ�ó�ʼ��ָ�� 2.����Ҫ��ʾ���ַ�����
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(0x30+Number/LCD_Pow(10,i-1)%10);
	}
}


//��ʾ�к�ʮ�����ַ�����������Ϊ��1.���͹��λ�ó�ʼ��ָ�� 2.����Ҫ��ʾ���ַ�����
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{
	unsigned char i;
	unsigned int Number1;//�����洢�޷��ŵ�����
	LCD_SetCursor(Line,Column);
	//�ж��������������������
	if(Number>=0)
	{
			LCD_WriteData('+');
			Number1=Number;//�����Ͳ��øı�
	}
	else
	{
			LCD_WriteData('-');
			Number1=-Number;//������Ҫ��Ϊ�෴������Ϊ����
	}
	//���¶�����Number1�������������Ϊ�����Ѿ������������
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(0x30+Number1/LCD_Pow(10,i-1)%10);
	}
}


//��ʾʮ���ַ�����������Ϊ��1.���͹��λ�ó�ʼ��ָ�� 2.����Ҫ��ʾ���ַ�����
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	unsigned char SingleNumber;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		SingleNumber=Number/LCD_Pow(16,i-1)%16;//ʮ�����ǳ���10��ʮ������ͬ��
		if(SingleNumber<10)
		{
			LCD_WriteData('0'+SingleNumber);//9���ڵ�ֱ�Ӿ���0������ŵ�ASCII�ַ�
		}
		else
		{
		LCD_WriteData('A'+SingleNumber-10);//10�����ϵ���A������ŵ�ASCII�ַ�
		}
	}
}


//��ʾ�������ַ�����������Ϊ��1.���͹��λ�ó�ʼ��ָ�� 2.����Ҫ��ʾ���ַ�����
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData('0'+Number/LCD_Pow(2,i-1)%2);
	}
}

