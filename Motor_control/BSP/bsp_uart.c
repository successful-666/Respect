#include "bsp_uart.h"
#include "Serial_motor.h"
#include "string.h"
#include "board.h"

#define DATA_BUFFER_SIZE 10	
uint8_t dataBuffer[DATA_BUFFER_SIZE];
uint8_t dataIndex = 0;

void uart_Init(void)
{
	//NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
	NVIC_ClearPendingIRQ(UART_1_INST_INT_IRQN);
	NVIC_ClearPendingIRQ(UART_2_INST_INT_IRQN);
	
	//NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
	NVIC_EnableIRQ(UART_1_INST_INT_IRQN);//ʹ���ж�
	NVIC_EnableIRQ(UART_2_INST_INT_IRQN);
	
	DL_UART_clearInterruptStatus(UART_1_INST,DL_UART_INTERRUPT_RX);//����жϱ�־λ
	DL_UART_clearInterruptStatus(UART_2_INST,DL_UART_INTERRUPT_RX);//����жϱ�־λ

}

uint8_t ch1[2]={1,2},ch2[2]={3,4};
extern int i;

void UART_1_INST_IRQHandler(void)
{
  switch (DL_UART_Main_getPendingInterrupt(UART_1_INST))
  {
            {
      uint8_t ch = DL_UART_Main_receiveData(UART_1_INST);
      // �����յ������ݴ��뻺����
            if (dataIndex < DATA_BUFFER_SIZE)
            {
                dataBuffer[dataIndex++] = ch;
            }

            // ����Ƿ���յ����������ݰ�
				 // ����6�ֽ����ݰ�
            if (dataIndex >= 6 && dataBuffer[0] == 0x01 && dataBuffer[1] == 0x35 && dataBuffer[5] == 0x6B)
            {
               
					Read_Val(dataBuffer);
					 i=6;
					memset((void *)dataBuffer,0,sizeof(dataBuffer));
               dataIndex = 0; // ��������
					
            }
				// ����8�ֽ����ݰ�
             else if (dataIndex >= 8 && dataBuffer[0] == 0x01 && dataBuffer[1] == 0x36 && dataBuffer[7] == 0x6B)
            {
                
              Read_Pos(dataBuffer);
					i=8;
				
					//usart1_send_bytes(ch2,1);
					memset((void *)dataBuffer,0,sizeof(dataBuffer));
                dataIndex = 0; // ��������
            }
				else if (dataIndex >= 8 && dataBuffer[0] == 0x01 && dataBuffer[1] == 0x30 && dataBuffer[7] == 0x6B)
            {
                
               Read_Pul(dataBuffer);
					i=9;
				
					memset((void *)dataBuffer,0,sizeof(dataBuffer));
               dataIndex = 0; // ��������
            }
				// ������������ˣ���û���ҵ���Ч�İ�����������
            else if (dataIndex == DATA_BUFFER_SIZE)
            {
                
					memset((void *)dataBuffer,0,sizeof(dataBuffer));
               dataIndex = 0;
            }
				DL_UART_clearInterruptStatus(UART_0_INST,DL_UART_INTERRUPT_RX);//����жϱ�־λ
    }
    break;

    default:
		 DL_UART_clearInterruptStatus(UART_0_INST,DL_UART_INTERRUPT_RX);//����жϱ�־λ
      break;
  }
}
void UART_2_INST_IRQHandler(void)
{
  switch (DL_UART_Main_getPendingInterrupt(UART_2_INST))
  {
    case DL_UART_MAIN_IIDX_RX:
    {
      uint8_t ch = DL_UART_Main_receiveData(UART_2_INST);
     
    }
    break;

    default:
      break;
  }
}





void usart1_send_bytes(unsigned char *buf, int len)
{
 // while (DL_UART_isBusy(UART_1_INST) == true );
  while(len--)
  {
    DL_UART_Main_transmitDataBlocking(UART_1_INST, *buf);
    buf++;
  }
}

void usart2_send_bytes(unsigned char *buf, int len)
{
  while(len--)
  {
    DL_UART_Main_transmitDataBlocking(UART_2_INST, *buf);
    buf++;
  }
}


void usart_SendCmd(usart_send_bytes_t usart_send_bytes, const uint8_t *cmd, uint8_t len)
{
    // ����ʹ�ô���ĺ���ָ������������
    usart_send_bytes((unsigned char *)cmd, len);
}