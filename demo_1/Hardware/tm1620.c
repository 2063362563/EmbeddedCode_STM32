
#include "stm32f10x.h"                  // Device header


#include "tm1620.h"
#include "delay.h"
#include <intrins.h>
#include <string.h>

/**************** 显示模式命令 ****************/
#define		GRID4_SEG13 0x00	// 4倍13段
#define		GRID5_SEG12 0x01	// 5倍12段
#define		GRID6_SEG11 0x02	// 6倍11段
#define		GRID7_SEG10 0x03	// 7倍10段
/**************** 显示地址命令 ****************/
#define		ADD_00H		0xC0	// 显示地址GRID1
#define		ADD_01H		0xC1	// 显示地址GRID1
#define		ADD_02H		0xC2	// 显示地址GRID2
#define		ADD_03H		0xC3	// 显示地址GRID2
#define		ADD_04H		0xC4	// 显示地址GRID3
#define		ADD_05H		0xC5	// 显示地址GRID3
#define		ADD_06H		0xC6	// 显示地址GRID4
#define		ADD_07H		0xC7	// 显示地址GRID4
#define		ADD_08H		0xC8	// 显示地址GRID5
#define		ADD_09H		0xC9	// 显示地址GRID5
#define		ADD_0AH		0xCA	// 显示地址GRID6
#define		ADD_0BH		0xCB	// 显示地址GRID6
#define		ADD_0CH		0xCC	// 显示地址GRID7
#define		ADD_0DH		0xCD	// 显示地址GRID7


u8 code LED_Nume[10] = {NUM_0,NUM_1,NUM_2,NUM_3,NUM_4,NUM_5,NUM_6,NUM_7,NUM_8,NUM_9};	// 共阳数码管0-9的编码
u8 code LED_Lock[9]  = {CHR_L,CHR_O,CHR_C,CHR_K,0x00,0x00,0x00,0x00,0x00};	  			// LOCK
u8 code LED_Ulock[9] = {CHR_U,CHR_L,CHR_O,CHR_C,CHR_K,0x00,0x00,0x00,0x00}; 			// ULOCK
u8 code LED_Open[4]  = {CHR_O,CHR_P,CHR_E,CHR_N};			// OPEN
u8 code LED_TEST[4]  = {CHR_A,CHR_N,CHR_Y,CHR_J};			// TSET
u8 code LED_ANDY[7]  = {NUM_0,NUM_1,NUM_2,NUM_3,NUM_4,NUM_5,NUM_6};		   		// 卜卜卜卜
u8 code LED_Blank[4] = {0x40,0x40,0x40,0x40};				// ---- BLANK
u8 code LED_Blank1[4]= {0x40,0x00,0x00,0x00};				//    - BLANK1
u8 code LED_Blank2[4]= {0x40,0x40,0x00,0x00};				//   -- BLANK2
u8 code LED_0000[4]  = {NUM_0,NUM_0,NUM_0,0x00};			// 0000
u8 code LED_ERR[4]   = {0x00,CHR_r,CHR_r,CHR_E};			//  RRE
u8 code LED_ERR2[4]  = {NUM_2,CHR_r,CHR_r,CHR_E};			// 2RRE
u8 code LED_ERR3[4]  = {NUM_3,CHR_r,CHR_r,CHR_E};			// 3RRE
u8 code LED_ERR6[4]  = {NUM_6,CHR_r,CHR_r,CHR_E};			// 6RRE
u8 code LED_ADD[4]   = {0x08,CHR_d,CHR_d,CHR_A};			// -ddA
u8 code LED_DEL[4]   = {0x08,CHR_L,CHR_E,CHR_d,};			// -LEd
u8 code LED_LOAD[4]  = {CHR_d,CHR_A,CHR_O,CHR_L};		   	// DAOL
u8 code LED_PROG[4]  = {CHR_G,CHR_O,CHR_r,CHR_P};		   	// GORP
u8 code LED_FFFF[4]  = {CHR_F,CHR_F,CHR_F,CHR_F};		   	// FFFF
u8 code LED_001[4]   = {NUM_1,NUM_0,NUM_0,0x00};			// 001
u8 code LED_SET[4]   = {0x08,0x08,0x00,0x00};				//   --
u8 code LED_SET1[4]  = {0x08,0x00,0x00,0x00};				//    -
u8 code *LED_STR[] = {(u8*)LED_Lock,(u8*)LED_Ulock,LED_Open,LED_TEST,LED_ANDY,LED_Blank,LED_Blank1,LED_Blank2,
						 LED_0000,LED_ERR,LED_ERR2,LED_ERR3,LED_ERR6,LED_ADD,LED_DEL,LED_SET,LED_LOAD,LED_PROG,LED_FFFF, LED_001,LED_SET1};

