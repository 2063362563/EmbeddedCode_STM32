#include "block.h"
#include <stdlib.h>
#include <stdio.h>
#include "ds18b20.h"
#include "lcd.h"
#include "serial.h"
#include "led.h"
#include "timer.h"

#define  I_color  BLUE
#define  O_color  BRED
#define  T_color  GRED
#define  L_color  GBLUE
#define  S_color  RED
#define  J_color  GREEN
#define  Z_color  LIGHTGREEN

short temperature;   
int block_int[7][4] = {
	{17476,3840,8738,240}, 	// I��״�ķ���
	{1632,1632,1632,1632},	// O��״�ķ���
	{3648,9760,624,1124},	// T��״�ķ���
	{1094,232,25120,368},	// L��״�ķ���
	{1728,17952,864,1122},	// S��״�ķ���
	{550,2272,25664,1808},	// J��״�ķ���
	{3168,9792,1584,612}, 	// Z��״�ķ���
};
int item_arr[7] = {0,1,2,3,4,5,6};
int arr_size = sizeof(item_arr) / sizeof(item_arr[0]);
int remaining = 7;//��ʣ��������
struct Block curr_block;
struct Face face;
int hasCollision  = 0; // �����ж��Ƿ񴥵׻���ײ


//��������˳��,���¶������������
void shuffle(int *array, int size) {
	int i,j,temp;
	//temperature=DS18B20_Get_Temp();	
    srand(rand_num);
    for (i = size - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void interface_Init(){
	uint8_t i,j;
	LCD_ShowString(90,25,200,24,24,"Tetris");
	LCD_ShowString(150,80,200,24,24,"score:");
	LCD_ShowString(160,120,200,24,24,"000");
	LCD_ShowString(150,155,200,24,24,"next:");
	LCD_Fill(4, 72, 124, 74,BLACK);
	LCD_Fill(125, 72, 127, 315,BLACK);
	//����Ϸ�߽�
	for(i=1;i<=3;i++){
		LCD_DrawRectangle(i, i, 239-i, 319-i);
	}
	//�����и��Ӷ����ó�false
	for(i=0;i<10;i++){
		for(j=0;j<20;j++){
			face.data[i][j] = 0;
		}
	}
}

//�Ӷ����³���һ������
void new_block(){
	
	if(remaining == 7){
		shuffle(item_arr, arr_size);
	}
	curr_block.Shape = item_arr[--remaining];
	curr_block.rotation = 0;
	curr_block.x = 3;//  x��[0,9]
	//�жϲ�ͬ����ĳ�ʼY�������ɫ
	switch(curr_block.Shape){
		case 0:curr_block.y = -3;curr_block.color = I_color;break;//I  y��[0,19]
		case 1:curr_block.y = -2;curr_block.color = O_color;break;//O
		case 2:curr_block.y = -2;curr_block.color = T_color;break;//T
		case 3:curr_block.y = -3;curr_block.color = L_color;break;//L
		case 4:curr_block.y = -2;curr_block.color = S_color;break;//S
		case 5:curr_block.y = -3;curr_block.color = J_color;break;//J
		case 6:curr_block.y = -2;curr_block.color = Z_color;break;//Z
	}

	curr_block.rotation = 0;
	if(remaining == 0){
		remaining = 7;
	}
}

//��ײ
void is_hasCollision(){
	int i, x, y, offset_x, offset_y;
	if(hasCollision == 1){
		for (i = 15; i >= 0; i--) {
			offset_x = i % 4;
			offset_y = i / 4;
			x = curr_block.x + offset_x;
			y = curr_block.y + offset_y;
			if (((block_int[curr_block.Shape][curr_block.rotation] >> i) & 1) == 1) {
				face.data[x][y] = 1;
				face.color[x][y] = curr_block.color;
			}
		}
		//����Ƿ���Ϸ����
		is_over();
		//�������
		clean_row();
		//����һ������
		new_block();
	}
}
//��ʾ��ǰ����
void show_curr_block() {
    int i, x, y, offset_x, offset_y;
    hasCollision  = 0; // �����ж��Ƿ񴥵׻���ײ
	
	
    for (i = 15; i >= 0; i--) {
        offset_x = i % 4;//���x����
        offset_y = i / 4;//���y����
        x = curr_block.x + offset_x;//ʵ��x����
        y = curr_block.y + offset_y;//ʵ��y����

        if (y < 0 || y > 19) {
            continue;
        }
		
		//ѡ�е�ǰ4*4�е���ɫ����
        if (((block_int[curr_block.Shape][curr_block.rotation] >> i) & 1) == 1) {
			
            Fill_LCD_Block(x, y, curr_block.color);
			//�ж��Ƿ񴥵׻�����ײ
            if (y == 19 || face.data[x][y + 1] == 1) {
                hasCollision  = 1;
            }
        }
    }
}

//����Ƿ���Ϸ����
void is_over(){
	int x,i,j;
	for(x=0;x<10;x++){
		if(face.data[x][0] == 1){
			//��Ϸ����
			for(i=0;i<10;i++){
				for(j=0;j<20;j++){
					face.data[i][j] = 0;//������Ϸ����
				}
			}
		}
	}
}


// ���м�������
void clean_row() {
    for (int y = 19; y >= 0; y--) {
        // �жϵ�ǰ���Ƿ�����
        int full_row = 1;
        for (int x = 0; x < 10; x++) {
            if (face.data[x][y] == 0) {
                full_row = 0;
                break;
            }
        }

        // �����ǰ�����У���������в���
        if (full_row) {
            // �ӵ�ǰ�п�ʼ�������������������һ��
            for (int k = y; k > 0; k--) {
                for (int x = 0; x < 10; x++) {
                    face.data[x][k] = face.data[x][k - 1];
                }
            }

            // ��ն�����һ��
            for (int x = 0; x < 10; x++) {
                face.data[x][0] = 0;
            }

            // ������ʾ
            Refresh_Display();

            // ����������������ˣ���Ҫ���¼�鵱ǰ��
            y++;
        }
    }
}

//������ʾ,������,Ȼ����ʾface.data[][]Ϊ1�ĸ���
void Refresh_Display(){
	int x,y;
	//����Ϸ�����е�λ��,δ�ȶ���ѡ��λ������
	for(x=0;x<10;x++){
		for(y=0;y<20;y++){
			if(face.data[x][y] == 0){
				Fill_LCD_Block(x,y,WHITE);
			}
		}
	}
	
	//����Ϸ�����е�λ��
	for(x=0;x<10;x++){
		for(y=0;y<20;y++){
			if(face.data[x][y] == 1){
				Fill_LCD_Block(x,y,face.color[x][y]);
			}
		}
	}
}

// ����
void left_move() {
    int i, x,y, offset_x,offset_y;
    for (i = 15; i >= 0; i--) {
		offset_x = i % 4;//���x����
		offset_y = i / 4;//���y����
		x = curr_block.x + offset_x;//ʵ��x����
		y = curr_block.y + offset_y;//ʵ��y����
		if (((block_int[curr_block.Shape][curr_block.rotation] >> i) & 1) == 1) {
            if (x == 0 || face.data[x-1][y] == 1) {
				return;
			}
        }
        
    }
    curr_block.x--;
    Refresh_Display();
    show_curr_block();
}

// ����
void right_move() {
	int i, x,y, offset_x,offset_y;
    for (i = 15; i >= 0; i--) {
		offset_x = i % 4;//���x����
		offset_y = i / 4;//���y����
		x = curr_block.x + offset_x;//ʵ��x����
		y = curr_block.y + offset_y;//ʵ��y����
        if (((block_int[curr_block.Shape][curr_block.rotation] >> i) & 1) == 1) {
            if (x == 9 || face.data[x+1][y] == 1) {
				return;
			}
        }
    }
    curr_block.x++;
    Refresh_Display();
    show_curr_block();
}



//����
void transform(){
	//������κ�λ�������ȶ������غϻ򳬳���Ϸ�������ܱ���
	int i, x, y, offset_x, offset_y;
	for (i = 15; i >= 0; i--) {
		offset_x = i % 4;//���x����
		offset_y = i / 4;//���y����
		x = curr_block.x + offset_x;//ʵ��x����
		y = curr_block.y + offset_y;//ʵ��y����
		
		//ѡ�б��κ�4*4�е���ɫ����
		if (((block_int[curr_block.Shape][curr_block.rotation+1==4?0:curr_block.rotation+1] >> i) & 1) == 1) {
			if(face.data[x][y] == 1 || x < 0 || x > 9 || y > 19){
				return;
			}
		}
	}
	//�������
	curr_block.rotation = curr_block.rotation+1==4?0:(curr_block.rotation+1);
	Refresh_Display();
	show_curr_block();
}


