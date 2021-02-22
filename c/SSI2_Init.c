#include "H/Function_Init.H"
//#include"H/OledFont.h"


uint temp_vH;		//�����ⲿ�¶ȱ���
uint temp_vH1;		//���ڴ������¶ȴ���60ʱ,�ϴ��Ʊ���60
uint temp_vL;		//�����ⲿ�¶ȱ���

uint humid_vH;		//�����ⲿʪ�ȱ���
uint humid_vL;		//�����ⲿʪ�ȱ���
uchar temp_H;		//�¶�ֵ��8λ
uchar temp_L;		//�¶�ֵ��8λ

uchar humid_z;		//ʪ��ֵ
//float temp_vHxs;	//���ڴ��С�����¶��м�ֵ


bit TWI1Flag = 0;         //TWI1�жϱ�־λ
bit TWI2Flag = 0;         //TWI2�жϱ�־λ
bit test_bit=0;			  //����һ��SHT20����ʪ���������ݱ�־λ

bit fs_temp;			//Ϊ�����ı���


char temp_shiwei;	//�¶�ʮλ
char temp_gewei; 	//�¶�ʮλ��λ
char temp_xiaoshu; //�¶�ʮλС��λ

char	humid_shiwei;	//ʪ��ʮλ
char	humid_gewei;	  	//ʪ�ȸ�λ


/*****************************************************
*�������ƣ�void Write_IIC_Data(unsigned char IIC_Data)
*�������ܣ�I2C��OLED����  ��������
*��ڲ�����void
*���ڲ�����void
*****************************************************/

void Write_IIC_Data(uchar IIC_Data)	  //д����
 {
	US1CON1 |= 0x20;    //������ʼ����,ͬʱ������ж�
	while(!TWI1Flag); 	//�ȴ�TWI�ж�
	TWI1Flag = 0;		//TWI1�жϱ�־λ��0
	US1CON3 = 0x78;	    //���͵�ַ��д���� ���ݻ���Ĵ������ֽ�		���λΪ0��д
	while(!TWI1Flag); 	//�ȴ�TWI�ж�,��������Ҳ������ж�
    TWI1Flag = 0;		//TWI1�жϱ�־λ��0
	US1CON3 = 0x40;	    //��ʾ���淢����д����
	while(!TWI1Flag); 	//�ȴ�TWI�ж�
    TWI1Flag = 0;		//TWI1�жϱ�־λ��0
	US1CON3 = IIC_Data;	//��������,��������Ҳ������ж�
    while(!TWI1Flag);	//�ȴ�TWI�ж�
    TWI1Flag = 0;		//TWI2�жϱ�־λ��0
	Delay(100);			//��ʱ
	US1CON1 |= 0x10; 	//����ֹͣ����	 ����Ҳ�������ж������鲻��*/   
	Delay(100);			//��ʱ
	TWI1Flag = 0;		//TWI1�жϱ�־λ��0  ***********����һ���жϱ�־,����ֹͣ����Ҳ�������ж�,��ֹ��������һ֡����(��ַ)
}
/*****************************************************
*�������ƣ�Write_IIC_Command(unsigned char IIC_Command)
*�������ܣ�I2C��OLED����  ��ָ����
*��ڲ�����void
*���ڲ�����void
*****************************************************/
 
void  Write_IIC_Command(uchar IIC_Command)	  //д��ָ��
 {
	US1CON1 |= 0x20;    //������ʼ����,ͬʱ������ж�
	while(!TWI1Flag); 	//�ȴ�TWI�ж�
    TWI1Flag = 0;		//TWI1�жϱ�־λ��0
	US1CON3 = 0x78;	    //���͵�ַ��д���� ���ݻ���Ĵ������ֽ�		���λΪ0��д
	while(!TWI1Flag); 	//�ȴ�TWI�ж�,��������Ҳ������ж�
    TWI1Flag = 0;		//TWI1�жϱ�־λ��0
	US1CON3 = 0x00;	    //��ʾ���淢����д����
	while(!TWI1Flag); 	//�ȴ�TWI�ж�
    TWI1Flag = 0;		//TWI1�жϱ�־λ��0
	US1CON3 = IIC_Command;	//��������,��������Ҳ������ж�
    while(!TWI1Flag);	//�ȴ�TWI�ж�
    TWI1Flag = 0;		//TWI1�жϱ�־λ��0
	Delay(100);			//��ʱ
	US1CON1 |= 0x10; 	//����ֹͣ���� 
	Delay(100);			//��ʱ
	TWI1Flag = 0;		//TWI1�жϱ�־λ��0  ***********����һ���жϱ�־,����ֹͣ����Ҳ�������ж�,��ֹ��������һ֡����(��ַ)

} 			  //*/






