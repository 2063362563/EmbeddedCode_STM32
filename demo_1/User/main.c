#include "stm32f10x.h"                  
#include "delay.h"  
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "serial.h"
#include "timer.h"
#include "pwm.h"
#include "utils.h"
#include "ad.h"

uint16_t num;
uint8_t key_v;
uint8_t count;
    char str1[20]="addsfgdfh232414bc"; 

int main(void){
	
	float num = 0.4;
    char str[20]; 
	u16 led0pwmval=0;    	//ARR
	u8 dir=1;				
	
	Led_Init();
	//Timer1_Init();
	PWM_Init();
	//PA8 PD2
	
	Serial_Init();	 	
	Key_Init();
	
	LCD_Init();
	LCD_Display_Dir(1);
	LCD_Clear(WHITE);
	
	LCD_ShowString(30,40,200,24,24,"Mini STM32 ^_^");
	//LCD_ShowNum(30,70,1,1,24);  						
	LCD_ShowChar(30,100,'#',24,1);	
	LCD_ShowSingleHZ(30,130,"你好",CHN_font_12);
	LCD_ShowHZ_ASCIIString(30,160,"你好!!!!",CHN_font_24);
	
	floatToString(num, str);
	LCD_ShowHZ_ASCIIString(30,190,str,CHN_font_24);
	
	//Serial_SendString("asdsdfg");
	
	while(1){
		//LCD_ShowNum(30,70,num,1,24); 
		delay_ms(10);
		if(dir)led0pwmval++;
		else led0pwmval--;	 
 		if(led0pwmval>=100)dir=0;
		if(led0pwmval==0)dir=1;	   					 
		TIM_SetCompare1(TIM1,led0pwmval);	  
		
		key_v = Key_GetNum();
		switch(key_v){
			case 1:
				yellow_turn();
				count++;
				//Serial_SendByte(0x56 );
				
				Serial_SendString("你好");
				break;
			case 2:
				red_turn();
				break;
			case 3:
				//red_turn();
				break;
		}
	}
}

