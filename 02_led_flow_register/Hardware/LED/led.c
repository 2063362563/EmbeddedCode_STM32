#include "led.h"

void LED_Init()
{
    // 时钟配置
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // GPIO工作模式配置(推挽输出)
    GPIOA->CRL &= ~GPIO_CRL_CNF0;
    GPIOA->CRL |= GPIO_CRL_MODE0;
    GPIOA->CRL &= ~GPIO_CRL_CNF1;
    GPIOA->CRL |= GPIO_CRL_MODE1;
    GPIOA->CRH &= ~GPIO_CRH_CNF8;
    GPIOA->CRH |= GPIO_CRH_MODE8;

    // 初始输出高电平(灭)
	// yellow
	GPIOA->ODR |= GPIO_ODR_ODR0;
	// red
	GPIOA->ODR |= GPIO_ODR_ODR1;
	// green
	GPIOA->ODR |= GPIO_ODR_ODR8;
}
void LED_On(uint16_t led)
{
    GPIOA->ODR &= ~led;
}
void LED_Off(uint16_t led)
{
    GPIOA->ODR |= led;
}
void LED_Toggle(uint16_t led)
{
    if (GPIOA->IDR & led == 0)
    {
        LED_Off(led);
    }
    else
    {
        LED_On(led);
    }
}
