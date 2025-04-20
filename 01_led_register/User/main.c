#include <stdint.h>

int main()
{
	//时钟配置
	*(uint32_t *)(0x40021000 + 0x18) = 4;
	
	//GPIO工作模式配置
	*(uint32_t *)(0x40010800 + 0x00) = 3;
	
	//PA0输出低电平
	*(uint32_t *)(0x40010800 + 0x0C) = 0xfffe;
	
	//用一个死循环保持状态
	while(1){
	
	}
	
}
