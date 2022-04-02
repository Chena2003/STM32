#include "SysTick.h"
#include "Stepper_move.h"
#include "blueya.h"

int main(void)
{
//	int time_count = 25000;
	
	Systick_Configuration();
	blueya_Configuation();

	
	while(1)
	{
			USART_SendString("Hello World");
	}	
}
