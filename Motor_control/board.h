#ifndef	__BOARD_H__
#define 	__BOARD_H__


#include "ti_msp_dl_config.h"

void board_Init(void);
void delay_us(unsigned long __us);
void delay_ms(unsigned long ms);

void uart0_send_char(char ch);
void uart0_send_string(char* str);



#endif
