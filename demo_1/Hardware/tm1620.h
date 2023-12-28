
#ifndef __TM1620_H_
#define __TM1620_H_

/*
#define LED_BLANK	0x00  	// 空显示
#define	LED_POINT	0x80	// LED数码管小数点显示
#define	LED_STAR	0x70	// '*'
#define	LED_BAR		0x40	// '-'
#define	LED_BRIGHT	0x8F	// LED亮度
*/
/* 修改接口顺序后字码 */
#define LED_BLANK	0x00  	// 空显示
#define	LED_POINT	0x20	// LED数码管小数点显示
#define	LED_STAR	0x8A	// '*'
#define	LED_BAR		0x40	// '-'
#define LED_P		CHR_A	// 0xAF	// 'P.'
#define	LED_BRIGHT	0x88	// LED亮度	88-8F

#define	 SEG_A	0x40 	// 数码管a段
#define	 SEG_B	0x20	 // 数码管b段
#define	 SEG_C	0x08 	 // 数码管c段
#define	 SEG_D 	0x02	// 数码管d段
#define	 SEG_E	0x01 	// 数码管e段
#define	 SEG_F	0x80 	// 数码管f段
#define	 SEG_G	0x10 	// 数码管g段
#define	 SEG_P	0x04 	// 数码管圆点
/* 数字段码定义 */
#define  NUM_0  (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F        )
#define  NUM_1  (        SEG_B | SEG_C                                )
#define  NUM_2  (SEG_A | SEG_B         | SEG_D | SEG_E         | SEG_G)
#define  NUM_3  (SEG_A | SEG_B | SEG_C | SEG_D                 | SEG_G)
#define  NUM_4  (        SEG_B | SEG_C                 | SEG_F | SEG_G)
#define  NUM_5  (SEG_A         | SEG_C | SEG_D         | SEG_F | SEG_G)
#define  NUM_6  (SEG_A         | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define  NUM_7  (SEG_A | SEG_B | SEG_C                                )
#define  NUM_8  (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define  NUM_9  (SEG_A | SEG_B | SEG_C | SEG_D         | SEG_F | SEG_G)
/* 英文字母段码字义 */
#define	 CHR_A	(SEG_A | SEG_B | SEG_C         | SEG_E | SEG_F | SEG_G)
#define	 CHR_b	(                        SEG_D | SEG_E | SEG_F | SEG_G)
#define  CHR_C  (SEG_A                 | SEG_D | SEG_E | SEG_F        )
#define  CHR_d  (        SEG_B | SEG_C | SEG_D | SEG_E         | SEG_G)
#define  CHR_E  (SEG_A                 | SEG_D | SEG_E | SEG_F | SEG_G)
#define  CHR_F  (SEG_A                         | SEG_E | SEG_F | SEG_G)
#define  CHR_G  (SEG_A         | SEG_C | SEG_D | SEG_E | SEG_F        )
#define  CHR_H  (        SEG_B | SEG_C         | SEG_E | SEG_F | SEG_G)
#define  CHR_I  (        SEG_B | SEG_C                                )
#define  CHR_K  (        SEG_B | SEG_C         | SEG_E | SEG_F | SEG_G)		// K同H用
#define  CHR_L  (                        SEG_D | SEG_E | SEG_F        )
#define  CHR_N  (SEG_A | SEG_B | SEG_C         | SEG_E | SEG_F        )
#define  CHR_O  (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F        )
#define  CHR_P  (SEG_A | SEG_B                 | SEG_E | SEG_F | SEG_G)
#define  CHR_r  (                                SEG_E         | SEG_G)		
#define  CHR_S  (SEG_A         | SEG_C | SEG_D         | SEG_F | SEG_G)
#define  CHR_T  (SEG_A                         | SEG_E | SEG_F        )
#define  CHR_U  (        SEG_B | SEG_C | SEG_D | SEG_E | SEG_F        )
#define  CHR_Y  (        SEG_B | SEG_C | SEG_D         | SEG_F | SEG_G)

#define  CHR_J  (		 SEG_B | SEG_C | SEG_D 						  )

#define		LED0		SEG_P
#define		LED1		SEG_E
#define		LED2		SEG_D
#define		LED_FREE	LED0
#define		LED_BUSY	LED1
#define		LED_OK		LED2

typedef enum LED_Str_Typ
{
	str_lock = 0,
	str_ulock,
	str_open,
	str_andy,
	str_test,
	str_blank,
	str_blank_1,
	str_blank_2,
 	str_0000,
	str_err,
	str_err2,
	str_err3,
	str_err6,
	str_add,
	str_del,
	str_set,
	str_load,
	str_prog,
	str_ffff,
	str_001,
	str_set1
};

extern uint8_t InpBuf[12];		
extern u8 LED_Buf[8];		// 数码显示缓存
extern u8 code LED_Nume[10];

//extern void LED_SendByte(u8 dat);
extern void LED_ShowP(void);
extern void LED_ShowSEL(void);
extern void LED_SendByte(u8 dat);
extern void LED_SendCmd(u8 cmd);
extern void LED_Init(void);
extern void LED_ClearBuf(void);
extern void LED_RefreshBuf(void);
extern void LED_SetVal(u8 led);
extern void LED_ClrVal(u8 led);

extern void LED_SendChar(u8 dat);
extern void LED_SendNum(u8 *str, u8 mode, u8 delay);
extern void LED_SendString(enum LED_Str_Typ str, u8 mode, u8 delay);

#endif
