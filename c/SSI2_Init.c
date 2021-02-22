#include "H/Function_Init.H"
//#include"H/OledFont.h"


uint temp_vH;		//引入外部温度变量
uint temp_vH1;		//用于传感器温度大于60时,上传云保持60
uint temp_vL;		//引入外部温度变量

uint humid_vH;		//引入外部湿度变量
uint humid_vL;		//引入外部湿度变量
uchar temp_H;		//温度值高8位
uchar temp_L;		//温度值低8位

uchar humid_z;		//湿度值
//float temp_vHxs;	//用于存点小数的温度中间值


bit TWI1Flag = 0;         //TWI1中断标志位
bit TWI2Flag = 0;         //TWI2中断标志位
bit test_bit=0;			  //读完一次SHT20的温湿度完整数据标志位

bit fs_temp;			//为负数的变量


char temp_shiwei;	//温度十位
char temp_gewei; 	//温度十位个位
char temp_xiaoshu; //温度十位小数位

char	humid_shiwei;	//湿度十位
char	humid_gewei;	  	//湿度个位


/*****************************************************
*函数名称：void Write_IIC_Data(unsigned char IIC_Data)
*函数功能：I2C点OLED屏用  发数据用
*入口参数：void
*出口参数：void
*****************************************************/

void Write_IIC_Data(uchar IIC_Data)	  //写数据
 {
	US1CON1 |= 0x20;    //产生起始条件,同时会产生中断
	while(!TWI1Flag); 	//等待TWI中断
	TWI1Flag = 0;		//TWI1中断标志位清0
	US1CON3 = 0x78;	    //发送地址及写命令 数据缓存寄存器高字节		最低位为0是写
	while(!TWI1Flag); 	//等待TWI中断,发完数据也会产生中断
    TWI1Flag = 0;		//TWI1中断标志位清0
	US1CON3 = 0x40;	    //表示后面发的是写数据
	while(!TWI1Flag); 	//等待TWI中断
    TWI1Flag = 0;		//TWI1中断标志位清0
	US1CON3 = IIC_Data;	//发送数据,发完数据也会产生中断
    while(!TWI1Flag);	//等待TWI中断
    TWI1Flag = 0;		//TWI2中断标志位清0
	Delay(100);			//延时
	US1CON1 |= 0x10; 	//产生停止条件	 可能也产生了中断与规格书不符*/   
	Delay(100);			//延时
	TWI1Flag = 0;		//TWI1中断标志位清0  ***********多清一次中断标志,发完停止可能也进入了中断,防止发不出第一帧数据(地址)
}
/*****************************************************
*函数名称：Write_IIC_Command(unsigned char IIC_Command)
*函数功能：I2C点OLED屏用  发指令用
*入口参数：void
*出口参数：void
*****************************************************/
 
void  Write_IIC_Command(uchar IIC_Command)	  //写入指令
 {
	US1CON1 |= 0x20;    //产生起始条件,同时会产生中断
	while(!TWI1Flag); 	//等待TWI中断
    TWI1Flag = 0;		//TWI1中断标志位清0
	US1CON3 = 0x78;	    //发送地址及写命令 数据缓存寄存器高字节		最低位为0是写
	while(!TWI1Flag); 	//等待TWI中断,发完数据也会产生中断
    TWI1Flag = 0;		//TWI1中断标志位清0
	US1CON3 = 0x00;	    //表示后面发的是写数据
	while(!TWI1Flag); 	//等待TWI中断
    TWI1Flag = 0;		//TWI1中断标志位清0
	US1CON3 = IIC_Command;	//发送数据,发完数据也会产生中断
    while(!TWI1Flag);	//等待TWI中断
    TWI1Flag = 0;		//TWI1中断标志位清0
	Delay(100);			//延时
	US1CON1 |= 0x10; 	//产生停止条件 
	Delay(100);			//延时
	TWI1Flag = 0;		//TWI1中断标志位清0  ***********多清一次中断标志,发完停止可能也进入了中断,防止发不出第一帧数据(地址)

} 			  //*/






