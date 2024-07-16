#include "ti_msp_dl_config.h"
#include "stdio.h"
#include "board.h"
#include "bsp_uart.h"
#include "oled.h"
#include "Serial_motor.h"
#include "hwt101.h"

extern struct Params	Motor;	//电机参数
int sta,i;

int main(void)
{
   board_Init();
	uart_Init();
	NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
	OLED_Init();
	//OLED_Clear();
//	 Emm_V5_Reset_CurPos_To_Zero(usart1_send_bytes,0);
	delay_ms(2000);
	//Emm_V5_Pos_Control(usart1_send_bytes,1,CW,30,2,64000,0,0);
//	Emm_V5_Pos_Control(usart0_send_bytes,1,CCW,30,2,64000,0,0);
	Emm_V5_Vel_Control(usart0_send_bytes,1,CCW,100,2,0);
	Emm_V5_Vel_Control(usart1_send_bytes,1,CW,100,2,0);
	delay_ms(1000);
	sta=1;
//	//Emm_V5_Vel_Control(usart1_send_bytes,1,CW,100,10,0);
//	Emm_V5_Pos_Control(usart1_send_bytes,1,CW,100,10,10000,0,0);
//	DL_GPIO_clearPins(LED_PORT,LED_PIN0_PIN);
//	sta=1;
    while (1) {
		// DL_GPIO_togglePins(LED_PORT,LED_PIN0_PIN);
		
		//printf("val: %d - cur : %d ",Motor.Cur_Val,Motor.Cur_Pos);
		
       // OLED_ShowString(0,8,(uint8_t *)"ABC",12,1);//6*12 “ABC”
       //OLED_ShowString(1,20,(uint8_t *)"ABC",16,1);//8*16 “ABC”
//		 OLED_ShowNum(0,0,Motor.Cur_Pul,8,16,1);
//			OLED_ShowNum(0,20,Motor.Cur_Val,8,16,1);
//		 OLED_ShowNum(0,35,sta,8,16,1);
//			OLED_ShowNum(0,50,Motor.Cur_Pos,8,16,1);
//     OLED_Refresh();
//		  
	//delay_ms(100);	 
       
    }
}



//定时器的中断服务函数 已配置为100MS的周期
void TIMER_0_INST_IRQHandler(void)
{
    //如果产生了定时器中断
    switch( DL_TimerG_getPendingInterrupt(TIMER_0_INST) )
    {
        case DL_TIMER_IIDX_ZERO://如果是0溢出中断
            //将LED灯的状态翻转
         DL_GPIO_togglePins(LED_PORT,LED_PIN0_PIN);
		  //S_CPOS 	位置   S_VEL 速度  S_CPUL	脉冲数
		if(sta!=0)
			{
				
				if(sta==1)
				{
					Emm_V5_Read_Sys_Params(usart1_send_bytes,1, S_CPUL);
				}
				else if(sta==2)
				{
					Emm_V5_Read_Sys_Params(usart1_send_bytes,1,S_VEL);
				}
					sta++;
				if(sta>2)sta=1;
			}
		 
		  //WRead_Pul(usart1_send_bytes,1);
            break;
        
        default://其他的定时器中断
            break;
    }
}
