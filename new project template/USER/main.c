#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "lcd.h"
#include "serial.h"


int main(void)
{	
	Led_Init();
	Serial_Init();
	LCD_Init();
	
	LCD_ShowString(30,40,200,24,24,"Mini STM32 ^_^");	
	LCD_ShowString(30,70,200,16,16,"TFTLCD TEST");
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,130,200,12,12,"2014/3/7");
	LCD_ShowSingleHZ(30,160,"Äã",CHN_font_12);
	while(1){
		red_on();
		delay_ms(300);
		red_off();
		delay_ms(300);
	}
}

