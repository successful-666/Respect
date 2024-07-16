#include "board.h"
#include "stdio.h"

volatile unsigned int delay_times = 0;
volatile unsigned char uart_data = 0;

//系统函数初始化
void board_Init(void)
{
	SYSCFG_DL_init();
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
   NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
	
}

//微秒级延时
void delay_us(unsigned long __us) 
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 38;
    ticks = __us * (32000000 / 1000000);

  
    told = SysTick->VAL;

    while (1)
    {      
        tnow = SysTick->VAL;

        if (tnow != told)
        {
            if (tnow < told)
                tcnt += told - tnow;
            else
                tcnt += SysTick->LOAD - tnow + told;
            told = tnow;
            if (tcnt >= ticks)
                break;
        }
    }
}
//毫秒级延时
void delay_ms(unsigned long ms) 
{
	delay_us( ms * 1000 );
}
//发送字符
void uart0_send_char(char ch)
{
	
	while( DL_UART_isBusy(UART_0_INST) == true );
	
	DL_UART_Main_transmitData(UART_0_INST, ch);

}
//发送字符串
void uart0_send_string(char* str)
{
	
	while(*str!=0&&str!=0)
	{
	
		uart0_send_char(*str++);
	}
}

void usart0_send_bytes(unsigned char *buf, int len)
{
  while(len--)
  {
    DL_UART_Main_transmitDataBlocking(UART_0_INST, *buf);
    buf++;
  }
}

#if !defined(__MICROLIB)

#if (__ARMCLIB_VERSION <= 6000000)

struct __FILE
{
	int handle;
};
#endif

FILE __stdout;


void _sys_exit(int x)
{
	x = x;
}
#endif


//printf重定义
int fputc(int ch, FILE *stream)
{
	
	while( DL_UART_isBusy(UART_0_INST) == true );
	
	DL_UART_Main_transmitData(UART_0_INST, ch);
	
	return ch;
}

//串口中断
void UART_0_INST_IRQHandler(void)
{
	
	switch( DL_UART_getPendingInterrupt(UART_0_INST) )
	{
		case DL_UART_IIDX_RX:
		
			uart_data = DL_UART_Main_receiveData(UART_0_INST);
			
			break;
		
		default:
			break;
	}
}


