#include "serial.h"
#include "delay.h"


void Serial_Init(){
	
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);
	
	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
	   
	//USART1_RX	  GPIOA.10初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = 9600;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode =  USART_Mode_Tx| USART_Mode_Rx;	//收发模式
    USART_Init(USART1, &USART_InitStructure); //初始化串口1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
    USART_Cmd(USART1, ENABLE);                    //使能串口1 
	
}


void Serial_SendByte(uint8_t byte){
	USART_SendData(USART1,byte);
	//检查标志位,如果置一说明发送完毕
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == SET);
	delay_ms(1);
}

void Serial_SendArray(uint8_t *arr,uint16_t length){
	uint16_t i;
	
	for(i = 0; i < length;i++){
		Serial_SendByte(arr[i]);
		
	}
}

void Serial_SendString(char *String){
	uint8_t i;
	
	for(i = 0;String[i] != '\0';i++){
		Serial_SendByte(String[i]);
		
	}
}

uint32_t Serial_Pow(uint32_t x,uint32_t y){
	uint32_t result = 1;
	while(y--){
		result *= x;
	}
	return result;
}

void Serial_SendNum(uint32_t num,uint8_t length){
	uint8_t i;
	
	for(i = 0; i < length;i++){
		Serial_SendByte(num / Serial_Pow(10,length - 1 - i)% 10 +  0x30) ;
		
	}
}

//fputc函数是printf函数的底层,所以重写fputc
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	Serial_SendByte(ch);     
	return ch;
}

void Serial_Printf(char *format, ...){
	char String[100];
	
	va_list arg;
	va_start(arg,format);
	vsprintf(String,format,arg);
	va_end(arg);
	Serial_SendString(String);	
}




