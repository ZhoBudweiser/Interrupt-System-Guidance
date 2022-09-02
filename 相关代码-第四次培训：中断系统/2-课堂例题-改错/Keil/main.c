/*****************************
*���Ĵ���ѵ-��������-�Ĵ���
*�޸�ʱ��:	2021-10-30
*******************************/
#include <reg52.h>

/*�������Ŷ���*/
sbit K1 = P3^2;

/*LED���Ŷ���*/
#define LED P2

/*ȫ�ֱ�������*/
bit isOn = 0;			//LED���������

/*��ʱ����*/
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

/*������*/
void mian()
{
	Int0Init();
	LED = 0x00;			//LEDȫ��
	while (1)
	{
		if (isOn)
		{
			LED = ~LED;
			Delay_ms(500);			
		}
	}
}

/*�ⲿ�ж�0��ʼ������*/
void Int0Init()
{
	IT0 = 1;		//�����ش�����ʽ���½��أ�
	EX0 = 1;		//�� INT0 ���ж�����
}

/*�ⲿ�ж�0��������ʵ��ĳλLED����˸����*/
void Int0()	interrupt 1
{
	Delay_ms(5);	 //��ʱ����
	if(k1 == 1)
	{
		isOn = ~isOn;
	}
	while (!k1);
}
