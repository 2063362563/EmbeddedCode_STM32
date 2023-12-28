#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "lcd.h"
#include "serial.h"

uint16_t num = 10;
int main(void)
{	
	Led_Init();
	Serial_Init();
	LCD_Init();
	
	LCD_ShowString(30,40,200,24,24,"Mini STM32 ^_^");	
	
	
	Serial_TxPacket[0] = 0x01;
	Serial_TxPacket[1] = 0x02;
	Serial_TxPacket[2] = 0x03;
	Serial_TxPacket[3] = 0x04;
	Serial_SendPacket();
	
	Serial_SendString("SET_NUM(0,20,3);");
	
	while(1){
		if(Serial_GetRxFlag() == 1){
			red_off();
			Serial_SendByte(Serial_RxPacket[0]);
			Serial_SendByte(Serial_RxPacket[1]);
			Serial_SendByte(Serial_RxPacket[2]);
			Serial_SendByte(Serial_RxPacket[3]);
			LCD_ShowxNum(30,60,Serial_RxPacket[0],2,24,1);
			LCD_ShowxNum(30,90,Serial_RxPacket[1],3,24,1);
			LCD_ShowxNum(30,120,Serial_RxPacket[2],2,24,1);
			LCD_ShowxNum(30,150,Serial_RxPacket[3],2,24,1);
		}
		
	}
}

