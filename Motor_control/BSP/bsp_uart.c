#include "bsp_uart.h"
#include "Serial_motor.h"
#include "string.h"
#include "board.h"
#include "Motor_control.h"


extern int error1,error2;


#define DATA_BUFFER_SIZE 10	
uint8_t dataBuffer[DATA_BUFFER_SIZE];
uint8_t dataIndex = 0;

void uart_Init(void)
{
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
	NVIC_ClearPendingIRQ(UART_1_INST_INT_IRQN);
	NVIC_ClearPendingIRQ(UART_2_INST_INT_IRQN);
	
	NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
	NVIC_EnableIRQ(UART_1_INST_INT_IRQN);//ʹ���ж�
	NVIC_EnableIRQ(UART_2_INST_INT_IRQN);
	
	DL_UART_clearInterruptStatus(UART_0_INST,DL_UART_INTERRUPT_RX);//����жϱ�־λ
	DL_UART_clearInterruptStatus(UART_1_INST,DL_UART_INTERRUPT_RX);//����жϱ�־λ
	DL_UART_clearInterruptStatus(UART_2_INST,DL_UART_INTERRUPT_RX);//����жϱ�־λ

}


//�����ж�
void UART_0_INST_IRQHandler(void)
{
	switch( DL_UART_getPendingInterrupt(UART_0_INST) )
	{
		case DL_UART_IIDX_RX:
		{
			
		 uint8_t ch = DL_UART_Main_receiveData(UART_0_INST);
			break;
		}
		default:
			break;
	}
}
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
					memset((void *)dataBuffer,0,sizeof(dataBuffer));
               dataIndex = 0; // ��������
					
            }
				// ����8�ֽ����ݰ�
             else if (dataIndex >= 8 && dataBuffer[0] == 0x01 && dataBuffer[1] == 0x36 && dataBuffer[7] == 0x6B)
            {
                
              Read_Pos(dataBuffer);
				
					memset((void *)dataBuffer,0,sizeof(dataBuffer));
                dataIndex = 0; // ��������
            }
				else if (dataIndex >= 8 && dataBuffer[0] == 0x01 && dataBuffer[1] == 0x30 && dataBuffer[7] == 0x6B)
            {
                
               Read_Pul(dataBuffer);
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

//5c  flag1 error1  flag2 error2 a5
uint8_t dataBuffer2[7];
uint16_t dataIndex2 = 0;
uint8_t PID_flag;
extern uint8_t con_flag,stop_flag;
void UART_2_INST_IRQHandler(void)
{
  switch (DL_UART_Main_getPendingInterrupt(UART_2_INST))
  {
    case DL_UART_MAIN_IIDX_RX:
    {
		
		 DL_GPIO_togglePins(LED_PORT,LED_PIN0_PIN);
      uint8_t ch = DL_UART_Main_receiveData(UART_2_INST);
		
       if (dataIndex2 < 7)
            {
                dataBuffer2[dataIndex2++] = ch;
				
            }
            // ����Ƿ���յ����������ݰ� (֡ͷ0x5c, flag1, error1, flag2, error2, ֡β0xA5)
       if (dataIndex2 >= 6 && dataBuffer2[0] == 0x5c && dataBuffer2[5] == 0xA5)
         {
				// uart2_send_string((uint8_t *)dataBuffer);
//				for(int i=0;i<6;i++)
				uart2_send_char(stop_flag);
				
//					if(dataBuffer2[1]==0xff&&dataBuffer2[2]==0xff)
//					{
//					
//						//Motor_Processdata(dataBuffer2);	//��������
//					
//					
//					else 
//					{
//						error1=0;
//						error2=0;
//					}
//					memset((void *)dataBuffer2, 0, sizeof(dataBuffer2));//������ݰ�
//						 dataIndex2 = 0;
//					} 
					Motor_Processdata(dataBuffer2);
				if(stop_flag<2)
					PID_contorl(5,1);
				if(stop_flag>=2)	Motor_Stop();
					memset((void *)dataBuffer2, 0, sizeof(dataBuffer2));//������ݰ�
					dataIndex2 = 0;
			}
				else if (dataIndex2 == 7)
            {
					
                memset((void *)dataBuffer2, 0, sizeof(dataBuffer2));
                dataIndex2 = 0;
            }
				 DL_UART_clearInterruptStatus(UART_2_INST, DL_UART_INTERRUPT_RX); // ����жϱ�־λ
            break;

	}
			default:
		
			break;
		
	}	 
}


//���ڷ���


void uart2_send_char(char ch)
{
	
	while( DL_UART_isBusy(UART_2_INST) == true );
	
	DL_UART_Main_transmitData(UART_2_INST, ch);

}

void uart2_send_string(char* str)
{
	
	while(*str!=0&&str!=0)
	{
	
		uart2_send_char(*str++);
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


void usart1_send_bytes(unsigned char *buf, int len)
{
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