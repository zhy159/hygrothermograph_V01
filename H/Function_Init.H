#ifndef _Function_Init_H_
#define _Function_Init_H_

#include "SC95F761x_C.H"
#include "intrins.H"
#define uchar unsigned char
#define uint unsigned int
extern uchar Uart_data;			//串口接收临时变量
extern uchar temp_H;			//温度值高8位
extern uchar temp_L;			//温度值低8位
extern uchar humid_z;			//湿度值
extern uchar sd_ztxh;    		//定义收到的状态序号变量   

extern bit test_bit; 			//引入外部定义传感器读完标志位
extern uint Delay_jg;  			//引入外部定义读取的间隔
extern uint Delay_S;


extern bit UartSendFlag; 		//发送中断标志位
extern bit UartReceiveFlag;		//接收中断标志位
extern bit fs_temp;				//为负数的变量

extern void IO_Init(void);

extern	void tuya_sjcl(void);				//涂鸦数据处理

extern void Timer_Test(void);
extern void Uart_Init(uint Freq,unsigned long int baud);		//初始化串口并设定 时钟频率 与 波特率
extern void Uart_Temp(void);									//串口上报温湿度
extern uchar jszl_qf(void);										//收到的数据判断函数
//extern void SSI0_Test(void);
//extern void SSI1_Test(void);

extern void SSI2_Test(void);									//I2C与SHT30通信测温湿度用
extern void SSI2_R(void);
extern void TWI2_Init(void);																
extern void Uart_temp_up(void);		//上传温度	
extern void Uart_humid_up(void);	//上传湿度	

extern char temp_shiwei;		//温度十位
extern char temp_gewei; 		//温度十位个位
extern char temp_xiaoshu; 		//温度十位小数位

extern char humid_shiwei;		//湿度十位
extern char humid_gewei;		//湿度个位

extern void Delay(uint time);  

extern uchar tuya_DataTab[15];	//定义一个收到模块的数据表格
extern void Uart_sxt(void);		//收到首心跳回复 
extern void Uart_hxt(void);		//收到一次以上心跳回复
extern void Uart_xtxx(void);	//MCU上报ID MCU版本 配网方式	,系统信息
extern void Uart_xtmk(void);	//回复为MCU上报与模块配合处理
extern void Uart_wififf(void);	//模块报告WiFi 工作状态收到后MCU回复

extern void OLED_Init(void);	//OLED初始化
extern void OLED_WR_Byte(uchar dat,uchar cmd);	//对OLED写临一个字节数据或指令 cmd：1，写诶数据；0，写入命令
extern void Write_IIC_Data(uchar IIC_Data);	  			//写数据
extern void  Write_IIC_Command(uchar IIC_Command);	  	//写入指令
extern void OLED_ShowString(uchar x,uchar y,uchar *chr);
//extern void OLED_ShowChar(uchar x,uchar y,uchar chr);


extern void OLED_ShowString1(uchar x,uchar y);//显示温度函数
extern void OLED_ShowString2(uchar x,uchar y);//显示湿度函数
extern void OLED_ShowChar(uchar x,uchar y,uchar chr);





#endif