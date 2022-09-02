/*****************************
*第四次培训-课堂例题-外部中断的两种触发方式
*修改时间:	2021-10-30
*******************************/
#include <reg52.h>
#include <intrins.h>

#define 	uint8		unsigned char
#define		uint16		unsigned int

/*按键引脚定义*/
sbit k1 = P3^2;

/*LED引脚定义*/
#define LED P2

/*全局变量定义*/
bit isOn = 0;			//LED灯亮灭控制

/*延时函数*/
void Delay_ms(uint16 x)		//@11.0592MHz
{
	uint8 i, j;

	while (x--)
	{
		i = 2;
		j = 199;
		_nop_();
		do
		{
			while (--j);
		} while (--i);		
	}
}

/*外部中断0初始化函数*/
void Int0Init()
{
	IT0 = 0;		//跳变沿触发方式（下降沿）
	EX0 = 1;		//打开 INT0 的中断允许
	EA = 1;			//打开总中断
}

/*主函数*/
void main()
{
	Int0Init();
	LED = 0xff;	//LED全灭
	while(1)
	{
		
	}
}

///*外部中断0处理函数，IT0 = 1*/
//void Int0()	interrupt 0
//{
//	Delay_ms(5);	 //延时消抖
//	if(k1 == 0)
//	{
//		LED = ~LED;
//	}
//}

/*外部中断0处理函数，IT0 = 0*/
void Int0()	interrupt 0
{
	Delay_ms(5);	 //延时消抖
	if(k1 == 0)
	{
		LED = ~LED;
	}
	while (!k1);
}
