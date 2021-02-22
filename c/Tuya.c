#include "H/Function_Init.H" 

void Uart_SendOut(uchar Uart_data);  //���ڷ��ͺ���
uchar tuya_DataTab1[2];   //���յ������ݴ�ű��,���15��
uchar jyh_temp;
uchar Uart_data1;//��������֡ͷʶ��ı���
uchar a_ls;	
uchar sd_ztxh;    //�����յ���״̬��ű��� 

void Uart_sxt(void)	//�յ��������ظ�55 AA 03 00 00 01 00 03	 7λ����+У��
{ 					   
 uchar a_Ls;	
 uchar uart_tab[]={0x55,0xAA,0x03,0x00,0x00,0x01,0x00,0x03};																	

	for(a_Ls=0;a_Ls<=7;a_Ls++) 		//�����ֽ�����-1
	{
	Uart_SendOut(uart_tab[a_Ls]);
	} 
}  
void Uart_hxt(void)	//��һ�����������ظ� 7λ����+У�� 0x55,0xAA,0x03,0x00,0x00,0x01,0x01,0x4
{ 					   
uchar a_Ls;	
 uchar uart_tab[]={0x55,0xAA,0x03,0x00,0x00,0x01,0x01,0x04};																	

	for(a_Ls=0;a_Ls<=7;a_Ls++) //�����ֽ�����-1
	{
	Uart_SendOut(uart_tab[a_Ls]);
	}  
}

void Uart_xtxx(void)//MCU�ϱ�ID MCU�汾 ������ʽ	,ϵͳ��Ϣ	*********************************************
{ 
uchar a_Ls;	
 uchar uart_tab[]={
0x55,0xAA,0x03,0x01,0x00,0x2A,0x7B,0x22,0x70,0x22,0x3A,0x22,0x6C,0x71,0x6B,0x76,0x67,0x65,0x61,0x64,0x7A,		
0x30,0x7A,0x63,0x6A,0x6E,0x38,0x66,0x22,0x2C,0x22,0x76,0x22,0x3A,0x22,0x31,0x2E,0x30,0x2E,0x30,0x22,0x2C,0x22,	
0x6D,0x22,0x3A,0x30,0x7D,0x3B};	
	for(a_Ls=0;a_Ls<=48;a_Ls++)
	{
	Uart_SendOut(uart_tab[a_Ls]);
	}
}


void Uart_xtmk(void)//�ظ�ΪMCU�ϱ���ģ����ϴ���	*********************************************
{ 					   //55 AA 03 02 00 00 04
uchar a_Ls;	
 uchar uart_tab[]={0x55,0xAA,0x03,0x02,0x00,0x00,0x04};																	

	for(a_Ls=0;a_Ls<=6;a_Ls++)	   //�����ֽ�����-1
	{
	Uart_SendOut(uart_tab[a_Ls]);
	}
}


