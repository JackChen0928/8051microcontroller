#ifndef __DS1302_H_
#define __DS1302_H_

	extern unsigned char DS1302_TIME[];//�ⲿ�ɵ��õ�����ǰ��Ҫ��extren ��������
	unsigned char DS1302_ReadByte(unsigned char Command);
	void DS1302_Init(void);
	void DS1302_WriteByte(unsigned char Command,Data);
	void DS1302_SetTime(void);
	void DS1302_ReadTime(void);
#endif
