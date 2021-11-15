#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include <stm32f10x.h>

void Systick_Configuration(void);
void Delay_us(unsigned int n);


extern int count;



#endif
