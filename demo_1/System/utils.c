#include "utils.h"
#include <stdio.h>

// 将float数转换为字符串,保留3位小数
void floatToString(float number,char* result) {
	uint8_t i,digit,integerPart;
    // 处理整数部分
    integerPart = (uint8_t)number;
    result += sprintf(result, "%d", integerPart);

    // 小数点
    *result++ = '.';

    // 处理小数部分
    float decimalPart = number - integerPart;
    for (i = 0; i < 3; ++i) {
        decimalPart *= 10;
        digit = (uint8_t)decimalPart;
        *result++ = '0' + digit;
        decimalPart -= digit;
    }

    // 结束字符串
    *result = '\0';
}