u8  InpBuf[12];			
u8 LED_Buf[8];		// 数码显示缓存
						 
//------------- 功能：向TM1620发送8位数据,从低位开始 --------------//
void LED_SendByte(u8 dat)
{
	u8 i;

	LED_STB = 0;
	for(i = 0; i < 8; i++)
	{
		LED_SCL = 0;			_nop_(); _nop_(); _nop_(); _nop_(); 
		LED_SDI = dat & 0x01;	_nop_(); _nop_(); _nop_(); _nop_(); 
		LED_SCL = 1;			_nop_(); _nop_(); _nop_(); _nop_();
		dat >>= 1;				_nop_(); _nop_(); _nop_(); _nop_();		
	}
}

//----------------- 功能：向TM1620发送命令 -----------------//
void LED_SendCmd(u8 cmd)	
{
	LED_STB = 1;
	_nop_(); _nop_(); _nop_(); _nop_();
	LED_STB = 0;					// 在STB下降沿后收到的第一个数据为指令
	_nop_(); _nop_(); _nop_(); _nop_();
	LED_SendByte(cmd);
}			    

//------------ 初始化TM1602显示 --------------//
void LED_Init(void)
{
	LED_STB = 0;
	LED_SendCmd(GRID7_SEG10);		// 设置显示模式，7位10段模式
	LED_SendCmd(0x40);				// 设置数据命令, 采用地址自动加1模式
	LED_SendCmd(0xC0);				// 设置显示地址，从00H开始
	LED_SendCmd(LED_BRIGHT); //0x89	// 显示控制命令，打开显示并设置位最亮
	LED_STB = 1;
	
	memset(LED_Buf, 0x00, sizeof(LED_Buf));
}

void LED_SendChar (u8 dat)
{
	u8 val;

	if ((dat>=0x30) && (dat<=0x39))	// 处理数字
	{
		dat -= 0x30;
		val = LED_Nume[dat];
	}
	else if (dat == '.')
		val = LED_POINT;
	else if (dat == '*')
		val = LED_STAR;				// 星号 卜字形
	else if (dat == '-')
		val = LED_BAR;				// 
	else
		val = LED_BLANK;
	LED_SendByte(val);			
	LED_SendByte(0x00);
}

void LED_RefreshBuf (void)
{
	u8 i;

	LED_SendCmd(0xC0);
	for (i = 0; i < 7; i++)	
	{
		LED_SendByte(LED_Buf[i]);
		LED_SendByte(0x00);
	}
	LED_SendCmd(LED_BRIGHT);
}

void LED_ClearBuf (void)
{
	u8 led;
	
	led = LED_Buf[3];
	memset (LED_Buf, LED_BLANK, sizeof(LED_Buf));	
	LED_Buf[3] = led;
	LED_RefreshBuf();
}

void LED_SetVal (u8 led)
{
	LED_Buf[3] |= led;
	LED_Buf[3] &= LED0 | LED1 | LED2;
	LED_RefreshBuf();
}

void LED_ClrVal (u8 led)
{
	LED_Buf[3] &= ~led;
	LED_RefreshBuf();
}

