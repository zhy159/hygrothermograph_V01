#include "H/Function_Init.H"

unsigned char xdata LCDRAM[28]  _at_  0x1000;
void LCD_Init(void);
void LED_Init(void);
void PxVO_Init(void);
	
/*****************************************************
*函数名称：void LCD_Test(void)
*函数功能：LCD/LED测试
*入口参数：void
*出口参数：void
*****************************************************/
void LCD_LED_Test(void)
{
	LCD_Init();
//	LED_Init();
	while(1)
	{
	}
}
/*****************************************************
*函数名称：void LCD_Init(void)
*函数功能：LCD初始化
*入口参数：void
*出口参数：void
*****************************************************/
void LCD_Init(void)
{
	unsigned int i;
	DDRCON = 0x8F;    //-xyy zzzz  x:LCD/LED模式 y:占空比  z:LCD电压调节
	PxVO_Init();
	OTCON |= 0x04;    //---- xxyz  x:LCD分压电阻 y:复位管脚选择 z:LCD偏置电压
	for(i=0; i<8; i++)
	{
		LCDRAM[i] = 0xff;
	}
}

/*****************************************************
*函数名称：void LED_Init(void)
*函数功能：LED初始化
*入口参数：void
*出口参数：void
*****************************************************/
void LED_Init(void)
{
	unsigned int i;
	DDRCON = 0xC0;    //-xyy zzzz  x:LCD/LED模式 y:占空比1/8:00 1/6:01 1/5:10 1/4:11  z:LCD电压调节
	PxVO_Init();
	OTCON |= 0x00;    //---- xxyz  x:LCD分压电阻 y:复位管脚选择 z:LCD偏置电压
	for(i=0; i<8; i++)
	{
		LCDRAM[i] = 0xff;
	}
}

/*****************************************************
*函数名称：void PxVO_Init(void)
*函数功能：显示驱动输出口初始化
*入口参数：void
*出口参数：void
*****************************************************/
void PxVO_Init(void)
{
	P0VO = 0xFF;
	P1VO = 0xFF;
	P2VO = 0xFF;
	P3VO = 0xFF;
}