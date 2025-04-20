#include "stm32f10x.h"
#include "led.h"
#include "delay.h"



int main()
{
	LED_Init();
	// 用一个死循环保持状态
	while (1)
	{
		GPIOA->ODR &= ~GPIO_ODR_ODR0;
		Delay_ms(100);
		GPIOA->ODR |= GPIO_ODR_ODR0;

		GPIOA->ODR &= ~GPIO_ODR_ODR1;
		Delay_ms(100);
		GPIOA->ODR |= GPIO_ODR_ODR1;

		GPIOA->ODR &= ~GPIO_ODR_ODR8;
		Delay_ms(100);
		GPIOA->ODR |= GPIO_ODR_ODR8;
	}
}


