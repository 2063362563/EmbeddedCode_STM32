#include "utils.h"
#include <stdio.h>

// ��float��ת��Ϊ�ַ���,����3λС��
void floatToString(float number,char* result) {
	uint8_t i,digit,integerPart;
    // ������������
    integerPart = (uint8_t)number;
    result += sprintf(result, "%d", integerPart);

    // С����
    *result++ = '.';

    // ����С������
    float decimalPart = number - integerPart;
    for (i = 0; i < 3; ++i) {
        decimalPart *= 10;
        digit = (uint8_t)decimalPart;
        *result++ = '0' + digit;
        decimalPart -= digit;
    }

    // �����ַ���
    *result = '\0';
}



