#include "H/Function_Init.H" 

void Uart_SendOut(uchar Uart_data);  //串口发送函数
uchar tuya_DataTab1[2];   //接收到的数据存放表格,最多15个
uchar jyh_temp;
uchar Uart_data1;//定义两个帧头识别的变量
uchar a_ls;	
uchar sd_ztxh;    //定义收到的状态序号变量 

void Uart_sxt(void)	//收到首心跳回复55 AA 03 00 00 01 00 03	 7位数据+校验
{ 					   
 uchar a_Ls;	
 uchar uart_tab[]={0x55,0xAA,0x03,0x00,0x00,0x01,0x00,0x03};																	

	for(a_Ls=0;a_Ls<=7;a_Ls++) 		//发送字节数量-1
	{
	Uart_SendOut(uart_tab[a_Ls]);
	} 
}  
void Uart_hxt(void)	//收一次以上心跳回复 7位数据+校验 0x55,0xAA,0x03,0x00,0x00,0x01,0x01,0x4
{ 					   
uchar a_Ls;	
 uchar uart_tab[]={0x55,0xAA,0x03,0x00,0x00,0x01,0x01,0x04};																	

	for(a_Ls=0;a_Ls<=7;a_Ls++) //发送字节数量-1
	{
	Uart_SendOut(uart_tab[a_Ls]);
	}  
}

void Uart_xtxx(void)//MCU上报ID MCU版本 配网方式	,系统信息	*********************************************
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


void Uart_xtmk(void)//回复为MCU上报与模块配合处理	*********************************************
{ 					   //55 AA 03 02 00 00 04
uchar a_Ls;	
 uchar uart_tab[]={0x55,0xAA,0x03,0x02,0x00,0x00,0x04};																	

	for(a_Ls=0;a_Ls<=6;a_Ls++)	   //发送字节数量-1
	{
	Uart_SendOut(uart_tab[a_Ls]);
	}
}


void Uart_wififf(void)//模块报告WiFi 工作状态收到后MCU回复	*********************************************
{ 					   	//55 AA 03 03 00 00 05
	uchar a_Ls;	
	uchar uart_tab[]={0x55,0xAA,0x03,0x03,0x00,0x00,0x05};																	

	for(a_Ls=0;a_Ls<=6;a_Ls++)	   //发送字节数量-1
	{
	Uart_SendOut(uart_tab[a_Ls]);
	} 
}
void Uart_temp_up(void)	//上传温度***************************************************************
{ 
			
	if(fs_temp)												 //负数标志位置位了,也就是温度是负的
	{
		uchar a_Ls;
		uchar uart_tab[]={0x55,0xAA,0x03,0x07,0x00,0x08,0x01,0x02,0x00,0x04,0xFF,0xFF,};	//12位后还有两位温度值+校验和
		jyh_temp=(temp_L+temp_H+0X55+0XAA+0X03+0X07+0X08+0X01+0X02+0X04+0XFF+0XFF);			//计算校验和,用uchar相加只会得256以下的数高位丢弃
		uart_tab[12]=temp_H;uart_tab[13]=temp_L;uart_tab[14]=jyh_temp;						//温度高低位及校验位存入发送的表格															
		for(a_Ls=0;a_Ls<=14;a_Ls++)	   //发送字节数量-1
		{
		Uart_SendOut(uart_tab[a_Ls]);
		}
	} 
	else												  //温度是正的
	{
		
	 	uchar a_Ls;
		uchar uart_tab[]={0x55,0xAA,0x03,0x07,0x00,0x08,0x01,0x02,0x00,0x04,0x00,0x00};	//12位后还有两位温度值+校验和
		jyh_temp=(temp_L+temp_H+0X55+0XAA+0X03+0X07+0X08+0X01+0X02+0X04);				//计算校验和,用uchar相加只会得256以下的数高位丢弃
		uart_tab[12]=temp_H;uart_tab[13]=temp_L;uart_tab[14]=jyh_temp;					//温度高低位及校验位存入发送的表格															
	
		for(a_Ls=0;a_Ls<=14;a_Ls++)	   //发送字节数量-1
		{
		Uart_SendOut(uart_tab[a_Ls]);
		}	


	
	}  //*/
}
	 


void Uart_humid_up(void)	//上传湿度 **************************************************************************
{ 
	uchar a_Ls;	
	uchar uart_tab[]={0x55,0xAA,0x03,0x07,0x00,0x08,0x02,0x02,0x00,0x04,0x00,0x00,0x00};	//13位后还有两位温度值+校验和
	jyh_temp=(humid_z+0X55+0XAA+0X03+0X07+0X08+0X02+0X02+0X04);								//计算校验和,用uchar相加只会得256以下的数高位丢弃
	uart_tab[13]=humid_z;uart_tab[14]=jyh_temp;												//湿度及校验位存入发送的表格
	for(a_Ls=0;a_Ls<=14;a_Ls++)	   //发送字节数量-1
	{
	Uart_SendOut(uart_tab[a_Ls]);
	}
}

