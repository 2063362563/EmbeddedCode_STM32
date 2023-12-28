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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	TIM3_Int_Init(4999,7199);//10Khz的计数频率，计数到1000为100ms  
	interface_Init();//界面初始化
	new_block();
	
	while(1){
		key_v = KEY_Scan(0);//读取按键
		switch(key_v){
			
			case WKUP_PRES:	//WK_UP按下 
				//左移
				left_move();
				break;
			case KEY0_PRES:	//key_0按下
				//右移
				right_move();
				break;
			case KEY1_PRES:	//key_1按下
				//变形
				transform();
				break;
			case 0:			//无按键按下
				break;
		}
		if(timer_flag == 1){//定时器触发中断
			//检测碰撞
			is_hasCollision();
			timer_flag = 0;//标志位复位
			curr_block.y++;//方块下落
			rand_num++;//用作随机种子
			Refresh_Display();//刷新显示
			show_curr_block();
		}
	}
}

