#include "H/Function_Init.H"
bit xt=0;  	//首心跳标志号

void main(void)
{
	IO_Init();
	TWI2_Init();			//初始化I2C1与I2C2
	Timer_Test();
	OLED_Init(); 			//OLED屏初始化
	WDTCON |= 0x10;		    //清看门狗
   Uart_Init(32,9600);		//初始化串口并设定 时钟频率 与 波特率
   while(1)
   {	
		uchar dfxh; //定义答复序号
		if(Delay_jg>3000)	 //循环间隔
		{
			Delay_jg=0;
			Delay_S=0; 			//定时器清0
			SSI2_Test();		//发送SHT30测温湿的指令
			Delay_jg=0;			//循环间隔量数清0
			test_bit=0;	 		//测量完成标志位重新开始由定时器产生
			WDTCON |= 0x10;		    //清看门狗
			while(!test_bit);	//
			SSI2_R();			//读SHT30测量到的数据
			WDTCON |= 0x10;		    //清看门狗
			Uart_Temp();		//发送读到的温湿度
			OLED_ShowString(0,0,"Temperature:");//温度标志		
            OLED_ShowString1(70,2);//显示温度
			OLED_ShowString(0,4,"Humidity:");//温度标志
			OLED_ShowString2(70,6);//显示温度	
		} //*/
		dfxh = jszl_qf();	//读取状态字
		sd_ztxh=0;			//读完清变量********防止重复执行
		switch(dfxh)	   
		{
		 case 1:if(!xt){Uart_sxt();xt=1;} else{Uart_hxt();};//收到首次或非首次心跳，MCU相应回复
		 break;
		 case 2:Uart_xtxx(); 								//MCU上报ID MCU版本 配网方式,系统信息
		 break; 
		 case 3:Uart_xtmk();							//回复MCU上报与模块配合处理
		 break;
		 case 4:Uart_wififf();P00=0;P01=0;					//收到wifi为Smortconfig状态回复  两个灯都亮
		 break;
		 case 5:Uart_wififf();P00=1;P01=0;					//收到wifi为AP状态回复	白灯熄灭
		 break;
		 case 6:Uart_wififf();P00=0;P01=1;					//收到wifi配网成功但未边上路由  红灯熄灭
		 break;
		 case 7:Uart_wififf();P00=1;P01=1;					//收到wifi已连上路由器	 两个灯都是灭的
		 break;
		 case 8:Uart_wififf();P00=1;P01=1;;					//收到wifi已连上路由器且连接到云端  两个灯都是灭的
		 break;
		 default:
		 break; 		
		}
		WDTCON |= 0x10;		    //清看门狗

	}
}


