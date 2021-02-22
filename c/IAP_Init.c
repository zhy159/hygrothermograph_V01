#include "H/Function_Init.H"

//#define IapROM  0x00	  //0x00：选择ROM区操作  0x02：选择EEPROM区操作
//#define IapEPPROM  0x02	  //0x00：选择ROM区操作  0x02：选择EEPROM区操作
unsigned char code *IapAddr = 0x00;

void IAPWrite(uint Addr,uchar Value,uchar IAPArea);
void IAPPageErase(uint Addr,uchar IAPArea);
uchar IAPRead(uint Addr,uchar IAPArea);
uchar IapReadData = 0x00;   //存放读取的IAP数据

/*****************************************************
*函数名称：void IAP_Test(uchar Address,uchar IAPArea)
*函数功能：IAP测试
*入口参数：Address,IAPArea
*出口参数：void
*****************************************************/
void IAP_Test(uint Address,uchar IAPArea)
{
    IAPPageErase(Address,IAPArea);   //页擦除
	IAPWrite(Address,0xff,IAPArea);  //写数据
	IapReadData = IAPRead(Address,IAPArea);
	while(1)
	{
		if(IapReadData == 0xff)
		{
			P02 = ~P02;
		}
		else
		{
			P03 = ~P03;
		}
	}
}

/*****************************************************
*函数名称：void IAPWrite(uchar Addr,uchar Value,uchar IAPArea)
*函数功能：IAP写初始化
*入口参数：Addr,Value,IAPArea
*出口参数：void
*****************************************************/
//IAP写操作
void IAPWrite(uint Addr,uchar Value,uchar IAPArea)
{	
    bit temp = EA;
	EA = 0;
    IAPADE = IAPArea;   //IAPArea=0x00：选择ROM区操作  IAPArea=0x02：选择EEPROM区操作
	IAPDAT = Value;     //写入数据Data
	IAPADH = (unsigned char)((Addr >> 8));   //写入地址的高8位
	IAPADL = (unsigned char)Addr;            //写入地址的低8位
	IAPKEY = 0xF0;		//IAP开启保护控制时间
    IAPCTL = 0X10;      //执行“写入或快擦除操作命令”后，进入flash编程操作
	IAPCTL |= 0x02;     //执行“写入或快擦除操作命令”
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	IAPADE = 0x00;      //MOVC指向ROM
	EA = temp;
}

/*****************************************************
*函数名称：void IAPPageErase(uint Addr,uchar IAPArea)
*函数功能：IAP页擦除
*入口参数：Addr,IAPArea
*出口参数：void
*****************************************************/
void IAPPageErase(uint Addr,uchar IAPArea)
{
	bit temp = EA;
	EA = 0;
	IAPADE = IAPArea;
	
	IAPADH = (unsigned char)((Addr >> 8)); //写入待擦除首地址高位
    IAPADL = (unsigned char)Addr;          //写入待擦除首地址低位
	
	IAPKEY = 0XF0;
	IAPCTL = 0X20;
	IAPCTL |= 0X02;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
    _nop_();
	_nop_();
	_nop_();
	_nop_();
	IAPADE = 0x00;
	EA = temp;		
}

/*****************************************************
*函数名称：uchar IAPRead(uchar Addr,uchar IAPArea)
*函数功能：IAP读初始化
*入口参数：Addr,IAPArea
*出口参数：ReadValue
*****************************************************/
uchar IAPRead(uint Addr,uchar IAPArea)
{
	uchar ReadValue = 0x00;
    bit temp = EA;
	EA = 0;
	IAPADE = IAPArea;
	ReadValue = *(IapAddr+Addr); //读取的数据
	IAPADE = 0x00;               //MOVC指向ROM
	EA = temp;
	return ReadValue;
}
