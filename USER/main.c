#include "SysTick.h"
#include "Stepper_move.h"
#include "blueya.h"

int main(void)
{
//	int time_count = 25000;
	
	Systick_Configuration();
	pwm();
	key_Configuration();
	LED_Configuration();
	Stepper_Configuration();
	blueya_Configuation();
	
	GPIO_WriteBit(GPIOB, GPIO_Pin_4 | GPIO_Pin_8, Bit_SET);
	GPIO_WriteBit(GPIOB, GPIO_Pin_5 | GPIO_Pin_9, Bit_RESET);
	
	while(1)
	{
//		Delay_us(15000);
//		//向前
//		if(car_flag == 1)
//		{
//			GPIO_WriteBit(GPIOB, GPIO_Pin_4 | GPIO_Pin_8, Bit_SET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_5 | GPIO_Pin_9, Bit_RESET);
//		}
//		//停止
//		else if(car_flag == 2)
//		{
//			GPIO_WriteBit(GPIOB, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9, Bit_RESET);
//			//TIM_SetCompare1(TIM4, 49999);
//			//TIM_SetCompare2(TIM4, 49999);
//		}
//		//后退
//		else if(car_flag == 3)
//		{
//			GPIO_WriteBit(GPIOB, GPIO_Pin_5 | GPIO_Pin_9, Bit_SET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_4 | GPIO_Pin_8, Bit_RESET);
//		//		
//		//
//		}
//		//左转
//		else if(car_flag == 4)
//		{
//			GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_SET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_9, Bit_RESET);
//		}
//		//右转
//		else if(car_flag == 5)
//		{
//			GPIO_WriteBit(GPIOB, GPIO_Pin_4, Bit_SET);
//			GPIO_WriteBit(GPIOB, GPIO_Pin_5 | GPIO_Pin_9 | GPIO_Pin_8, Bit_RESET);
//		}
//		//加速
//		else if(car_flag == 6)
//		{
//			if(time_count >= 0)
//			{
//				time_count -= 5000;
//				TIM_SetCompare1(TIM4, time_count);
//				TIM_SetCompare2(TIM4, time_count);
//			}
//		}
//		//减速
//		else if(car_flag == 7)
//		{
//			if(time_count <= 49999)
//			{
//				time_count += 5000;
//				TIM_SetCompare1(TIM4, time_count);
//				TIM_SetCompare2(TIM4, time_count);
//			}
//		}
	}	
}
