#include "H/Function_Init.H"

#if (IC_MODEL == SC95F7617 || IC_MODEL == SC95F7616 || IC_MODEL == SC95F7615)
unsigned int xdata PWMRD_40  _at_  0x1040;
unsigned int xdata PWMRD_41  _at_  0x1042;
unsigned int xdata PWMRD_42  _at_  0x1044;
unsigned int xdata PWMRD_43  _at_  0x1046;
unsigned int xdata PWMRD_50  _at_  0x1048;
unsigned int xdata PWMRD_51  _at_  0x104A;
unsigned int xdata PWMRD_52  _at_  0x104C;
unsigned int xdata PWMRD_53  _at_  0x104E;
#endif

#if (IC_MODEL == SC95F7613)
unsigned int xdata PWMRD_40  _at_  0x1040;
unsigned int xdata PWMRD_41  _at_  0x1042;
unsigned int xdata PWMRD_42  _at_  0x1044;
unsigned int xdata PWMRD_43  _at_  0x1046;
#endif

unsigned int xdata PWMRD_Temp;
void PWM_Init(void);
/*****************************************************
*函数名称：void PWM_Test(void)
*函数功能：PWM测试
*入口参数：void
*出口参数：void
*****************************************************/
void PWM_Test(void)
{
	PWM_Init();
	while(1)
	{
	}
}

/*****************************************************
*函数名称：void PWM_Init(void)
*函数功能：PWM独立模式初始化
*入口参数：void
*出口参数：void
*****************************************************/
void PWM_Init(void)
{
	//设置了周期为50us，占空比为50%的PWM波形
    PWMMOD = 0x00;           //独立模式，边沿对齐
	PWMCON = 0x3F;           //周期设置低8位,50us
    PWMCFG = 0x86;           //7:开关  5-4：时钟源选择  3-0：周期设置高4位	
	PWMRD_41 = 0x8000 | 0x320;     //开启PWM口，设置占空比
    IE1 |= 0x02;        //开启中断标志位
    EA = 1;
}

/*****************************************************
*函数名称：void PWM_Init(void)
*函数功能：PWM互补模式初始化
*入口参数：void
*出口参数：void
*****************************************************
void PWM_Init(void)
{
	//设置了周期为50us，占空比为50%的PWM波形
    PWMMOD = 0x0C;           //互补模式，中心对齐
	PWMCON = 0x3F;           //周期设置低8位,50us
    PWMCFG = 0x86;           //7:开关  5-4：时钟源选择  3-0：周期设置高4位	
	PWMRD_40 = 0x8000 | 0x320;     //开启PWM40口，设置占空比
    PWMRD_41 = 0xC000 ;            //开启PWM41口，输出反向
    PWMDFR = 0x88;                 //设置上升沿死区时间：4*PWMDFR[3:0]/fHRC  设置下降沿死区时间：4*PWMDFR[7:4]/fHRC
    IE1 |= 0x02;        //开启中断标志位
    EA = 1;
}
*/

/*****************************************************
*函数名称：void PWM_Interrup() interrupt 8
*函数功能：PWM中断服务函数
*入口参数：void
*出口参数：void
*****************************************************/
void PWM_Interrup() interrupt 8
{
    if(PWMCFG & 0x40)
    {
        PWMCFG &= ~0x40;  //清除中断标志位
        P04 = ~P04;       
    }
}