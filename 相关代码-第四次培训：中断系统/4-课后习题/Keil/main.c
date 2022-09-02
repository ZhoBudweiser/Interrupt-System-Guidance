/*****************************
*���Ĵ���ѵ��ҵ-�ڶ���ο�����
*�޸�ʱ��:	2021-10-25
*******************************/
#include <reg52.h>
#include <intrins.h>

#define 	uint8		unsigned char
#define		uint16		unsigned int

/*�������Ŷ���*/
sbit k1 = P3^2;
sbit k2 = P3^3;

/*LED���Ŷ���*/
#define LED P2

/*ȫ�ֱ�������*/
bit isOn = 0;			//LED���������
uint8 pos = 0xfe;		//LEDλ����λѡ��

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
	IT0 = 1;		//�����ش�����ʽ���½��أ�
	EX0 = 1;		//�� INT0 ���ж�����
	EA = 1;			//�����ж�
}

/*�ⲿ�ж�1��ʼ������*/
void Int1Init()
{
	IT1 = 1;		//�����ش�����ʽ���½��أ�
	EX1 = 1;		//�� INT1 ���ж�����	
	EA = 1;			//�����ж�	
}

/*������*/
void main()
{
	Int0Init();
	Int1Init();
	LED = 0xff;	//LEDȫ��

	while(1)
	{
		if (isOn)
		{
			LED = ~LED;		 	//��P2�������ŵ�LED����ȡ������
			LED |= pos;			//����Ŀ��λ�����LED��1��ȷ���䴦��Ϩ��״̬
			Delay_ms(500);
		}
	}
}

/*�ⲿ�ж�0��������ʵ��ĳλLED����˸����*/
void Int0()	interrupt 0
{
	Delay_ms(5);	 //��ʱ����
	if(k1 == 0)
	{
		isOn = ~isOn;
	}
}

/*�ⲿ�ж�1��������ʵ��LED����λѡ��*/
void Int1()	interrupt 2
{
	Delay_ms(5);	 //��ʱ����
	if(k2 == 0 && isOn)			//��LED������ͣ״̬ʱ�û������ܿ�����λ��Ч�������׳����ʲ�����
	{							//�˴�ֱ��������ƣ�ͬѧ�ǿ����ʵ����ӣ�������
		pos = ~pos;				//������λ�������������λ�ǲ�0�����������Ƚ���ȡ��
		pos = pos << 1;
		if (pos == 0x00)		//����1�����λ�Ƴ������
		{
			pos = 0x01;
		}
		pos = ~pos;
	}
}