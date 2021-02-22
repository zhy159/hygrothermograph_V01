#include "H/Function_Init.H" 

void Uart_Init(uint Freq,unsigned long int baud);
bit UartSendFlag = 0; 		//发送中断标志位
bit UartReceiveFlag = 0;	//接收中断标志位
uchar Uart_data;

uchar tuya_DataTab[15];   //接收到的数据存放表格,最多15个
/*****************************************************
*函数名称：void Uart_Init(uint Freq,unsigned long int baud)
*函数功能：Uart中断初始化
*入口参数：Freq-主频，baud-波特率
*出口参数：void
*****************************************************/
void Uart_Init(uint Freq,unsigned long int baud)    //选择Timer1作为波特率信号发生器
{
	P2CON &= 0xFC;   //TX/RX设置为输入带上拉
	P2PH  |= 0x03;
	
	SCON  |= 0X50;   //设置通信方式为模式一，允许接收
	TMCON |= 0X02;
	TH1 = (Freq*1000000/baud)>>8;	  //波特率为T1的溢出时间；
	TL1 = Freq*1000000/baud;
	TR1 = 0;
	ET1 = 0;
	EUART = 1;     //开启Uart中断
	EA = 1;
}

void Uart_Temp(void)//发送读到的温湿度
{
	Uart_temp_up();		//上传温度到云
	Uart_humid_up();	//上传湿度到云
}

/*****************************************************
*函数名称：void UartInt(void) interrupt 4
*函数功能：Uart中断函数
*入口参数：void
*出口参数：void
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
		UartReceiveFlag = 1;//接收标志位置1
		Uart_data=SBUF;		//取收到的数
		tuya_sjcl();		//涂鸦数据处理
	}	
}
