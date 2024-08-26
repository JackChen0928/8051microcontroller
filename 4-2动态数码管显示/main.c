#include <REGX52.H>
#include <INTRINS.H>
//用于段选 选择LED灯显示什么数字
unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

//延时函数
void Delay(unsigned int xms)		//@11.0592MHz
{
	unsigned char i, j;
	while(xms--)
	{
				_nop_();
				i = 2;
				j = 199;
				do
				{
					while (--j);
				} while (--i);
				
	}
	
}

void Nixie(unsigned char Location,Number)//第几个LED灯,显示什么数字的函数 
{
	//位选 选择哪一个LED灯
	switch(Location)
	{
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=NixieTable[Number];//段选 选择LED灯显示什么数字
	Delay(1);//消影，位选 段选！位选 段选 段选到位选之间数据会错乱 需要把段选的数据清零消除影响 
	P0=0x00;

}

int main()
{
	while(1)
	{
		Nixie(1,1);
		//Delay(200);
		Nixie(2,2);
		//Delay(200);
		Nixie(3,3);
		//Delay(200);
	}
}