#include "blueya.h"

int car_flag;

void blueya_Configuation(void)
{
	usart_Configuation();
	usart_exit();
	USART1_IRQHandler();
}


void usart_Configuation(void)
{
	
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

	//TX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	USART_ClearFlag(USART1,USART_FLAG_RXNE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
}

void usart_exit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

int fputc (int c, FILE * fp)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
	USART_SendData(USART1, (uint8_t) c);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);
	
	return c;
}

void USART1_IRQHandler(void)
{
	char ch;
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
		ch = USART_ReceiveData(USART1);
		
		if(ch == '1')
			car_flag = 1;
		else if(ch == '2')
			car_flag = 2;
		else if(ch == '3')
			car_flag = 3;
		else if(ch == '4')
			car_flag = 4;
		else if(ch == '5')
			car_flag = 5; 
		else if(ch == '6')
			car_flag = 6;
		
		else if(ch == '7')
			car_flag = 7;
	}
}

