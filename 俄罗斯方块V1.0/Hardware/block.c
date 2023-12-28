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
	{17476,3840,8738,240}, 	// I形状的方块
	{1632,1632,1632,1632},	// O形状的方块
	{3648,9760,624,1124},	// T形状的方块
	{1094,232,25120,368},	// L形状的方块
	{1728,17952,864,1122},	// S形状的方块
	{550,2272,25664,1808},	// J形状的方块
	{3168,9792,1584,612}, 	// Z形状的方块
};
int item_arr[7] = {0,1,2,3,4,5,6};
int arr_size = sizeof(item_arr) / sizeof(item_arr[0]);
int remaining = 7;//还剩几个方块
struct Block curr_block;
struct Face face;
int hasCollision  = 0; // 用于判断是否触底或碰撞


//打乱数组顺序,用温度做随机数种子
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
	//画游戏边界
	for(i=1;i<=3;i++){
		LCD_DrawRectangle(i, i, 239-i, 319-i);
	}
	//将所有格子都设置成false
	for(i=0;i<10;i++){
		for(j=0;j<20;j++){
			face.data[i][j] = 0;
		}
	}
}

//从顶部新出现一个方块
void new_block(){
	
	if(remaining == 7){
		shuffle(item_arr, arr_size);
	}
	curr_block.Shape = item_arr[--remaining];
	curr_block.rotation = 0;
	curr_block.x = 3;//  x∈[0,9]
	//判断不同方块的初始Y坐标和颜色
	switch(curr_block.Shape){
		case 0:curr_block.y = -3;curr_block.color = I_color;break;//I  y∈[0,19]
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

//碰撞
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
		//检测是否游戏结束
		is_over();
		//检测消行
		clean_row();
		//新增一个方块
		new_block();
	}
}
//显示当前方块
void show_curr_block() {
    int i, x, y, offset_x, offset_y;
    hasCollision  = 0; // 用于判断是否触底或碰撞
	
	
    for (i = 15; i >= 0; i--) {
        offset_x = i % 4;//相对x坐标
        offset_y = i / 4;//相对y坐标
        x = curr_block.x + offset_x;//实际x坐标
        y = curr_block.y + offset_y;//实际y坐标

        if (y < 0 || y > 19) {
            continue;
        }
		
		//选中当前4*4中的有色格子
        if (((block_int[curr_block.Shape][curr_block.rotation] >> i) & 1) == 1) {
			
            Fill_LCD_Block(x, y, curr_block.color);
			//判断是否触底或发生碰撞
            if (y == 19 || face.data[x][y + 1] == 1) {
                hasCollision  = 1;
            }
        }
    }
}

//检测是否游戏结束
void is_over(){
	int x,i,j;
	for(x=0;x<10;x++){
		if(face.data[x][0] == 1){
			//游戏结束
			for(i=0;i<10;i++){
				for(j=0;j<20;j++){
					face.data[i][j] = 0;//重置游戏界面
				}
			}
		}
	}
}


// 消行检测和消行
void clean_row() {
    for (int y = 19; y >= 0; y--) {
        // 判断当前行是否满行
        int full_row = 1;
        for (int x = 0; x < 10; x++) {
            if (face.data[x][y] == 0) {
                full_row = 0;
                break;
            }
        }

        // 如果当前行满行，则进行消行操作
        if (full_row) {
            // 从当前行开始，将上面的所有行下移一行
            for (int k = y; k > 0; k--) {
                for (int x = 0; x < 10; x++) {
                    face.data[x][k] = face.data[x][k - 1];
                }
            }

            // 清空顶部的一行
            for (int x = 0; x < 10; x++) {
                face.data[x][0] = 0;
            }

            // 更新显示
            Refresh_Display();

            // 由于上面的行下移了，需要重新检查当前行
            y++;
        }
    }
}

//更新显示,先清屏,然后显示face.data[][]为1的格子
void Refresh_Display(){
	int x,y;
	//找游戏界面中的位置,未稳定的选定位置清屏
	for(x=0;x<10;x++){
		for(y=0;y<20;y++){
			if(face.data[x][y] == 0){
				Fill_LCD_Block(x,y,WHITE);
			}
		}
	}
	
	//找游戏界面中的位置
	for(x=0;x<10;x++){
		for(y=0;y<20;y++){
			if(face.data[x][y] == 1){
				Fill_LCD_Block(x,y,face.color[x][y]);
			}
		}
	}
}

// 左移
void left_move() {
    int i, x,y, offset_x,offset_y;
    for (i = 15; i >= 0; i--) {
		offset_x = i % 4;//相对x坐标
		offset_y = i / 4;//相对y坐标
		x = curr_block.x + offset_x;//实际x坐标
		y = curr_block.y + offset_y;//实际y坐标
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

// 右移
void right_move() {
	int i, x,y, offset_x,offset_y;
    for (i = 15; i >= 0; i--) {
		offset_x = i % 4;//相对x坐标
		offset_y = i / 4;//相对y坐标
		x = curr_block.x + offset_x;//实际x坐标
		y = curr_block.y + offset_y;//实际y坐标
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



//变形
void transform(){
	//如果变形后位置与已稳定方格重合或超出游戏界面则不能变形
	int i, x, y, offset_x, offset_y;
	for (i = 15; i >= 0; i--) {
		offset_x = i % 4;//相对x坐标
		offset_y = i / 4;//相对y坐标
		x = curr_block.x + offset_x;//实际x坐标
		y = curr_block.y + offset_y;//实际y坐标
		
		//选中变形后4*4中的有色格子
		if (((block_int[curr_block.Shape][curr_block.rotation+1==4?0:curr_block.rotation+1] >> i) & 1) == 1) {
			if(face.data[x][y] == 1 || x < 0 || x > 9 || y > 19){
				return;
			}
		}
	}
	//方块变形
	curr_block.rotation = curr_block.rotation+1==4?0:(curr_block.rotation+1);
	Refresh_Display();
	show_curr_block();
}


