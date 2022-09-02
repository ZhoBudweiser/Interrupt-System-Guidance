#include <reg52.h>
#include <intrins.h>

#define LED P2

#define uint8 	unsigned char
#define uint16	unsigned int

bit isOn = 1;
sbit k1 = P3^2;

void Delay_ms(uint16 x)		//@11.0592MHz
{
	uint8 i, j;

	while (x > 0)
	{
		_nop_();
		i = 2;
		j = 199;
		do	  
		{
			while (--j);
		} while (--i);
		x = x -1;		
	}

}

void int0Init()
{
	IT0 = 1;
	EX0 = 1;
	EA = 1;
}

void main()
{
	int0Init();
	LED = 0xff;

	while (1)
	{
		if (isOn == 1)
		{
			LED = ~LED;
			Delay_ms(500);			
		}
	}
}

void int0() interrupt 0
{
	Delay_ms(5);
	if (k1 == 0)
	{
		isOn = ~isOn;
	}
}