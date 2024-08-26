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



//写指令
void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS=0;//根据时序结构来写，1为数据，0为指令，功能在引脚及其应用电路可查
	LCD_RW=0;//1为Read，0为Write
	LCD_DataPort=Command;//命令放在P0上，LCD_DataPort宏定义P0
	LCD_E=1;//使能，1为数据有效，下降沿执行命令
	LCD_Delay();//由于下降时间太快（ns级别），单片机（ms级别）识别不了，需要延时
	LCD_E=0;//下降沿执行命令
	LCD_Delay();
}



//写数据
void LCD_WriteData(unsigned char Data)
{
	LCD_RS=1;//根据时序结构来写，1为数据，0为指令，功能在引脚及其应用电路可查
	LCD_RW=0;
	LCD_DataPort=Data;//数据放在P0上，
	LCD_E=1;//使能，1为数据有效，下降沿执行命令
	LCD_Delay();
	LCD_E=0;
	LCD_Delay();
}



//初始化LCD1602，根据操作流程确定
void LCD_Init(void)
{
	LCD_WriteCommand(0x38);//八位数据接口，两行显示，5*7点阵
	LCD_WriteCommand(0x0C);//显示开，光标关，闪烁关
	LCD_WriteCommand(0x06);//数据读写操作后，光标自动加一，画面不动
	LCD_WriteCommand(0x01);//清屏
}



//设置初始光标
void LCD_SetCursor(unsigned char Line,unsigned char Column)
{
if(Line==1)
	{
		//0x80|地址
		LCD_WriteCommand(0x80|(Column-1));//(Column-1)是地址，设置光标位置，由存储器结构DDRAM（数据显示区）的地址决定，第一行，列是从0开始，所以要实际列数-1
	}
	else
	{
		LCD_WriteCommand(0x80|(Column-1)+0x40);//(Column-1)是地址，设置光标位置，由存储器结构DDRAM（数据显示区）的地址决定，第二行的地址与第一行偏移0x40，要加上0x40
	}
}


//显示字符，操作流程为：1.发送光标位置初始的指令 2.发送要显示的字符数据
void LCD_ShowChar(unsigned char Line,unsigned char Column,unsigned char Char)
{
	LCD_SetCursor(Line,Column);
	LCD_WriteData(Char);
}


//显示字符，操作流程为：1.发送光标位置初始的指令 2.发送要显示的字符数据
void LCD_ShowString(unsigned char Line,unsigned char Column,unsigned char String[])
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=0;String[i]!='\0';i++)
	{
		LCD_WriteData(String[i]);
	}
}


//自定义的乘方函数
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


//显示无号十进制字符，操作流程为：1.发送光标位置初始的指令 2.发送要显示的字符数据
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(0x30+Number/LCD_Pow(10,i-1)%10);
	}
}


//显示有号十进制字符，操作流程为：1.发送光标位置初始的指令 2.发送要显示的字符数据
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{
	unsigned char i;
	unsigned int Number1;//用来存储无符号的数字
	LCD_SetCursor(Line,Column);
	//判断数字正负来输出正负号
	if(Number>=0)
	{
			LCD_WriteData('+');
			Number1=Number;//正数就不用改变
	}
	else
	{
			LCD_WriteData('-');
			Number1=-Number;//负数需要变为相反数，成为正数
	}
	//以下都是用Number1来操作输出，因为上面已经输出了正负号
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(0x30+Number1/LCD_Pow(10,i-1)%10);
	}
}


//显示十六字符，操作流程为：1.发送光标位置初始的指令 2.发送要显示的字符数据
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	unsigned char SingleNumber;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		SingleNumber=Number/LCD_Pow(16,i-1)%16;//十进制是除以10，十六进制同理
		if(SingleNumber<10)
		{
			LCD_WriteData('0'+SingleNumber);//9以内的直接就是0后面跟着的ASCII字符
		}
		else
		{
		LCD_WriteData('A'+SingleNumber-10);//10及以上的是A后面跟着的ASCII字符
		}
	}
}


//显示二进制字符，操作流程为：1.发送光标位置初始的指令 2.发送要显示的字符数据
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData('0'+Number/LCD_Pow(2,i-1)%2);
	}
}

