#include "timer.h"

extern uint16_t num;

//ͨ�ö�ʱ��
void Timer2_Init(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	//ʱ��1��Ƶ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//���ϼ���
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//��ʱƵ��=72M/(PSC+1)/(ARR+1)
	//��72M����7200��Ƶ = 10K,��10K��Ƶ���¼�10000����,����һ����
	//10K / ARR = 1��,
	//ARR����(0��65535)
	TIM_TimeBaseInitStructure.TIM_Period = (10000-1);
	//PSCԤ��Ƶ(0��65535)
	TIM_TimeBaseInitStructure.TIM_Prescaler = (7200-1);
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	//��ʼ��
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	//Ԥ��Ƶ����Ҫ�ڸ���֮�������Ч,����TIM_TimeBaseInit()����
	//������ֶ�������һ���ж�,����Ҳ�����˽����жϵ����жϱ�־λû�����,
	//���������ֶ����һ��,�������ܱ���ճ�ʼ����ͽ����жϵ����
	TIM_ClearFlag(TIM2,TIM_IT_Update);
	
	//���������жϵ�NVICV
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	//NVIC���ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	
	NVIC_Init(&NVIC_InitStructure);
	//������ʱ��2
	TIM_Cmd(TIM2,ENABLE);
}

//��ʱ��2�жϺ���
void TIM2_IRQHandler(void){
	//����жϱ�־λ 
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET){
		
		num++;
		//�����־λ
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}

//�߼���ʱ��
void Timer1_Init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    TIM_InternalClockConfig(TIM1);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    // ʱ��1��Ƶ
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    // ���ϼ���
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    // ��ʱƵ��=72M/(PSC+1)/(ARR+1)
    // ��72M����7200��Ƶ = 10K����10K��Ƶ���¼�10000����������һ����
    // 10K / ARR = 1��,
    // ARR����(0��65535)
    TIM_TimeBaseInitStructure.TIM_Period = (10000 - 1);
    // PSCԤ��Ƶ(0��65535)
    TIM_TimeBaseInitStructure.TIM_Prescaler = (7200 - 1);
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    // ��ʼ��
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
    // Ԥ��Ƶ����Ҫ�ڸ���֮�������Ч������TIM_TimeBaseInit()����
    // ������ֶ�������һ���жϣ�����Ҳ�����˽����жϵ����жϱ�־λû�������
    // ���������ֶ����һ�Σ��������ܱ���ճ�ʼ����ͽ����жϵ����
    TIM_ClearFlag(TIM1, TIM_IT_Update);

    // ���������жϵ�NVIC
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    // NVIC���ȼ�����
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;

    // �ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    // ��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    // ��Ӧ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;

    NVIC_Init(&NVIC_InitStructure);
    // ������ʱ��1
    TIM_Cmd(TIM1, ENABLE);
}

// ��ʱ��1�жϺ���
void TIM1_UP_IRQHandler(void) {
    // ����жϱ�־λ 
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET) {
        num++;
        // �����־λ
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    }
}





