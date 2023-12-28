#ifndef __BLOCK_H_
#define __BLOCK_H_

enum Shape {
    I,  // I形状的方块
    O,  // O形状的方块
    T,  // T形状的方块
    L,  // L形状的方块
	S,  // S形状的方块
    J,  // J形状的方块
    Z   // Z形状的方块
};


//每一个格子
struct Face
{
	int data[10][20]; //用于标记指定位置是否有方块（1为有，0为无）
	int color[10][20]; //用于记录指定位置的方块颜色编码
};

//方块
struct Block {
    int x, y; // 方块的位置
    int Shape; // 方块的形状
    int rotation; // 方块的旋转状态
    int color; // 方块的颜色
};
extern struct Block curr_block;
extern struct Face face;
extern int block_int[7][4];
extern int hasCollision;

void interface_Init(void);									//界面初始化
void new_block(void);
void show_curr_block(void);
void Refresh_Display(void);
void is_over(void);
void clean_row(void);
void left_move(void);
void right_move(void);
void transform(void);
void is_hasCollision(void);

#endif



