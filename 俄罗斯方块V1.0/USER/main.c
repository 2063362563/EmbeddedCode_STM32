#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "lcd.h"
#include "serial.h"
#include "block.h"
#include "timer.h"
#include "key.h"

int key_v;

int main(void)
{	
	Led_Init();
	Serial_Init();
	LCD_Init();
	KEY_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	TIM3_Int_Init(4999,7199);//10Khz�ļ���Ƶ�ʣ�������1000Ϊ100ms  
	interface_Init();//�����ʼ��
	new_block();
	
	while(1){
		key_v = KEY_Scan(0);//��ȡ����
		switch(key_v){
			
			case WKUP_PRES:	//WK_UP���� 
				//����
				left_move();
				break;
			case KEY0_PRES:	//key_0����
				//����
				right_move();
				break;
			case KEY1_PRES:	//key_1����
				//����
				transform();
				break;
			case 0:			//�ް�������
				break;
		}
		if(timer_flag == 1){//��ʱ�������ж�
			//�����ײ
			is_hasCollision();
			timer_flag = 0;//��־λ��λ
			curr_block.y++;//��������
			rand_num++;//�����������
			Refresh_Display();//ˢ����ʾ
			show_curr_block();
		}
	}
}

