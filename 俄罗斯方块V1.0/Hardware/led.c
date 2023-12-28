#include "led.h"

//低电平点亮,A8红,D2黄,默认低电平
void Led_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD,ENABLE);
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}


void red_on(){
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}

void red_off(){
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
}

void red_turn(){
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_8) == 0){
		red_on();
	}else{
		red_off();
	}
}

void yellow_on(){
	GPIO_ResetBits(GPIOD,GPIO_Pin_2);
}

void yellow_off(){
	GPIO_SetBits(GPIOD,GPIO_Pin_2);
}

void yellow_turn(){
	if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_2) == 0){
		yellow_on();
	}else{
		yellow_off();
	}
}

