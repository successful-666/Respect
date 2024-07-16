#ifndef	__Motor_control__
#define 	__Motor_control__


#include "ti_msp_dl_config.h"
#include "stdio.h"
#include "board.h"
#include "bsp_uart.h"
#include "Serial_motor.h"


void Motor_Stop(void);
void Motor_Forward(int speed_L,int speed_R);
void Motor_Back(int speed_L,int speed_R);
void PID_contorl(float kp1,float kp2);
void Motor_Forward_CLK(int speed_LV_clk,int speed_RV_clk);
void contorl(void);
void Motor_Processdata(uint8_t *data);
#endif
