#include "pwm.h"

void PWM_Init(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
    TIM_InternalClockConfig(TIM1);
    
    // 时钟1分频
    TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
    // 向上计数
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    // 定时频率=72M/(PSC+1)/(ARR+1)
    // 对72M进行7200分频 = 10K Hz，在10K Hz的频率下计10000个数，就是一秒了
    // 10K / ARR = 1秒,
    // ARR周期(0～65535)
    TIM_TimeBaseInitStructure.TIM_Period = (900 - 1);
    // PSC预分频(0～65535) 72M = 72000000
    TIM_TimeBaseInitStructure.TIM_Prescaler = (1 - 1);
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    // 初始化
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
    
	
	
	
	//给这个结构体赋初始值
	TIM_OCStructInit(&TIM_OCInitStructure);
	//模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	//极性
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//CCR(占空比 = CCR / AAR)
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	
	//启动定时器1
	TIM_Cmd(TIM1,ENABLE);
}