void Uart_wififf(void)//ģ�鱨��WiFi ����״̬�յ���MCU�ظ�	*********************************************
{ 					   	//55 AA 03 03 00 00 05
	uchar a_Ls;	
	uchar uart_tab[]={0x55,0xAA,0x03,0x03,0x00,0x00,0x05};																	

	for(a_Ls=0;a_Ls<=6;a_Ls++)	   //�����ֽ�����-1
	{
	Uart_SendOut(uart_tab[a_Ls]);
	} 
}
void Uart_temp_up(void)	//�ϴ��¶�***************************************************************
{ 
			
	if(fs_temp)												 //������־λ��λ��,Ҳ�����¶��Ǹ���
	{
		uchar a_Ls;
		uchar uart_tab[]={0x55,0xAA,0x03,0x07,0x00,0x08,0x01,0x02,0x00,0x04,0xFF,0xFF,};	//12λ������λ�¶�ֵ+У���
		jyh_temp=(temp_L+temp_H+0X55+0XAA+0X03+0X07+0X08+0X01+0X02+0X04+0XFF+0XFF);			//����У���,��uchar���ֻ���256���µ�����λ����
		uart_tab[12]=temp_H;uart_tab[13]=temp_L;uart_tab[14]=jyh_temp;						//�¶ȸߵ�λ��У��λ���뷢�͵ı��															
		for(a_Ls=0;a_Ls<=14;a_Ls++)	   //�����ֽ�����-1
		{
		Uart_SendOut(uart_tab[a_Ls]);
		}
	} 
	else												  //�¶�������
	{
		
	 	uchar a_Ls;
		uchar uart_tab[]={0x55,0xAA,0x03,0x07,0x00,0x08,0x01,0x02,0x00,0x04,0x00,0x00};	//12λ������λ�¶�ֵ+У���
		jyh_temp=(temp_L+temp_H+0X55+0XAA+0X03+0X07+0X08+0X01+0X02+0X04);				//����У���,��uchar���ֻ���256���µ�����λ����
		uart_tab[12]=temp_H;uart_tab[13]=temp_L;uart_tab[14]=jyh_temp;					//�¶ȸߵ�λ��У��λ���뷢�͵ı��															
	
		for(a_Ls=0;a_Ls<=14;a_Ls++)	   //�����ֽ�����-1
		{
		Uart_SendOut(uart_tab[a_Ls]);
		}	


	
	}  //*/
}
	 


void Uart_humid_up(void)	//�ϴ�ʪ�� **************************************************************************
{ 
	uchar a_Ls;	
	uchar uart_tab[]={0x55,0xAA,0x03,0x07,0x00,0x08,0x02,0x02,0x00,0x04,0x00,0x00,0x00};	//13λ������λ�¶�ֵ+У���
	jyh_temp=(humid_z+0X55+0XAA+0X03+0X07+0X08+0X02+0X02+0X04);								//����У���,��uchar���ֻ���256���µ�����λ����
	uart_tab[13]=humid_z;uart_tab[14]=jyh_temp;												//ʪ�ȼ�У��λ���뷢�͵ı��
	for(a_Ls=0;a_Ls<=14;a_Ls++)	   //�����ֽ�����-1
	{
	Uart_SendOut(uart_tab[a_Ls]);
	}
}

void tuya_sjcl(void)//Ϳѻ���ݴ�����պ���******************************
{
			
 		UartReceiveFlag = 0;  	//���ձ�־λ ��0,���Խ����¸�����
		tuya_DataTab1[1]=tuya_DataTab1[0];
		tuya_DataTab1[0]=Uart_data;
		if((tuya_DataTab1[1]==0x55)&&(tuya_DataTab1[0]==0xAA))	 //�յ�55AAΪ֡ͷ,�ŵ�֡ͷ��λ��
		{
			 tuya_DataTab[0]=tuya_DataTab1[1];
			 tuya_DataTab[1]=tuya_DataTab1[0];
			 Uart_data1=(tuya_DataTab[1]+tuya_DataTab[0]);
			 a_ls=2;		
		}
		else
		{ 			
		  if((a_ls>1)&&(a_ls<15))					 //���ɷ�15��ucher������
		  {			  	
		   	tuya_DataTab[a_ls]=tuya_DataTab1[0];			//
			a_ls++;
		  }
		  else
		  {
		  	a_ls=0;
		  }		
		} 
}
 void Uart_SendOut(uchar Uart_data)  //���ڷ��ͺ���
 {
		SBUF = Uart_data;		   //						   1
		while(!UartSendFlag);  //�ȴ�������ɱ�־λ ��1
		UartSendFlag = 0;
}