/*****************************************************
*函数名称：void SSI2_Test(void)
*函数功能：SSI2测试		发送SHT30测温湿的指令
*入口参数：void
*出口参数：void
*****************************************************/

void SSI2_Test(void)
 {
	US2CON1 |= 0x20;    //产生起始条件,同时会产生中断
	while(!TWI2Flag); 	//等待TWI中断
    TWI2Flag = 0;		//TWI2中断标志位清0
	US2CON3 = 0x88;	    //发送地址及写命令 数据缓存寄存器高字节		最低位为0是写
	while(!TWI2Flag); 	//等待TWI中断,发完数据也会产生中断
    TWI2Flag = 0;		//TWI2中断标志位清0
	US2CON3 = 0x2C;	    //发送数据,发完数据也会产生中断	
	while(!TWI2Flag); 	//等待TWI中断
    TWI2Flag = 0;		//TWI2中断标志位清0
	US2CON3 = 0x06;	    //发送数据,发完数据也会产生中断
    while(!TWI2Flag);	//等待TWI中断
    TWI2Flag = 0;		//TWI2中断标志位清0
	Delay(100);			//延时
	US2CON1 |= 0x10; 	//产生停止条件	 
	Delay(100);			//延时
	TWI2Flag = 0;		//TWI2中断标志位清0	
}						//*/
/*****************************************************
*函数名称：void SSI2_R(void)
*函数功能：读SHT30测量到的数据
*入口参数：void
*出口参数：void
*****************************************************/

