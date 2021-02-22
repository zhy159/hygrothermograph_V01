#include "H/Function_Init.H"

//#define IapROM  0x00	  //0x00��ѡ��ROM������  0x02��ѡ��EEPROM������
//#define IapEPPROM  0x02	  //0x00��ѡ��ROM������  0x02��ѡ��EEPROM������
unsigned char code *IapAddr = 0x00;

void IAPWrite(uint Addr,uchar Value,uchar IAPArea);
void IAPPageErase(uint Addr,uchar IAPArea);
uchar IAPRead(uint Addr,uchar IAPArea);
uchar IapReadData = 0x00;   //��Ŷ�ȡ��IAP����

/*****************************************************
*�������ƣ�void IAP_Test(uchar Address,uchar IAPArea)
*�������ܣ�IAP����
*��ڲ�����Address,IAPArea
*���ڲ�����void
*****************************************************/
void IAP_Test(uint Address,uchar IAPArea)
{
    IAPPageErase(Address,IAPArea);   //ҳ����
	IAPWrite(Address,0xff,IAPArea);  //д����
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
*�������ƣ�void IAPWrite(uchar Addr,uchar Value,uchar IAPArea)
*�������ܣ�IAPд��ʼ��
*��ڲ�����Addr,Value,IAPArea
*���ڲ�����void
*****************************************************/
//IAPд����
void IAPWrite(uint Addr,uchar Value,uchar IAPArea)
{	
    bit temp = EA;
	EA = 0;
    IAPADE = IAPArea;   //IAPArea=0x00��ѡ��ROM������  IAPArea=0x02��ѡ��EEPROM������
	IAPDAT = Value;     //д������Data
	IAPADH = (unsigned char)((Addr >> 8));   //д���ַ�ĸ�8λ
	IAPADL = (unsigned char)Addr;            //д���ַ�ĵ�8λ
	IAPKEY = 0xF0;		//IAP������������ʱ��
    IAPCTL = 0X10;      //ִ�С�д���������������󣬽���flash��̲���
	IAPCTL |= 0x02;     //ִ�С�д��������������
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	IAPADE = 0x00;      //MOVCָ��ROM
	EA = temp;
}

/*****************************************************
*�������ƣ�void IAPPageErase(uint Addr,uchar IAPArea)
*�������ܣ�IAPҳ����
*��ڲ�����Addr,IAPArea
*���ڲ�����void
*****************************************************/
void IAPPageErase(uint Addr,uchar IAPArea)
{
	bit temp = EA;
	EA = 0;
	IAPADE = IAPArea;
	
	IAPADH = (unsigned char)((Addr >> 8)); //д��������׵�ַ��λ
    IAPADL = (unsigned char)Addr;          //д��������׵�ַ��λ
	
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
*�������ƣ�uchar IAPRead(uchar Addr,uchar IAPArea)
*�������ܣ�IAP����ʼ��
*��ڲ�����Addr,IAPArea
*���ڲ�����ReadValue
*****************************************************/
uchar IAPRead(uint Addr,uchar IAPArea)
{
	uchar ReadValue = 0x00;
    bit temp = EA;
	EA = 0;
	IAPADE = IAPArea;
	ReadValue = *(IapAddr+Addr); //��ȡ������
	IAPADE = 0x00;               //MOVCָ��ROM
	EA = temp;
	return ReadValue;
}
