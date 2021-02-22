#include "H/Function_Init.H"
bit xt=0;  	//��������־��

void main(void)
{
	IO_Init();
	TWI2_Init();			//��ʼ��I2C1��I2C2
	Timer_Test();
	OLED_Init(); 			//OLED����ʼ��
	WDTCON |= 0x10;		    //�忴�Ź�
   Uart_Init(32,9600);		//��ʼ�����ڲ��趨 ʱ��Ƶ�� �� ������
   while(1)
   {	
		uchar dfxh; //��������
		if(Delay_jg>3000)	 //ѭ�����
		{
			Delay_jg=0;
			Delay_S=0; 			//��ʱ����0
			SSI2_Test();		//����SHT30����ʪ��ָ��
			Delay_jg=0;			//ѭ�����������0
			test_bit=0;	 		//������ɱ�־λ���¿�ʼ�ɶ�ʱ������
			WDTCON |= 0x10;		    //�忴�Ź�
			while(!test_bit);	//
			SSI2_R();			//��SHT30������������
			WDTCON |= 0x10;		    //�忴�Ź�
			Uart_Temp();		//���Ͷ�������ʪ��
			OLED_ShowString(0,0,"Temperature:");//�¶ȱ�־		
            OLED_ShowString1(70,2);//��ʾ�¶�
			OLED_ShowString(0,4,"Humidity:");//�¶ȱ�־
			OLED_ShowString2(70,6);//��ʾ�¶�	
		} //*/
		dfxh = jszl_qf();	//��ȡ״̬��
		sd_ztxh=0;			//���������********��ֹ�ظ�ִ��
		switch(dfxh)	   
		{
		 case 1:if(!xt){Uart_sxt();xt=1;} else{Uart_hxt();};//�յ��״λ���״�������MCU��Ӧ�ظ�
		 break;
		 case 2:Uart_xtxx(); 								//MCU�ϱ�ID MCU�汾 ������ʽ,ϵͳ��Ϣ
		 break; 
		 case 3:Uart_xtmk();							//�ظ�MCU�ϱ���ģ����ϴ���
		 break;
		 case 4:Uart_wififf();P00=0;P01=0;					//�յ�wifiΪSmortconfig״̬�ظ�  �����ƶ���
		 break;
		 case 5:Uart_wififf();P00=1;P01=0;					//�յ�wifiΪAP״̬�ظ�	�׵�Ϩ��
		 break;
		 case 6:Uart_wififf();P00=0;P01=1;					//�յ�wifi�����ɹ���δ����·��  ���Ϩ��
		 break;
		 case 7:Uart_wififf();P00=1;P01=1;					//�յ�wifi������·����	 �����ƶ������
		 break;
		 case 8:Uart_wififf();P00=1;P01=1;;					//�յ�wifi������·���������ӵ��ƶ�  �����ƶ������
		 break;
		 default:
		 break; 		
		}
		WDTCON |= 0x10;		    //�忴�Ź�

	}
}


