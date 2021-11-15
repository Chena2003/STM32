#ifndef _STEPPER_MOVE_H_
#define _STEPPER_MOVE_H_

#include <stm32f10x.h>


void Stepper_Configuration(void);
void pwm(void);
void key_Configuration(void);
void LED_Configuration(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);


#endif