/*****************************************************
*�������ƣ�void SSI2_Test(void)
*�������ܣ�SSI2����		����SHT30����ʪ��ָ��
*��ڲ�����void
*���ڲ�����void
*****************************************************/

void SSI2_Test(void)
 {
	US2CON1 |= 0x20;    //������ʼ����,ͬʱ������ж�
	while(!TWI2Flag); 	//�ȴ�TWI�ж�
    TWI2Flag = 0;		//TWI2�жϱ�־λ��0
	US2CON3 = 0x88;	    //���͵�ַ��д���� ���ݻ���Ĵ������ֽ�		���λΪ0��д
	while(!TWI2Flag); 	//�ȴ�TWI�ж�,��������Ҳ������ж�
    TWI2Flag = 0;		//TWI2�жϱ�־λ��0
	US2CON3 = 0x2C;	    //��������,��������Ҳ������ж�	
	while(!TWI2Flag); 	//�ȴ�TWI�ж�
    TWI2Flag = 0;		//TWI2�жϱ�־λ��0
	US2CON3 = 0x06;	    //��������,��������Ҳ������ж�
    while(!TWI2Flag);	//�ȴ�TWI�ж�
    TWI2Flag = 0;		//TWI2�жϱ�־λ��0
	Delay(100);			//��ʱ
	US2CON1 |= 0x10; 	//����ֹͣ����	 
	Delay(100);			//��ʱ
	TWI2Flag = 0;		//TWI2�жϱ�־λ��0	
}						//*/
/*****************************************************
*�������ƣ�void SSI2_R(void)
*�������ܣ���SHT30������������
*��ڲ�����void
*���ڲ�����void
*****************************************************/

