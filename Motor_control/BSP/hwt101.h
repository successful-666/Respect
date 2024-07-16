#ifndef	__HWT101_H__
#define 	__HWT101_H__


#include "ti_msp_dl_config.h"
#include "bsp_uart.h"

struct Gyro
{
	float Acc;
	float Angle;
};


void hwt101_Set_Bound(usart_send_bytes_t usart_send_bytes,uint32_t bound);

void hwt101_Read_Angle(uint8_t *data);

#endif
