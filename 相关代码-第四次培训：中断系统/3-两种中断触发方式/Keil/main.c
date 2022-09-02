/*****************************
*���Ĵ���ѵ-��������-�ⲿ�жϵ����ִ�����ʽ
*�޸�ʱ��:	2021-10-30
*******************************/
#include <reg52.h>
#include <intrins.h>

#define 	uint8		unsigned char
#define		uint16		unsigned int

/*�������Ŷ���*/
sbit k1 = P3^2;

/*LED���Ŷ���*/
#define LED P2

/*ȫ�ֱ�������*/
bit isOn = 0;			//LED���������

/*��ʱ����*/
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

/*�ⲿ�ж�0��ʼ������*/
void Int0Init()
{
	IT0 = 0;		//�����ش�����ʽ���½��أ�
	EX0 = 1;		//�� INT0 ���ж�����
	EA = 1;			//�����ж�
}

/*������*/
void main()
{
	Int0Init();
	LED = 0xff;	//LEDȫ��
	while(1)
	{
		
	}
}

///*�ⲿ�ж�0��������IT0 = 1*/
//void Int0()	interrupt 0
//{
//	Delay_ms(5);	 //��ʱ����
//	if(k1 == 0)
//	{
//		LED = ~LED;
//	}
//}

/*�ⲿ�ж�0��������IT0 = 0*/
void Int0()	interrupt 0
{
	Delay_ms(5);	 //��ʱ����
	if(k1 == 0)
	{
		LED = ~LED;
	}
	while (!k1);
}
