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

	while(1)
	{
			if(P3_1==0)//an xia le
			{
				Delay(20);//xiao dou
				while(P3_1==0);//xiao dou hou haishi anxia jiu bu dong zhi dao song kai shou 
				Delay(20);
				
				P2_0=~P2_0;//song shou hou cai qu fan
			}
	}

}