void LED_SendNum (u8 *str, u8 mode, u8 delay)
{
  	u8 len;
	u8 i, j, k;
   	u8 buf[4];

	LED_SendCmd(0xC0);	
	if (mode == 0)						// 静态显示4位数据
	{
		for (i = 0; i < 4; i++)
			LED_SendChar(*(str+i));
		LED_SendCmd(LED_BRIGHT);
	}
	else if (mode == 1)
	{
	 	len = strlen(str);
		memset(buf, 0x00, 4);
		for (i = 0; i < 7; i++)	   		// 先清空4格显示
		{
			for (k = 0; k < delay; k++)
				Delay_ms(10);
			//LED_SendChar(buf[i]);
			LED_SendChar(0x00);
			LED_SendCmd(LED_BRIGHT);
		}
		for (i = 0; i < len; i++)
		{
			buf[3] = buf[2];
			buf[2] = buf[1];
			buf[1] = buf[0];
			//buf[0] = *(str+i);
			buf[0] = *str++;

			LED_SendCmd(0xC0);
		 	for (j = 0; j < 4; j++)
			  	LED_SendChar(buf[j]);
			LED_SendCmd(LED_BRIGHT);
			for (k = 0; k < delay; k++)
				Delay_ms(10);
		}
	}
	else if (mode == 2)				// 静态显示4位数据	不显示无效位0		
	{
		len = strlen(str);
		while(len)
			LED_SendChar(*(str+(--len)));
		LED_SendCmd(LED_BRIGHT);
	}		
	/*else if (mode == 2)
	{
		len = strlen(str);
		memset(buf, 0x00, 4);

		for (i = 0; i < len; i++)
		{
			buf[3] = buf[2];
			buf[2] = buf[1];
			buf[1] = buf[0];
			buf[0] = *(str+i);		 	
		}

		LED_SendCmd(0xC0);
		for (i = 0; i < 4; i++)
			 LED_SendChar(buf[i]);		
		LED_SendCmd(LED_BRIGHT);
	}*/
}

void LED_ShowSEL (void)
{
	LED_ClearBuf();
	LED_SendCmd(0xC0);
	LED_SendByte(LED_BAR);			
	LED_SendByte(0x00);
	LED_SendByte(CHR_L);			
	LED_SendByte(0x00);
	LED_SendByte(CHR_E);			
	LED_SendByte(0x00);
	LED_SendByte(CHR_S);		// 显示SEL		
	LED_SendByte(0x00);
	LED_SendCmd(LED_BRIGHT);
}

void LED_ShowP (void)
{
	LED_ClearBuf();
	LED_SendCmd(0xC0);
	LED_SendByte(0x00);			
	LED_SendByte(0x00);
	LED_SendByte(0x00);			
	LED_SendByte(0x00);
	LED_SendByte(0x00);			
	LED_SendByte(0x00);
	LED_SendByte(LED_P);		// 显示P。		
	LED_SendByte(0x00);
	LED_SendCmd(LED_BRIGHT);

}

/* mode: 0  1 */
void LED_SendString (enum LED_Str_Typ str, u8 mode, u8 delay)
{
	u8 i, j;
	u8 buf[7];
	u8 len;

	if ((str==str_lock) || (str == str_ulock))
		len = 9;
	else 
		len = 7;
   	memset(buf, 0x00, 7); 	
	LED_SendCmd(0xC0);
	if (mode == 0) 			// 静态显示
	{
		if ((str==str_open) || (str==str_test) || (str==str_andy))
		{
			for (i = 0; i < 7; i++)
			{
				LED_SendByte(*(LED_STR[str]+3-i));			
				LED_SendByte(0x00);
			}
		}
		else
		{
			for (i = 0; i < 7; i++)
			{	
				LED_SendByte(*(LED_STR[str]+i));			
				LED_SendByte(0x00);
			}
		}
		LED_SendCmd(LED_BRIGHT);
	}
	else if (mode == 1)			// 动态显示
	{
		for (i = 0; i < 7; i++)
			LED_SendChar(buf[i]);
		LED_SendCmd(LED_BRIGHT);
			
		for (i = 0; i < len; i++)
		{
			buf[6] = buf[5];
			buf[5] = buf[4];
			buf[4] = buf[3];
			
			buf[3] = buf[2];
			buf[2] = buf[1];
			buf[1] = buf[0];
			if (str == str_lock)
				buf[0] = LED_Lock[i];
			else if (str == str_ulock)
				buf[0] = LED_Ulock[i];
			else if (str == str_open)
				buf[0] = LED_Open[i];
			else if (str == str_test)
				buf[0] = LED_TEST[i];
 			else if (str == str_andy)
				buf[0] = LED_ANDY[i];
			LED_SendCmd(0xC0);
			for (j = 7; j > 0; j--)
			{
				LED_SendByte(buf[j-1]);			
				LED_SendByte(0x00);
			}
			LED_SendCmd(LED_BRIGHT);
			for (j = 0; j < delay; j++)
				Delay_ms(10);		 
		}
	}
}
