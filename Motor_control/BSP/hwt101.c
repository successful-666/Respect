#include "hwt101.h"

struct Gyro	hwt101;

void hwt101_Set_Bound(usart_send_bytes_t usart_send_bytes,uint32_t bound)
{
	uint8_t cmd[3];
	
	if(bound == 9600 || bound == 115200)
	{
		//装载命令
		cmd[0] = 0xFF;		//协议头
		cmd[1] = 0xAA;		//协议头
	
		if(bound == 9600) cmd[2] = 0x64;
		
		if(bound == 115200) cmd[2]= 0x63;
		
		usart_SendCmd(usart_send_bytes,cmd,3);
	}
	
}

void hwt101_Read_Angle(uint8_t *data)
{
	//判断协议头	55 53 4*00 yawL yawH VL VH SUM
	//SUM=0x55+0x53+YawH+YawL+VH+VL
	
	if(data[0]==0x55 && data[1]==0x53)
	{
		if(data[10] == (data[0]+data[1]+data[6]+data[7]+data[8]+data[9]))
		{
			//Z=((YawH<<8)|YawL)/32768*180
			hwt101.Angle = ((float)(data[6]<<8|data[7])/32768*180);
		}
	}
}