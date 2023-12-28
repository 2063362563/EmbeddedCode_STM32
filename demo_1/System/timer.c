#include "timer.h"

extern uint16_t num;

//通用定时器
void Timer2_Init(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	//时钟1分频
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//向上计数
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//定时频率=72M/(PSC+1)/(ARR+1)
	//对72M进行7200分频 = 10K,在10K的频率下计10000个数,就是一秒了
	//10K / ARR = 1秒,
	//ARR周期(0～65535)
	TIM_TimeBaseInitStructure.TIM_Period = (10000-1);
	//PSC预分频(0～65535)
	TIM_TimeBaseInitStructure.TIM_Prescaler = (7200-1);
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	//初始化
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	//预分频器需要在更新之后才能起效,所以TIM_TimeBaseInit()函数
	//在最后手动更新了一次中断,这样也导致了进入中断但是中断标志位没有清除,
	//所以我们手动清除一次,这样就能避免刚初始化完就进入中断的情况
	TIM_ClearFlag(TIM2,TIM_IT_Update);
	
	//开启更新中断到NVICV
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	//NVIC优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//中断通道
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	
	NVIC_Init(&NVIC_InitStructure);
	//启动定时器2
	TIM_Cmd(TIM2,ENABLE);
}

//定时器2中断函数
void TIM2_IRQHandler(void){
	//检查中断标志位 
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET){
		
		num++;
		//清除标志位
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}

//高级定时器
void Timer1_Init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    TIM_InternalClockConfig(TIM1);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    // 时钟1分频
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    // 向上计数
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    // 定时频率=72M/(PSC+1)/(ARR+1)
    // 对72M进行7200分频 = 10K，在10K的频率下计10000个数，就是一秒了
    // 10K / ARR = 1秒,
    // ARR周期(0～65535)
    TIM_TimeBaseInitStructure.TIM_Period = (10000 - 1);
    // PSC预分频(0～65535)
    TIM_TimeBaseInitStructure.TIM_Prescaler = (7200 - 1);
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    // 初始化
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
    // 预分频器需要在更新之后才能起效，所以TIM_TimeBaseInit()函数
    // 在最后手动更新了一次中断，这样也导致了进入中断但是中断标志位没有清除，
    // 所以我们手动清除一次，这样就能避免刚初始化完就进入中断的情况
    TIM_ClearFlag(TIM1, TIM_IT_Update);

    // 开启更新中断到NVIC
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    // NVIC优先级分组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;

    // 中断通道
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    // 抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    // 响应优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;

    NVIC_Init(&NVIC_InitStructure);
    // 启动定时器1
    TIM_Cmd(TIM1, ENABLE);
}

// 定时器1中断函数
void TIM1_UP_IRQHandler(void) {
    // 检查中断标志位 
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET) {
        num++;
        // 清除标志位
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    }
}