void tuya_sjcl(void)//涂鸦数据处理接收函数******************************
{
			
 		UartReceiveFlag = 0;  	//接收标志位 清0,可以接收下个数据
		tuya_DataTab1[1]=tuya_DataTab1[0];
		tuya_DataTab1[0]=Uart_data;
		if((tuya_DataTab1[1]==0x55)&&(tuya_DataTab1[0]==0xAA))	 //收到55AA为帧头,放到帧头的位置
		{
			 tuya_DataTab[0]=tuya_DataTab1[1];
			 tuya_DataTab[1]=tuya_DataTab1[0];
			 Uart_data1=(tuya_DataTab[1]+tuya_DataTab[0]);
			 a_ls=2;		
		}
		else
		{ 			
		  if((a_ls>1)&&(a_ls<15))					 //最多可放15个ucher的数据
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
 void Uart_SendOut(uchar Uart_data)  //串口发送函数
 {
		SBUF = Uart_data;		   //						   1
		while(!UartSendFlag);  //等待发送完成标志位 置1
		UartSendFlag = 0;
}

//*******************************收到的数据判断函数**************************
uchar jszl_qf(void)
{
	if((tuya_DataTab[0]==0x55)&&(tuya_DataTab[1]==0xaa)&&(tuya_DataTab[2]==0x00)&&(tuya_DataTab[3]==0x00)&&
		(tuya_DataTab[4]==0x00)&&(tuya_DataTab[5]==0x00)&&(tuya_DataTab[6]==0xff))//55 AA 00 00 00 00 FF 
		{ sd_ztxh=1;  tuya_DataTab[6]=0x55;/*防止重复答复//*/ }					//收到首次或非首次心跳，MCU相应回复		
	if((tuya_DataTab[0]==0x55)&&(tuya_DataTab[1]==0xaa)&&(tuya_DataTab[2]==0x00)&&(tuya_DataTab[3]==0x01)&&
		(tuya_DataTab[4]==0x00)&&(tuya_DataTab[5]==0x00)&&(tuya_DataTab[6]==0x00))
		{ sd_ztxh=2;}										  					//MCU上报ID MCU版本 配网方式,系统信息
	if((tuya_DataTab[0]==0x55)&&(tuya_DataTab[1]==0xaa)&&(tuya_DataTab[2]==0x00)&&(tuya_DataTab[3]==0x02)&&
	(tuya_DataTab[4]==0x00)&&(tuya_DataTab[5]==0x00)&&(tuya_DataTab[6]==0x01))
		{sd_ztxh=3;	tuya_DataTab[6]=0x55;/*防止重复答复//*/	}					//回复MCU上报与模块配合处理
	if((tuya_DataTab[0]==0x55)&&(tuya_DataTab[1]==0xaa)&&(tuya_DataTab[2]==0x00)&&(tuya_DataTab[3]==0x03)&&
	(tuya_DataTab[4]==0x00)&&(tuya_DataTab[5]==0x01)&&(tuya_DataTab[6]==0x00)&&(tuya_DataTab[7]==0x03))
		{sd_ztxh=4;	tuya_DataTab[6]=0x55;/*防止重复答复//*/	}				  	//wifi连网状态为Smartconfig配网
	if((tuya_DataTab[0]==0x55)&&(tuya_DataTab[1]==0xaa)&&(tuya_DataTab[2]==0x00)&&(tuya_DataTab[3]==0x03)&&
	(tuya_DataTab[4]==0x00)&&(tuya_DataTab[5]==0x01)&&(tuya_DataTab[6]==0x01)&&(tuya_DataTab[7]==0x04))
		{sd_ztxh=5;	tuya_DataTab[6]=0x55;/*防止重复答复//*/	}				  	//wifi连网状态为AP配网
	if((tuya_DataTab[0]==0x55)&&(tuya_DataTab[1]==0xaa)&&(tuya_DataTab[2]==0x00)&&(tuya_DataTab[3]==0x03)&&
	(tuya_DataTab[4]==0x00)&&(tuya_DataTab[5]==0x01)&&(tuya_DataTab[6]==0x02)&&(tuya_DataTab[7]==0x05))
		{sd_ztxh=6;	tuya_DataTab[6]=0x55;/*防止重复答复//*/	}				  	//wif配网成功但未连上路由器	
	if((tuya_DataTab[0]==0x55)&&(tuya_DataTab[1]==0xaa)&&(tuya_DataTab[2]==0x00)&&(tuya_DataTab[3]==0x03)&&
	(tuya_DataTab[4]==0x00)&&(tuya_DataTab[5]==0x01)&&(tuya_DataTab[6]==0x03)&&(tuya_DataTab[7]==0x06))
		{sd_ztxh=7;	tuya_DataTab[6]=0x55;/*防止重复答复//*/	}				  	//已连上路由器	
	if((tuya_DataTab[0]==0x55)&&(tuya_DataTab[1]==0xaa)&&(tuya_DataTab[2]==0x00)&&(tuya_DataTab[3]==0x03)&&
	(tuya_DataTab[4]==0x00)&&(tuya_DataTab[5]==0x01)&&(tuya_DataTab[6]==0x04)&&(tuya_DataTab[7]==0x07))
		{sd_ztxh=8;	tuya_DataTab[6]=0x55;/*防止重复答复//*/	}				  	//已连上路由器且连接到云端
	
	
				  

	return  sd_ztxh;  //返回收到的状态序号
}