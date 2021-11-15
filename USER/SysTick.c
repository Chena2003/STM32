#include "SysTick.h"

int count;

void Systick_Configuration(void)
{

	while(SysTick_Config(72));
	
	SysTick->CTRL &= ~(1 << 0);	
}

void Delay_us(unsigned int n)
{
	count = n;
	SysTick->CTRL |= (1 << 0);
	while(count);
	SysTick->CTRL &= ~(1 << 0);
}
