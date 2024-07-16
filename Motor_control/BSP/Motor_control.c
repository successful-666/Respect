#include "Motor_control.h"
#include "board.h"
#include "stdlib.h" 
#include "string.h"

uint8_t stop_flag;
int target_LV,target_RV;
int error1,error2;
uint8_t corner;
uint8_t con_flag=1;

extern struct Params	Motor;

void Motor_Stop(void)
{
	Emm_V5_Stop_Now(usart0_send_bytes,1,0);
	Emm_V5_Stop_Now(usart1_send_bytes,1,0);
}

void Motor_Forward(int speed_L,int speed_R)
{
	Emm_V5_Vel_Control(usart1_send_bytes,1,CW,speed_L,0,0);
	Emm_V5_Vel_Control(usart0_send_bytes,1,CCW,speed_R,0,0);
}

void Motor_Back(int speed_L,int speed_R)
{
	Emm_V5_Vel_Control(usart1_send_bytes,1,CCW,speed_L,0,0);
	Emm_V5_Vel_Control(usart0_send_bytes,1,CW,speed_R,0,0);
}

void Motor_Forward_CLK(int speed_LV_clk,int speed_RV_clk)
{
	Emm_V5_Pos_Control(usart1_send_bytes,1,CW,50,2,speed_LV_clk,0,0);
	Emm_V5_Pos_Control(usart0_send_bytes,1,CCW,50,2,speed_RV_clk,0,0);
	
}


void PID_contorl(float kp1,float kp2)
{
	
	if(abs(error1)>25)	error1=0;
	

	if(abs(error2)>=0&&abs(error2)<=5)
	{
		kp2 = 2;
		
	}
	if(abs(error2)>5 &&abs(error2)<= 10)
	{
		kp2 = 7;
	}
		
		error2 = error2 - 6;
	
	target_LV=80 +(+ error1*kp1 + error2*kp2)*con_flag;
	target_RV=80 +(- error2*kp2 - error2*kp2)*con_flag;
	
	
	
	if(target_LV<0)	target_LV =0;
	if(target_RV<0)	target_RV=0;
	if(target_LV>180)target_LV=180;
	if(target_RV>180)target_RV=180;
	
	Motor_Forward(target_LV,target_RV);

}
void Motor_Processdata(uint8_t *data)
{
//    /* 检测拐点 */
   if (data[1] == 0xff && data[2] == 0xff)
    {
       corner++; // 拐点计数器自增
        switch (corner)
       {
			 
           case 1:
                con_flag = 0; // 设置标志位
                data[1] = 0; // 重置数据
                data[2] = 0;
					 data[3] = 0;
					 data[4] = 0;
                error1 = 0; // 重置错误值
                error2 = 0;
                break;
            case 2:
               
					 data[1] = 0; // 重置数据
                data[2] = 0;
					 data[3] = 0;
					 data[4] =0 ;
                error1 = 0; // 重置错误值
                error2 = 0;
					 con_flag = 1; // 设置标志位
                break;
//            case 3:
//                con_flag = 0; // 设置标志位
//                break;
            default:
                break;
       }
			 error1 = 0; // 重置错误值
          error2 = 0;	
    }
	 if(data[1]==0xee && data[2]==0xee)
	 {
		 stop_flag++;
		 data[1] = 0; // 重置数据
       data[2] = 0;
		 data[3] = 0;
		 data[4] =0 ;
		 error1=0;
		 error2=0;
	 }

    /* 计算error1 */
    if (data[1] == 0)
    {
        error1 = -data[2]; // 如果data[1]为0，则error1取负值
    }
     else if(data[1]==1)
    {
        error1 = data[2]; // 否则，error1取正值
    }

    /* 计算error2 */
    if (data[3] == 0)
    {
        error2 = -data[4]; // 如果data[3]为0，则error2取负值
    }
    else if(data[3]==1)
    {
        error2 = data[4]; // 否则，error2取正值
    }
	 
}

void limit(int *Left,int *Right,int LV,int RV)
{
	
	
}


void contorl(void)
{
	
	
}