void SSI2_R(void)
 {
	US2CON1 |= 0x20;    //产生起始条件,同时会产生中断
	while(!TWI2Flag); 	//等待TWI中断
    TWI2Flag = 0;		//TWI2中断标志位清0
	US2CON3 = 0x89;	    //发送地址及读命令 		最低位为1是读
	while(!TWI2Flag); 	//等待TWI中断,发完数据也会产生中断
	TWI2Flag = 0;		//TWI2中断标志位清0
	US2CON0 |= 0x08; 	//使能应答位
//取温度第一字节
	while(!TWI2Flag); 	//等待TWI中断,接收8位数据也会产生中断

	TWI2Flag = 0;		//TWI2中断标志位清0
	temp_vH	= US2CON3;	//取出接收到的值,先温度后湿度
//取温度第二字节
	while(!TWI2Flag); 	//等待TWI中断,接收8位数据也会产生中断
	TWI2Flag = 0;		//TWI2中断标志位清0
	temp_vL	= US2CON3;	//取出接收到的值,先温度后湿度
//取温度校验值
	while(!TWI2Flag); 	//等待TWI中断,接收8位数据也会产生中断
	TWI2Flag = 0;		//TWI2中断标志位清0
//	temp_v	= US2CON3;	//取出接收到的值,先温度后湿度

//取湿度第一字节
	while(!TWI2Flag); 	//等待TWI中断,接收8位数据也会产生中断
	TWI2Flag = 0;		//TWI2中断标志位清0
	humid_vH	= US2CON3;	//取出接收到的值,先温度后湿度
//取湿度第二字节
	while(!TWI2Flag); 		//等待TWI中断,接收8位数据也会产生中断
	TWI2Flag = 0;			//TWI2中断标志位清0
	humid_vL	= US2CON3;	//取出接收到的值,先温度后湿度
	US2CON0 &= 0xF7; 		//关闭应答位   下一个字节停止
//取湿度校验值
	while(!TWI2Flag); 	//等待TWI中断,接收8位数据也会产生中断
	TWI2Flag = 0;		//TWI2中断标志位清0
    TWI2Flag = 0;		//TWI2中断标志位清0
	Delay(100);			//延时
	US2CON1 |= 0x10; 	//产生停止条件	*/   
	Delay(100);	
	  
	temp_vH<<=8;						//读出温度的高八位,需左移八位					
	temp_vH= temp_vH+temp_vL;			//可省略低八位,省略低八位把这注释掉


//	temp_vH=26850;						//调试用来假设温度

	if(temp_vH>16851)	//*******************正温度发送云端及显示*************************
	{ 
		fs_temp=0;										//清负数标志
	//****************以下三句为不输出负温度*****************************
		temp_vH = ((temp_vH/65535.0*175)-45)*10;		//要加个点零否则计算会出错
		if(temp_vH>600){temp_vH1=600;}					//当温度大于60度,OLED本地显示,云端数据保持60度,防止出错,原因为云端最大支持60
		else{temp_vH1=temp_vH;}						   	//温度小于60度显示与云同样的数据,即显示屏与手机一样显示.
		temp_H  = (temp_vH1/256);						//发云用的高八位
		temp_L  = (temp_vH1%256);	   					//发云用的低八位   */

		temp_shiwei	 = temp_vH%1000/100;				//求十位 ,显示用	
		temp_gewei 	 = temp_vH%100/10;					//求个位 ,显示用
		temp_xiaoshu = temp_vH%10;						//求小数位,显示用
	} 
	else	 	//*************负温度发送云端及显示***********************							   /65535
	{
		fs_temp=1;								//负数标志置1
		temp_vH = (temp_vH/65535.0*175)*10;		//要加个点零否则计算会出错
		temp_H  = 0xff;							//发云用的高八位
		temp_L	=0xff-(449-temp_vH);			//发云用的低八位   */

		temp_shiwei	 = (256-temp_L)/100;				//求十位 ,显示用	
		temp_gewei 	 = (256-temp_L)%100/10;				//求个位 ,显示用
		temp_xiaoshu = (256-temp_L)%10;					//求小数位,显示用
	
	}


//	temp_shiwei	 = temp_vH%1000/100;			//求十位 	
//	temp_gewei 	 = temp_vH%100/10;				//求个位
//	temp_xiaoshu = temp_vH%10;					//求小数位


//计算湿度
	humid_vH<<=8;
	humid_vH  = humid_vH+humid_vL;
	humid_vH  = humid_vH/655.35;
	humid_z   = humid_vH;  

	humid_shiwei	 = humid_vH/10;			//求十位
	humid_gewei 	 = humid_vH%10;;		//求个位

}



/*****************************************************
*函数名称：void TWI2_Init(void)
*函数功能：TWI1 TWI2   初始化
*入口参数：void
*出口参数：void
*****************************************************/
void TWI2_Init(void)
{
	OTCON  |= 0x80;   	//选择TWI1模式
	TMCON  |= 0x80;  	//三选一设置为TWI2通信模式
	US1CON0 = 0x80; 	//使能TWI 使能应答标志位
	US1CON1 = 0x03; 	//---- xxxx  x为时钟速率  0x05为1M	 03为250K
	US2CON0 = 0x80; 	//使能TWI 使能应答标志位
	US2CON1 = 0x03; 	//---- xxxx  x为时钟速率  0x05为1M	 03为250K
	
	IE2 |= 0x02;		//三合一USCI2中断允许中断
	IE2 |= 0x01;		//USCI1中断也允许中断
	EA = 1;	  			//打开总中断	  		//打开总中断
} 
void TWI1_Int() interrupt 15     //TWI1中断函数
{
	if(US1CON0&0x40)	 	//TWI中断
	{
		US1CON0 &= 0xbf;  	//中断清零
		TWI1Flag = 1;		//TWI2中断标志位置1
	}	
}
 

 //中断条件为1.发送启动信号2.发送完地址帧3.接收或发送完数据帧
void TWI2_Int() interrupt 16     //TWI2中断函数
{
	if(US2CON0&0x40)	  	//TWI中断
	{
		US2CON0 &= 0xbf;  	//中断清零
		TWI2Flag = 1; 		//TWI2中断标志位置1
	}	
}	
