#include "serial.h"
#include "delay.h"
#include "led.h"
uint8_t Serial_TxPacket[4];
uint8_t Serial_RxPacket[4];
uint8_t Serial_RxFlag;
uint8_t Serial_RxDate;
void Serial_Init(void) {
    // GPIO �˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // ʹ�� GPIOA �� USART1 ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    // USART1_TX GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // USART1_RX GPIOA.10 ��ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // NVIC ���ȼ�����
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // ��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        // �����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // USART ��ʼ������
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    // ���ʹ�� USART1
    USART_Cmd(USART1, ENABLE);
}



void Serial_SendByte(uint8_t byte){
	
	USART_SendData(USART1,byte);
	//����־λ,�����һ˵���������
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
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

//fputc������printf�����ĵײ�,������дfputc
//�ض���fputc���� 
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

uint8_t Serial_GetRxFlag(void){
	if(Serial_RxFlag == 1){
		Serial_RxFlag = 0;
		return 1;
	}else{
		return 0;
	}
}

void Serial_SendPacket(void){
	Serial_SendByte(0xFF);
	Serial_SendArray(Serial_TxPacket,4);
	Serial_SendByte(0xFE);
}


void USART1_IRQHandler(void){
	
	static  uint8_t RxState = 1;//����״̬,1�ȴ���ͷ,2�ȴ�����,3�ȴ���β
	static  uint8_t P_RxPacket = 0;//��¼�Ѵ洢����λ����
	
	if (USART_GetITStatus(USART1,USART_IT_RXNE) == SET){
		
		Serial_RxDate = USART_ReceiveData(USART1);
		Serial_SendByte(Serial_RxDate);
		switch(RxState){
			case 1:
				if(Serial_RxDate == 0xFF){
					red_off();
					RxState = 2;
				}
				
				break;
			case 2:
				Serial_RxPacket[P_RxPacket] = Serial_RxDate;
				P_RxPacket++;
				if(P_RxPacket == 4){
					red_on();
					
					RxState = 3;
				}
				break;
			case 3:
				if(Serial_RxDate == 0xFE){
					RxState = 1;
					Serial_RxFlag = 1;
					yellow_off();
					red_off();
				}
				break;
		}
		
		
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}