//*******************************�յ��������жϺ���**************************
uchar jszl_qf(void)
{
	if((tuya_DataTab[0]==0x55)&&(tuya_DataTab[1]==0xaa)&&(tuya_DataTab[2]==0x00)&&(tuya_DataTab[3]==0x00)&&
		(tuya_DataTab[4]==0x00)&&(tuya_DataTab[5]==0x00)&&(tuya_DataTab[6]==0xff))//55 AA 00 00 00 00 FF 
		{ sd_ztxh=1;  tuya_DataTab[6]=0x55;/*��ֹ�ظ���//*/ }					//�յ��״λ���״�������MCU��Ӧ�ظ�		
	if((tuya_DataTab[0]==0x55)&&(tuya_DataTab[1]==0xaa)&&(tuya_DataTab[2]==0x00)&&(tuya_DataTab[3]==0x01)&&
		(tuya_DataTab[4]==0x00)&&(tuya_DataTab[5]==0x00)&&(tuya_DataTab[6]==0x00))
		{ sd_ztxh=2;}										  					//MCU�ϱ�ID MCU�汾 ������ʽ,ϵͳ��Ϣ
	if((tuya_DataTab[0]==0x55)&&(tuya_DataTab[1]==0xaa)&&(tuya_DataTab[2]==0x00)&&(tuya_DataTab[3]==0x02)&&
	(tuya_DataTab[4]==0x00)&&(tuya_DataTab[5]==0x00)&&(tuya_DataTab[6]==0x01))
		{sd_ztxh=3;	tuya_DataTab[6]=0x55;/*��ֹ�ظ���//*/	}					//�ظ�MCU�ϱ���ģ����ϴ���
	if((tuya_DataTab[0]==0x55)&&(tuya_DataTab[1]==0xaa)&&(tuya_DataTab[2]==0x00)&&(tuya_DataTab[3]==0x03)&&
	(tuya_DataTab[4]==0x00)&&(tuya_DataTab[5]==0x01)&&(tuya_DataTab[6]==0x00)&&(tuya_DataTab[7]==0x03))
		{sd_ztxh=4;	tuya_DataTab[6]=0x55;/*��ֹ�ظ���//*/	}				  	//wifi����״̬ΪSmartconfig����
	if((tuya_DataTab[0]==0x55)&&(tuya_DataTab[1]==0xaa)&&(tuya_DataTab[2]==0x00)&&(tuya_DataTab[3]==0x03)&&
	(tuya_DataTab[4]==0x00)&&(tuya_DataTab[5]==0x01)&&(tuya_DataTab[6]==0x01)&&(tuya_DataTab[7]==0x04))
		{sd_ztxh=5;	tuya_DataTab[6]=0x55;/*��ֹ�ظ���//*/	}				  	//wifi����״̬ΪAP����
	if((tuya_DataTab[0]==0x55)&&(tuya_DataTab[1]==0xaa)&&(tuya_DataTab[2]==0x00)&&(tuya_DataTab[3]==0x03)&&
	(tuya_DataTab[4]==0x00)&&(tuya_DataTab[5]==0x01)&&(tuya_DataTab[6]==0x02)&&(tuya_DataTab[7]==0x05))
		{sd_ztxh=6;	tuya_DataTab[6]=0x55;/*��ֹ�ظ���//*/	}				  	//wif�����ɹ���δ����·����	
	if((tuya_DataTab[0]==0x55)&&(tuya_DataTab[1]==0xaa)&&(tuya_DataTab[2]==0x00)&&(tuya_DataTab[3]==0x03)&&
	(tuya_DataTab[4]==0x00)&&(tuya_DataTab[5]==0x01)&&(tuya_DataTab[6]==0x03)&&(tuya_DataTab[7]==0x06))
		{sd_ztxh=7;	tuya_DataTab[6]=0x55;/*��ֹ�ظ���//*/	}				  	//������·����	
	if((tuya_DataTab[0]==0x55)&&(tuya_DataTab[1]==0xaa)&&(tuya_DataTab[2]==0x00)&&(tuya_DataTab[3]==0x03)&&
	(tuya_DataTab[4]==0x00)&&(tuya_DataTab[5]==0x01)&&(tuya_DataTab[6]==0x04)&&(tuya_DataTab[7]==0x07))
		{sd_ztxh=8;	tuya_DataTab[6]=0x55;/*��ֹ�ظ���//*/	}				  	//������·���������ӵ��ƶ�
	
	
				  

	return  sd_ztxh;  //�����յ���״̬���
}