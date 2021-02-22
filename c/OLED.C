 #include"H/OledFont.h"
 #include "H/Function_Init.H"

 #define OLED_CMD  0	//写命令
 #define OLED_DATA 1	//写数据
 #define SIZE 16		//字符尺寸
 #define Max_Column	128 //最大列数

extern void OLED_ShowString(uchar x,uchar y,uchar *chr);
extern void OLED_ShowChar(uchar x,uchar y,uchar chr);



//************对OLED写临一个字节数据或指令 cmd：1，写诶数据；0，写入命令**************************************
void OLED_WR_Byte(uchar dat,uchar cmd)
{
	if(cmd) 
	{
       Write_IIC_Data(dat); //写入数据
	}
	else
	{
       Write_IIC_Command(dat); //写入命令
	}
}
//*****************清屏*****************
void OLED_Clear(void)  
{  
	unsigned char i,n;		    //定义变量
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //从0~7页依次写入
		OLED_WR_Byte (0x00,OLED_CMD);      //列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //列高地址  
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); //写入 0 清屏
	}
}
//********************设置原点*******************
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);				//写入  页地址   B0到B7
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);	//写入列高4位地址
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD);  		//写入列低4位地址+1
}
//******************指定的区域显示字符串************************************************
void OLED_ShowString(uchar x,uchar y,uchar *chr)
{
	uchar j=0; //定义变量
	while (chr[j]!='\0') //如果不是最后一个字符
	{		
		OLED_ShowChar(x,y,chr[j]); 	//显示字符
			x+=8; 					//列数加8 ，一个字符的列数占8
		if(x>120){x=0;y+=2;} 		//如果x超过128，切换页，从该页的第一列显示
			j++; 					//下一个字符
	}
}

 //******************************画字符*************************88
