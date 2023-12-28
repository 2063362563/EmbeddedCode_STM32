#ifndef _DELAY_H
#define _DELAY_H

#include "stm32f10x.h"  

extern void delay_us(uint32_t xus);
extern void delay_ms(uint32_t xms);
extern void delay_s(uint32_t xs);

#endif
