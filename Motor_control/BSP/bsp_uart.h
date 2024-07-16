#ifndef	__BSP_UART_H__
#define 	__BSP_UART_H__


#include "ti_msp_dl_config.h"
#include "board.h"

void uart_Init(void);
void uart2_send_char(char ch);
void uart2_send_string(char* str);
void usart0_send_bytes(unsigned char *buf, int len);
void usart1_send_bytes(unsigned char *buf, int len);
void usart2_send_bytes(unsigned char *buf, int len);
typedef void (*usart_send_bytes_t)(unsigned char *buf, int len);
void usart_SendCmd(usart_send_bytes_t usart_send_bytes, const uint8_t *cmd, uint8_t len);

#endif
