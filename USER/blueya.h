#ifndef _BLUEYA_H_
#define _BLUEYA_H_

#include <stm32f10x.h>
#include <stdio.h>

extern int car_flag;

void usart_Configuation(void);
void usart_exit(void);
int fputc (int c, FILE * fp);
void USART1_IRQHandler(void);
void blueya_Configuation(void);
void USART_SendString(const unsigned char *pt);


#endif
