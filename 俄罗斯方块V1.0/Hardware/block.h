#ifndef __BLOCK_H_
#define __BLOCK_H_

enum Shape {
    I,  // I��״�ķ���
    O,  // O��״�ķ���
    T,  // T��״�ķ���
    L,  // L��״�ķ���
	S,  // S��״�ķ���
    J,  // J��״�ķ���
    Z   // Z��״�ķ���
};


//ÿһ������
struct Face
{
	int data[10][20]; //���ڱ��ָ��λ���Ƿ��з��飨1Ϊ�У�0Ϊ�ޣ�
	int color[10][20]; //���ڼ�¼ָ��λ�õķ�����ɫ����
};

//����
struct Block {
    int x, y; // �����λ��
    int Shape; // �������״
    int rotation; // �������ת״̬
    int color; // �������ɫ
};
extern struct Block curr_block;
extern struct Face face;
extern int block_int[7][4];
extern int hasCollision;

void interface_Init(void);									//�����ʼ��
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



