#include "H/Function_Init.H"
/*****************************************************
*�������ƣ�void IO_Init(void)
*�������ܣ�IO��ʼ��
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void IO_Init(void)
{
	P0CON = 0xFF;  //����P0Ϊǿ����ģʽ
	P0PH  = 0x00;
//	P0=0XFF;
	P1CON = 0x00;  //����P1Ϊ��������ģʽ
	P1PH  = 0x00;
	P2CON = 0x00;  //����P2Ϊ���������ģʽ
	P2PH  = 0xFF;
	P3CON = 0xFF;  //����P3Ϊǿ����ģʽ
	P3PH  = 0x00;
	P4CON = 0xFF;  //����P4Ϊǿ����ģʽ
	P4PH  = 0x01;
	P5CON = 0xFF;  //����P5Ϊǿ����ģʽ
	P5PH  = 0x00;

}

void Delay(uint time)
{
    for(;time>0;time--);
}