#include "H/Function_Init.H" 

void Uart_Init(uint Freq,unsigned long int baud);
bit UartSendFlag = 0; 		//�����жϱ�־λ
bit UartReceiveFlag = 0;	//�����жϱ�־λ
uchar Uart_data;

uchar tuya_DataTab[15];   //���յ������ݴ�ű��,���15��
/*****************************************************
*�������ƣ�void Uart_Init(uint Freq,unsigned long int baud)
*�������ܣ�Uart�жϳ�ʼ��
*��ڲ�����Freq-��Ƶ��baud-������
*���ڲ�����void
*****************************************************/
void Uart_Init(uint Freq,unsigned long int baud)    //ѡ��Timer1��Ϊ�������źŷ�����
{
	P2CON &= 0xFC;   //TX/RX����Ϊ���������
	P2PH  |= 0x03;
	
	SCON  |= 0X50;   //����ͨ�ŷ�ʽΪģʽһ���������
	TMCON |= 0X02;
	TH1 = (Freq*1000000/baud)>>8;	  //������ΪT1�����ʱ�䣻
	TL1 = Freq*1000000/baud;
	TR1 = 0;
	ET1 = 0;
	EUART = 1;     //����Uart�ж�
	EA = 1;
}

void Uart_Temp(void)//���Ͷ�������ʪ��
{
	Uart_temp_up();		//�ϴ��¶ȵ���
	Uart_humid_up();	//�ϴ�ʪ�ȵ���
}

/*****************************************************
*�������ƣ�void UartInt(void) interrupt 4
*�������ܣ�Uart�жϺ���
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void UartInt(void) interrupt 4
{
	if(TI)
	{
		TI = 0;	
		UartSendFlag = 1;		
	}
	if(RI)
	{
		RI = 0;	
		UartReceiveFlag = 1;//���ձ�־λ��1
		Uart_data=SBUF;		//ȡ�յ�����
		tuya_sjcl();		//Ϳѻ���ݴ���
	}	
}
