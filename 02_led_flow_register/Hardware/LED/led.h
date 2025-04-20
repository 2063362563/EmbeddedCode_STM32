#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define LED_YELLOW GPIO_ODR_ODR0
#define LED_RED GPIO_ODR_ODR1
#define LED_GREEN GPIO_ODR_ODR8

void LED_Init(void);
void LED_On(uint16_t led);
void LED_Off(uint16_t led);
void LED_Toggle(uint16_t led);

#endif
