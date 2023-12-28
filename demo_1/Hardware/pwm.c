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
    
    // ʱ��1��Ƶ
    TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
    // ���ϼ���
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    // ��ʱƵ��=72M/(PSC+1)/(ARR+1)
    // ��72M����7200��Ƶ = 10K Hz����10K Hz��Ƶ���¼�10000����������һ����
    // 10K / ARR = 1��,
    // ARR����(0��65535)
    TIM_TimeBaseInitStructure.TIM_Period = (900 - 1);
    // PSCԤ��Ƶ(0��65535) 72M = 72000000
    TIM_TimeBaseInitStructure.TIM_Prescaler = (1 - 1);
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    // ��ʼ��
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
    
	
	
	
	//������ṹ�帳��ʼֵ
	TIM_OCStructInit(&TIM_OCInitStructure);
	//ģʽ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	//����
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//CCR(ռ�ձ� = CCR / AAR)
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	
	//������ʱ��1
	TIM_Cmd(TIM1,ENABLE);
}




