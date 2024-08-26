#include <REGX52.H>
#include "Delay.h"
/**
  * @brief  矩阵键盘读取按键键码
  * @param  无
  * @retval KeyNumber 按下按键的键码值
			如果按键按下不放 程序会停留在此函数，松手的一瞬间，返回按键键码，没有按键按下时，返回0
  */
unsigned char MatrixKey()
{
	unsigned char KeyNumber=0;
	//1.按列扫描 先固定第一列 然后扫描1234行 如果监测到按键按下就返回那个按键对应的数字
	P1=0xFF;//先初始化所有P1的值（即P1_0、P1_1、P1_2、P1_3、P1_4、P1_5、P1_6、P1_7）为1
	P1_3=0;//固定第一列
	if(P1_7==0){Delay(20);while(P1_7==0);	Delay(20);KeyNumber=1;}//延时来消除按键抖动
	if(P1_6==0){Delay(20);while(P1_6==0);	Delay(20);KeyNumber=5;}//延时来消除按键抖动
	if(P1_5==0){Delay(20);while(P1_5==0);	Delay(20);KeyNumber=9;}//延时来消除按键抖动
	if(P1_4==0){Delay(20);while(P1_4==0);	Delay(20);KeyNumber=13;}//延时来消除按键抖动
	
	//2.按列扫描 先固定第二列 然后扫描1234行 如果监测到按键按下就返回那个按键对应的数字
	P1=0xFF;//先初始化所有P1的值（即P1_0、P1_1、P1_2、P1_3、P1_4、P1_5、P1_6、P1_7）为1
	P1_2=0;//固定第二列
	if(P1_7==0){Delay(20);while(P1_7==0);	Delay(20);KeyNumber=2;}//延时来消除按键抖动
	if(P1_6==0){Delay(20);while(P1_6==0);	Delay(20);KeyNumber=6;}//延时来消除按键抖动
	if(P1_5==0){Delay(20);while(P1_5==0);	Delay(20);KeyNumber=10;}//延时来消除按键抖动
	if(P1_4==0){Delay(20);while(P1_4==0);	Delay(20);KeyNumber=14;}//延时来消除按键抖动
	
	//3.按列扫描 先固定第三列 然后扫描1234行 如果监测到按键按下就返回那个按键对应的数字
	P1=0xFF;//先初始化所有P1的值（即P1_0、P1_1、P1_2、P1_3、P1_4、P1_5、P1_6、P1_7）为1
	P1_1=0;//固定第三列
	if(P1_7==0){Delay(20);while(P1_7==0);	Delay(20);KeyNumber=3;}//延时来消除按键抖动
	if(P1_6==0){Delay(20);while(P1_6==0);	Delay(20);KeyNumber=7;}//延时来消除按键抖动
	if(P1_5==0){Delay(20);while(P1_5==0);	Delay(20);KeyNumber=11;}//延时来消除按键抖动
	if(P1_4==0){Delay(20);while(P1_4==0);	Delay(20);KeyNumber=15;}//延时来消除按键抖动
	
	//4.按列扫描 先固定第四列 然后扫描1234行 如果监测到按键按下就返回那个按键对应的数字
	P1=0xFF;//先初始化所有P1的值（即P1_0、P1_1、P1_2、P1_3、P1_4、P1_5、P1_6、P1_7）为1
	P1_0=0;//固定第四 列
	if(P1_7==0){Delay(20);while(P1_7==0);	Delay(20);KeyNumber=4;}//延时来消除按键抖动
	if(P1_6==0){Delay(20);while(P1_6==0);	Delay(20);KeyNumber=8;}//延时来消除按键抖动
	if(P1_5==0){Delay(20);while(P1_5==0);	Delay(20);KeyNumber=12;}//延时来消除按键抖动
	if(P1_4==0){Delay(20);while(P1_4==0);	Delay(20);KeyNumber=16;}//延时来消除按键抖动
	
	return KeyNumber;

}	