void OLED_ShowChar(uchar x,uchar y,uchar chr)
{      	
		uchar c=0,i=0;	
		c=chr-' ';									//获取字符的偏移量	
		if(x>Max_Column-1){x=0;y=y+2;} 				//如果列书超出了范围128，就从下2页的第0列开始
		if(SIZE ==16) 								//字符大小如果为 16 = 8*16
			{
			OLED_Set_Pos(x,y);						//从x y 开始画点
			for(i=0;i<8;i++)  						//循环8次 占8列
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA); 	//找出字符 c 的数组位置，先在第一页把列画完
			OLED_Set_Pos(x,y+1); 					//页数加1
			for(i=0;i<8;i++)  //循环8次
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA); //把第二页的列数画完
			}

}

  //*/

 void OLED_Init(void)//OLED初始化
{
	OLED_WR_Byte(0xAE,OLED_CMD);//关闭显示	 地址AE发数据0	
	OLED_WR_Byte(0x2e,OLED_CMD);//关闭滚动
	OLED_WR_Byte(0x00,OLED_CMD);//设置低列地址
	OLED_WR_Byte(0x10,OLED_CMD);//设置高列地址
	OLED_WR_Byte(0x40,OLED_CMD);//设置起始行地址  40~7FH
	OLED_WR_Byte(0xB0,OLED_CMD);//设置页地址

	OLED_WR_Byte(0x81,OLED_CMD); // 对比度设置，可设置亮度
	OLED_WR_Byte(0xFF,OLED_CMD);//  1~255  

	OLED_WR_Byte(0xA0,OLED_CMD);//X轴(左右)镜像与不镜像设置,为0XA0与0XA1
	OLED_WR_Byte(0xA7,OLED_CMD);//显示正常与反转设置；0xa7数据为0亮1灭   0xa6数据为1亮0灭

	OLED_WR_Byte(0xA8,OLED_CMD);//设置驱动路数(下一条数据)
	OLED_WR_Byte(0x3F,OLED_CMD);//1/64duty	 Y轴的点数,也就是多少行
	
	OLED_WR_Byte(0xC0,OLED_CMD);//为0xC0:从COM0到COM[N-1]扫描   为0xC8:COM[N-1]~COM0扫描 改变上下扫描方式,改变时显示的字符也会镜像,但位置不变
															   //上一行为Y轴(上下)镜像与不镜像设置
	OLED_WR_Byte(0xD3,OLED_CMD);//设置显示偏移
	OLED_WR_Byte(0x00,OLED_CMD);//无偏移
	
	OLED_WR_Byte(0xD5,OLED_CMD);//设置震荡器分频（默认）
	OLED_WR_Byte(0xF0,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//设置 area color mode off（没有）
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD6,OLED_CMD);//放大显示
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//设置 Pre-Charge Period（默认）
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//设置 com pin configuartion（默认）
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//设置 Vcomh，可调节亮度（默认）
	OLED_WR_Byte(0x30,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//设置OLED电荷泵
	OLED_WR_Byte(0x14,OLED_CMD);//开显示
	
	OLED_WR_Byte(0xA4,OLED_CMD);//设置全屏全亮:0xa4为RAM数据显示   0xa5点亮全屏
	OLED_WR_Byte(0xA6,OLED_CMD);//显示正常与反转设置；0xa7数据为0亮1灭   0xa6数据为1亮0灭 
	
//	OLED_WR_Byte(0x23,OLED_CMD);//设置闪烁
//	OLED_WR_Byte(0x00,OLED_CMD);//

 //**********以下是水平滚动的设置*****************************
/*	OLED_WR_Byte(0x27,OLED_CMD);//水平向左滚动	 0X26:从左往右滚动 0X27: 从右往左滚动
	OLED_WR_Byte(0x00,OLED_CMD);//虚拟字节
	OLED_WR_Byte(0x06,OLED_CMD);//起始页(行号0~7共8行)	 有可能两行共同显一个字符,要注间一起滚动,否则......
	OLED_WR_Byte(0x00,OLED_CMD);//滚动时间间隔
	OLED_WR_Byte(0x07,OLED_CMD);//终止页(行号0~7共8行
	OLED_WR_Byte(0x00,OLED_CMD);//虚拟字节
	OLED_WR_Byte(0xFF,OLED_CMD);//虚拟字节 
	OLED_WR_Byte(0x2F,OLED_CMD);//开启滚动	*/

	OLED_WR_Byte(0xAF,OLED_CMD);//开启OLED面板显示
	OLED_Clear();        //清屏
	OLED_Set_Pos(0,0); 	 //画点
}


 void OLED_ShowString1(uchar x,uchar y)		//显示温度
{	// OLED_ShowChar(x,y,45);				//显示负号
	if(fs_temp)								//如果温度为负
	{OLED_ShowChar(x-8,y,45);}				//显示负号
	else								   	
	{OLED_ShowChar(x-8,y,32);}				//否则不显示负号
	if(temp_shiwei!=0)						//如果十位是零,则不显示
	{OLED_ShowChar(x,y,temp_shiwei+'0');}	//不是0,显示温度的十位
	else{OLED_ShowChar(x,y,32);}			//为0不显示,空格的ASCII的值32	  */
	OLED_ShowChar(x+8,y,temp_gewei+'0'); 	//显示温度的个位
	OLED_ShowChar(x+16,y,14+' '); 			//显示小数点
	OLED_ShowChar(x+24,y,temp_xiaoshu+'0'); //显示温度的小数位
	OLED_ShowChar(x+32,y,95+' '); 			//显示摄氏度符号的前半部分
	OLED_ShowChar(x+40,y,96+' '); 			//显示摄氏度符号的前后部分	
}  //*/

 void OLED_ShowString2(uchar x,uchar y)		//显示湿度
{
	OLED_ShowChar(x,y,humid_shiwei+'0'); 	//显示第三个数的ASCII码字符
	OLED_ShowChar(x+8,y,humid_gewei+'0'); 	//显示第三个数的ASCII码字符
	OLED_ShowChar(x+16,y,5+' '); 	        //显示%

}  //*/