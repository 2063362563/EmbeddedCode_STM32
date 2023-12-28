#ifndef _AD_H
#define _AD_H

#include "stm32f10x.h"  

void AD_Init(void);

u16 Get_Adc(u8 ch);   


u16 Get_Adc_Average(u8 ch,u8 times);


#endif