void SSI2_R(void)
 {
	US2CON1 |= 0x20;    //������ʼ����,ͬʱ������ж�
	while(!TWI2Flag); 	//�ȴ�TWI�ж�
    TWI2Flag = 0;		//TWI2�жϱ�־λ��0
	US2CON3 = 0x89;	    //���͵�ַ�������� 		���λΪ1�Ƕ�
	while(!TWI2Flag); 	//�ȴ�TWI�ж�,��������Ҳ������ж�
	TWI2Flag = 0;		//TWI2�жϱ�־λ��0
	US2CON0 |= 0x08; 	//ʹ��Ӧ��λ
//ȡ�¶ȵ�һ�ֽ�
	while(!TWI2Flag); 	//�ȴ�TWI�ж�,����8λ����Ҳ������ж�

	TWI2Flag = 0;		//TWI2�жϱ�־λ��0
	temp_vH	= US2CON3;	//ȡ�����յ���ֵ,���¶Ⱥ�ʪ��
//ȡ�¶ȵڶ��ֽ�
	while(!TWI2Flag); 	//�ȴ�TWI�ж�,����8λ����Ҳ������ж�
	TWI2Flag = 0;		//TWI2�жϱ�־λ��0
	temp_vL	= US2CON3;	//ȡ�����յ���ֵ,���¶Ⱥ�ʪ��
//ȡ�¶�У��ֵ
	while(!TWI2Flag); 	//�ȴ�TWI�ж�,����8λ����Ҳ������ж�
	TWI2Flag = 0;		//TWI2�жϱ�־λ��0
//	temp_v	= US2CON3;	//ȡ�����յ���ֵ,���¶Ⱥ�ʪ��

//ȡʪ�ȵ�һ�ֽ�
	while(!TWI2Flag); 	//�ȴ�TWI�ж�,����8λ����Ҳ������ж�
	TWI2Flag = 0;		//TWI2�жϱ�־λ��0
	humid_vH	= US2CON3;	//ȡ�����յ���ֵ,���¶Ⱥ�ʪ��
//ȡʪ�ȵڶ��ֽ�
	while(!TWI2Flag); 		//�ȴ�TWI�ж�,����8λ����Ҳ������ж�
	TWI2Flag = 0;			//TWI2�жϱ�־λ��0
	humid_vL	= US2CON3;	//ȡ�����յ���ֵ,���¶Ⱥ�ʪ��
	US2CON0 &= 0xF7; 		//�ر�Ӧ��λ   ��һ���ֽ�ֹͣ
//ȡʪ��У��ֵ
	while(!TWI2Flag); 	//�ȴ�TWI�ж�,����8λ����Ҳ������ж�
	TWI2Flag = 0;		//TWI2�жϱ�־λ��0
    TWI2Flag = 0;		//TWI2�жϱ�־λ��0
	Delay(100);			//��ʱ
	US2CON1 |= 0x10; 	//����ֹͣ����	*/   
	Delay(100);	
	  
	temp_vH<<=8;						//�����¶ȵĸ߰�λ,�����ư�λ					
	temp_vH= temp_vH+temp_vL;			//��ʡ�ԵͰ�λ,ʡ�ԵͰ�λ����ע�͵�


//	temp_vH=26850;						//�������������¶�

	if(temp_vH>16851)	//*******************���¶ȷ����ƶ˼���ʾ*************************
	{ 
		fs_temp=0;										//�帺����־
	//****************��������Ϊ��������¶�*****************************
		temp_vH = ((temp_vH/65535.0*175)-45)*10;		//Ҫ�Ӹ���������������
		if(temp_vH>600){temp_vH1=600;}					//���¶ȴ���60��,OLED������ʾ,�ƶ����ݱ���60��,��ֹ����,ԭ��Ϊ�ƶ����֧��60
		else{temp_vH1=temp_vH;}						   	//�¶�С��60����ʾ����ͬ��������,����ʾ�����ֻ�һ����ʾ.
		temp_H  = (temp_vH1/256);						//�����õĸ߰�λ
		temp_L  = (temp_vH1%256);	   					//�����õĵͰ�λ   */

		temp_shiwei	 = temp_vH%1000/100;				//��ʮλ ,��ʾ��	
		temp_gewei 	 = temp_vH%100/10;					//���λ ,��ʾ��
		temp_xiaoshu = temp_vH%10;						//��С��λ,��ʾ��
	} 
	else	 	//*************���¶ȷ����ƶ˼���ʾ***********************							   /65535
	{
		fs_temp=1;								//������־��1
		temp_vH = (temp_vH/65535.0*175)*10;		//Ҫ�Ӹ���������������
		temp_H  = 0xff;							//�����õĸ߰�λ
		temp_L	=0xff-(449-temp_vH);			//�����õĵͰ�λ   */

		temp_shiwei	 = (256-temp_L)/100;				//��ʮλ ,��ʾ��	
		temp_gewei 	 = (256-temp_L)%100/10;				//���λ ,��ʾ��
		temp_xiaoshu = (256-temp_L)%10;					//��С��λ,��ʾ��
	
	}


//	temp_shiwei	 = temp_vH%1000/100;			//��ʮλ 	
//	temp_gewei 	 = temp_vH%100/10;				//���λ
//	temp_xiaoshu = temp_vH%10;					//��С��λ


//����ʪ��
	humid_vH<<=8;
	humid_vH  = humid_vH+humid_vL;
	humid_vH  = humid_vH/655.35;
	humid_z   = humid_vH;  

	humid_shiwei	 = humid_vH/10;			//��ʮλ
	humid_gewei 	 = humid_vH%10;;		//���λ

}



/*****************************************************
*�������ƣ�void TWI2_Init(void)
*�������ܣ�TWI1 TWI2   ��ʼ��
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void TWI2_Init(void)
{
	OTCON  |= 0x80;   	//ѡ��TWI1ģʽ
	TMCON  |= 0x80;  	//��ѡһ����ΪTWI2ͨ��ģʽ
	US1CON0 = 0x80; 	//ʹ��TWI ʹ��Ӧ���־λ
	US1CON1 = 0x03; 	//---- xxxx  xΪʱ������  0x05Ϊ1M	 03Ϊ250K
	US2CON0 = 0x80; 	//ʹ��TWI ʹ��Ӧ���־λ
	US2CON1 = 0x03; 	//---- xxxx  xΪʱ������  0x05Ϊ1M	 03Ϊ250K
	
	IE2 |= 0x02;		//����һUSCI2�ж������ж�
	IE2 |= 0x01;		//USCI1�ж�Ҳ�����ж�
	EA = 1;	  			//�����ж�	  		//�����ж�
} 
void TWI1_Int() interrupt 15     //TWI1�жϺ���
{
	if(US1CON0&0x40)	 	//TWI�ж�
	{
		US1CON0 &= 0xbf;  	//�ж�����
		TWI1Flag = 1;		//TWI2�жϱ�־λ��1
	}	
}
 

 //�ж�����Ϊ1.���������ź�2.�������ַ֡3.���ջ���������֡
void TWI2_Int() interrupt 16     //TWI2�жϺ���
{
	if(US2CON0&0x40)	  	//TWI�ж�
	{
		US2CON0 &= 0xbf;  	//�ж�����
		TWI2Flag = 1; 		//TWI2�жϱ�־λ��1
	}	
}	
