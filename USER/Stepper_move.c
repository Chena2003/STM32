#include "Stepper_move.h"
#include "SysTick.h"

void Stepper_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	// 改变指定管脚的映射 GPIO_Remap_SWJ_Disable SWJ 完全禁用（JTAG+SW-DP）
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	// 改变指定管脚的映射 GPIO_Remap_SWJ_JTAGDisable ，JTAG-DP 禁用 + SW-DP 使能
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 |GPIO_Pin_8 |GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOB, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9, Bit_RESET);

	TIM_SetCompare1(TIM4, 25000);
	TIM_SetCompare2(TIM4, 25000);
	
}

void pwm(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//计时50ms
	TIM_TimeBaseStructure.TIM_Period = 49999;
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	//TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	//先低电平，再高电平	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState= TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse =0;
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	
	TIM_CtrlPWMOutputs(TIM4,ENABLE);															//MOE 主输出使能	
  
	//PB6 PWM输出-->L298N_ENA，右电机
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  						//CH1预装载使能	
	//PB7 PWM输出-->L298N_ENB，左电机
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  						//CH1预装载使能
	
	TIM_ARRPreloadConfig(TIM4, ENABLE); 													//使能TIMx在ARR上的预装载寄存器
 	TIM_Cmd(TIM4, ENABLE);
}

void key_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	
	//key0中断配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);
	
	//key1中断配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line15;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15);	
}

void LED_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	
	//初始化LED0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	//初始化LED1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
	GPIO_WriteBit(GPIOD, GPIO_Pin_2, Bit_SET);
}

void EXTI9_5_IRQHandler(void)
{
	//Delay_us(10);
	if(EXTI_GetITStatus(EXTI_Line5) == SET)
	{
		TIM_SetCompare1(TIM4, 0);
		TIM_SetCompare2(TIM4, 0);
		GPIO_WriteBit(GPIOB, GPIO_Pin_4 | GPIO_Pin_8, Bit_SET);
		GPIO_WriteBit(GPIOB, GPIO_Pin_5 | GPIO_Pin_9, Bit_RESET);
		//EXTI_ClearITPendingBit(EXTI_Line5);
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
//		GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_RESET);
//		Delay_us(100000);
//		GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
		GPIOA->ODR ^= GPIO_Pin_8;
   		Delay_us(1000);
	}
}

void EXTI15_10_IRQHandler(void)
{
	//Delay_us(10);
	if(EXTI_GetITStatus(EXTI_Line15) == SET)
	{
		TIM_SetCompare1(TIM4, 49999);
		TIM_SetCompare2(TIM4, 49999);
		GPIO_WriteBit(GPIOB, GPIO_Pin_4 | GPIO_Pin_8, Bit_SET);
		GPIO_WriteBit(GPIOB, GPIO_Pin_5 | GPIO_Pin_9, Bit_RESET);
		//EXTI_ClearITPendingBit(EXTI_Line15);
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
//		GPIO_WriteBit(GPIOD, GPIO_Pin_2, Bit_RESET);
//		Delay_us(100000);
//		GPIO_WriteBit(GPIOD, GPIO_Pin_2, Bit_SET);
		GPIOD->ODR ^= GPIO_Pin_2;
		Delay_us(1000);		
	}
	
}
