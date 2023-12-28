#include "key.h"
#include "delay.h"

//key_0 PC5   key_1 PA15
void Key_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

uint8_t Key_GetNum(void){
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15) == 0){
		delay_ms(50);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15) == 0);
		delay_ms(50);
		return 1;
	}else if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) == 0){
		delay_ms(50);
		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) == 0);
		delay_ms(50);
		return 2;
	}else{
		return 3;
	}
	
}

