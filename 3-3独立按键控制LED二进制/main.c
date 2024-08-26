#include <REGX52.H>
#include <INTRINS.H>
void Delay(unsigned int xms)		//@11.0592MHz
{
	unsigned char i, j;
	while(xms)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		xms--;
	}
}

void main()
{
 unsigned char LEDNum=0;
	while(1)
	{
			if(P3_1==0)//an xia le
			{
				Delay(20);//xiao dou
				while(P3_1==0);//如果发现没有松开手那就进入循环一直到松手 
				Delay(20);
				//上面都是按键消抖
				//1111 1111
				LEDNum++;
				P2=~LEDNum;//1111 1111
			}
	}

}