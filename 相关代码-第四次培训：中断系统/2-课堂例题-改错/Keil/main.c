/*****************************
*第四次培训-课堂例题-改错题
*修改时间:	2021-10-30
*******************************/
#include <reg52.h>

/*按键引脚定义*/
sbit K1 = P3^2;

/*LED引脚定义*/
#define LED P2

/*全局变量定义*/
bit isOn = 0;			//LED灯亮灭控制

/*延时函数*/
void delay_ms(uint16 x)		//@11.0592MHz
{
	uint8 i = 2; j = 199;

	while (x--)
	{
		_nop_();
		do
		{
			while (--j);
		} while (--i);		
	}

	return 0;
}

/*主函数*/
void mian()
{
	Int0Init();
	LED = 0x00;			//LED全灭
	while (1)
	{
		if (isOn)
		{
			LED = ~LED;
			Delay_ms(500);			
		}
	}
}

/*外部中断0初始化函数*/
void Int0Init()
{
	IT0 = 1;		//跳变沿触发方式（下降沿）
	EX0 = 1;		//打开 INT0 的中断允许
}

/*外部中断0处理函数，实现某位LED的闪烁控制*/
void Int0()	interrupt 1
{
	Delay_ms(5);	 //延时消抖
	if(k1 == 1)
	{
		isOn = ~isOn;
	}
	while (!k1);
}
