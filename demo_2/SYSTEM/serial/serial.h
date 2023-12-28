#ifndef _SERIAL_H
#define _SERIAL_H

#include "stm32f10x.h"  
#include <stdio.h>
#include <stdarg.h>

extern uint8_t Serial_TxPacket[];
extern uint8_t Serial_RxPacket[];


void Serial_Init(void);
void Serial_SendByte(uint8_t byte);
void Serial_SendArray(uint8_t *arr,uint16_t length);
void Serial_SendString(char *String);
uint32_t Serial_Pow(uint32_t x,uint32_t y);
void Serial_SendNum(uint32_t num,uint8_t length);
int fputc(int ch, FILE *f);
void Serial_Printf(char *format, ...);


uint8_t Serial_GetRxFlag(void);
void Serial_SendPacket(void);


#endif
