#include <REGX52.H>

sbit DS1302_SCLK=P3^6;//^表示地址
sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;

//宏定义  容易理解   芯片中的一个地址代表一个时间数据
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
	DS1302_CE=0;//初始化置0
	DS1302_SCLK=0;//初始化置0
}

/**
  * @brief  把数据写入芯片的操作
  * @param  Command是命令的数据，来控制写入还是读取等等，Data是写入的数据
  * @retval 无
  */
void DS1302_WriteByte(unsigned char Command,Data)
{
		unsigned char i;
		DS1302_CE=1;//把CE置1，根据单个字节的时序定义图来确定流程
	//写入命令的数据
	for(i=0;i<8;i++)
	{
		//根据时许定序图，DS1302的写入操作是：一个SCLK脉冲 读一位数，而且是SCLK上升沿读入一位
		DS1302_IO=Command&(0x01<<i);//利用循环取出第0-第7位写入IO口，让芯片知道我们要干什么，例如0x01=0000 0001 相当于只留下第0位，第1-第7位都清0 
		DS1302_SCLK=1;//把SCLK置1，SCLK上升沿读入一位，根据时序定义图来确定流程
		DS1302_SCLK=0;//把SCLK置0，完成读取
	}
	//写入数据操作
	for(i=0;i<8;i++)
	{
		//根据时许定序图，DS1302的写入操作是：一个SCLK脉冲 读一位数，而且是SCLK上升沿读入一位
		DS1302_IO=Data&(0x01<<i);//利用循环取出第0-第7位写入IO口，让芯片知道我们要向芯片里面写入的每一位数据，例如0x01=0000 0001 相当于只留下第0位，第1-第7位都清0 
		DS1302_SCLK=1;//把SCLK置1，SCLK上升沿读入一位，根据时序定义图来确定流程
		DS1302_SCLK=0;//把SCLK置0，完成读取
	}
		DS1302_CE=0;//把CE置0，是根据单个字节的时序定义图来确定的
	
}

/**
  * @brief  从芯片中读出数据的操作
  * @param  Command是命令的数据，来控制写入还是读取等等
  * @retval 返回Data是读出来的数据
  */

unsigned char DS1302_ReadByte(unsigned char Command)
{
		unsigned char i,Data=0x00;//把Data初始化为0
		Command|=0x01;
		DS1302_CE=1;//把CE置1，是根据单个字节的时序定义图来确定的
		//写入命令操作
		for(i=0;i<8;i++)
		{
			DS1302_IO=Command&(0x01<<i);//利用循环取出第0-第7位，例如0x01=0000 0001 相当于只留下第0位，第1-第7位都清0 
			DS1302_SCLK=0;//因为SCLK的时序不是我们规定的，我们需要跟上这个时序就要先给0 后给1，不然会乱
			DS1302_SCLK=1;//把SCLK置1，SCLK上升沿读入一位，根据时序定义图来确定流程
		}
		//读出数据操作
		for(i=0;i<8;i++)
		{
			DS1302_SCLK=1;//这里重复置1，没有关系，如果先0后1 会导致最后SCLK为1，与时序图不符
			DS1302_SCLK=0;
			if(DS1302_IO){Data=Data|(0x01<<i);}//如果io口接受到数据（==1），因为上面DS1302_IO=Command&(0x01<<7)，根据时序图是等于1的，然后data就逐一读出数据每一位
		}
		DS1302_CE=0;//把CE置0，是根据单个字节的时序定义图来确定的
		DS1302_IO=0;
		return Data;
}






/**
  * @brief  设置一个我们自己目前的初始时间，这里我们把时间的数字都写成了数组DS1302_TIME[]，方便写代码
  * @param  无
  * @retval 无
  */
void DS1302_SetTime(void)
{
	DS1302_WriteByte(DS1302_WP,0x00);//关闭写保护
	DS1302_WriteByte(DS1302_YEAR,DS1302_TIME[0]/10*16+DS1302_TIME[0]%10);//这里的表达式是将十进制转成BCD码，因为芯片DS1302是用BCD码来储存数字的
	DS1302_WriteByte(DS1302_MONTH,DS1302_TIME[1]/10*16+DS1302_TIME[1]%10);
	DS1302_WriteByte(DS1302_DATE,DS1302_TIME[2]/10*16+DS1302_TIME[2]%10);
	DS1302_WriteByte(DS1302_HOUR,DS1302_TIME[3]/10*16+DS1302_TIME[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_TIME[4]/10*16+DS1302_TIME[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_TIME[5]/10*16+DS1302_TIME[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_TIME[6]/10*16+DS1302_TIME[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80);//开启写保护
}


/**
  * @brief  读取通过芯片计算后的时间，我们把初始化的时间输入芯片后，芯片会自动计算1s递增的时间，我们只需要读出数据即可
  * @param  无
  * @retval 无
  */
void DS1302_ReadTime(void)
{
		unsigned char Temp;
		Temp=DS1302_ReadByte(DS1302_YEAR);//读出来的数字暂时存于Temp中，方便转化为十进制
		DS1302_TIME[0]=Temp/16*10+Temp%16;//这里的表达式是将BCD码转成十进制，因为芯片DS1302是用BCD码来储存数字的,我们从里面读出来的数字是BCD码，需要化成十进制才能显示在LCD上
	Temp=DS1302_ReadByte(DS1302_MONTH);
		DS1302_TIME[1]=Temp/16*10+Temp%16;//将这个读出来的计算后的数字，重新读入数组DS1302_TIME[]中
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





