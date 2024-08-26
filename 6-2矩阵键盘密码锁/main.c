#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum;
unsigned int Password,Count;//储存密码和读取个数

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
		while(1)
		{
				KeyNum=MatrixKey();//先接受扫描回来的数字 然后存起来
				if(KeyNum)//如果数字不为0，必要的判断，不然进入下一个循环，MatrixKey函数会把keynum变成0；导致显示00
				{
					if(KeyNum<=10)//如果s1-s10按键（表示1 2 3 4 5 6 7 8 9 0）按下，输入密码
					{
							if(Count<4)//输入四个数字才读入，按下第五个数字就不读了
							{
								Password*=10;//密码左移一位，我们的密码是四位数，但是读取的时候是一位一位的读取，所以左移保存
								Password+=KeyNum%10;//这个主要是在KeyNum=10的时候 把10转化成0的 也是获取一位密码
							}
							Count++;//计次加一
					}	
					
					
					//另一种情况 如果s11-s16按下 表示11-16 那就password不存起来，LCD也就不会显示出来
					
					
					if(KeyNum==11)//把s11按键设立成确认按键
					{
						if(Password==2345)//正确的密码
						{
							LCD_ShowString(1,14,"OK ");//密码正确就显示OK
							Password=0;//密码清零
							Count=0;//计次清零
							LCD_ShowNum(2,1,Password,4);//显示清零
						}
						else
						{
							LCD_ShowString(1,14,"ERR");//否则显示ERR
							Password=0;//密码清零
							Count=0;//计次清零
							LCD_ShowNum(2,1,Password,4);//显示清零
						}
						
						
					}
					if(KeyNum==12)//把s12按键设立成取消按键
					{
						
							Password=0;//密码清零
							Count=0;//计次清零
							LCD_ShowNum(2,1,Password,4);//显示清零
					
					}
					
					LCD_ShowNum(2,1,Password,4);//在数码管上显示该数字（password）
				}
		}


}