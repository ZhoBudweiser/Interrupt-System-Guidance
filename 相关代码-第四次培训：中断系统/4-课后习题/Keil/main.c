/*****************************
*第四次培训作业-第二题参考代码
*修改时间:	2021-10-25
*******************************/
#include <reg52.h>
#include <intrins.h>

#define 	uint8		unsigned char
#define		uint16		unsigned int

/*按键引脚定义*/
sbit k1 = P3^2;
sbit k2 = P3^3;

/*LED引脚定义*/
#define LED P2

/*全局变量定义*/
bit isOn = 0;			//LED灯亮灭控制
uint8 pos = 0xfe;		//LED位置移位选择

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
	IT0 = 1;		//跳变沿触发方式（下降沿）
	EX0 = 1;		//打开 INT0 的中断允许
	EA = 1;			//打开总中断
}

/*外部中断1初始化函数*/
void Int1Init()
{
	IT1 = 1;		//跳变沿触发方式（下降沿）
	EX1 = 1;		//打开 INT1 的中断允许	
	EA = 1;			//打开总中断	
}

/*主函数*/
void main()
{
	Int0Init();
	Int1Init();
	LED = 0xff;	//LED全灭

	while(1)
	{
		if (isOn)
		{
			LED = ~LED;		 	//对P2所有引脚的LED进行取反操作
			LED |= pos;			//将除目标位置外的LED置1，确保其处于熄灭状态
			Delay_ms(500);
		}
	}
}

/*外部中断0处理函数，实现某位LED的闪烁控制*/
void Int0()	interrupt 0
{
	Delay_ms(5);	 //延时消抖
	if(k1 == 0)
	{
		isOn = ~isOn;
	}
}

/*外部中断1处理函数，实现LED的移位选择*/
void Int1()	interrupt 2
{
	Delay_ms(5);	 //延时消抖
	if(k2 == 0 && isOn)			//当LED处于暂停状态时用户并不能看到移位的效果，容易出错，故不合理
	{							//此处直接添加限制，同学们可以适当发挥，合理即可
		pos = ~pos;				//考虑移位运算符，由于移位是补0操作，所以先进行取反
		pos = pos << 1;
		if (pos == 0x00)		//考虑1从最高位移出的情况
		{
			pos = 0x01;
		}
		pos = ~pos;
	}
}