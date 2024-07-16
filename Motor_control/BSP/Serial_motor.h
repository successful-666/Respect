#ifndef	__SERIAL_MOTOR_H__
#define 	__SERIAL_MOTOR_H__

#include "ti_msp_dl_config.h"
#include "bsp_uart.h"

#define		ABS(x)		((x) > 0 ? (x) : -(x)) 


typedef enum {
	S_VER   = 0,			/* 读取固件版本和对应的硬件版本 */
	S_RL    = 1,			/* 读取读取相电阻和相电感 */
	S_PID   = 2,			/* 读取PID参数 */
	S_VBUS  = 3,			/* 读取总线电压 */
	S_CPHA  = 5,			/* 读取相电流 */
	S_ENCL  = 7,			/* 读取经过线性化校准后的编码器值 */
	S_CPUL  = 8,      /* 读取实时脉冲数（根据实时位置计算得到的脉冲数） */
	S_TPOS  = 9,			/* 读取电机目标位置角度 */
	S_VEL   = 10,			/* 读取电机实时转速 */
	S_CPOS  = 11,			/* 读取电机实时位置角度 */
	S_PERR  = 12,			/* 读取电机位置误差角度 */
	S_FLAG  = 13,			/* 读取使能/到位/堵转状态标志位 */
	S_Conf  = 14,			/* 读取驱动参数 */
	S_State = 15,			/* 读取系统状态参数 */
	S_ORG   = 16,     /* 读取正在回零/回零失败状态标志位 */
}SysParams_t;



typedef enum{
	CW 	= 	0, //顺时针
	CCW	=	1,	//逆时针 
}Dir;

struct Params
{
	int Cur_Pos;		//位置
	int Cur_Val;		//速度
	int Cur_Pul;		//脉冲数
	uint8_t Cur_sta;	//状态
};



//将当前位置清零
void Emm_V5_Reset_CurPos_To_Zero(usart_send_bytes_t usart_send_bytes,uint8_t addr);
//速度模式
void Emm_V5_Vel_Control(usart_send_bytes_t,uint8_t addr, uint8_t dir, uint16_t vel, uint8_t acc, bool snF);
//位置模式
void Emm_V5_Pos_Control(usart_send_bytes_t,uint8_t addr, uint8_t dir, uint16_t vel, uint8_t acc, uint32_t clk, bool raF, bool snF);
//急停
void Emm_V5_Stop_Now(usart_send_bytes_t,uint8_t addr, bool snF);
//设置零点
void Emm_V5_Origin_Set_Zero(usart_send_bytes_t,uint8_t addr, bool svF);
//触发回零
void Emm_V5_Origin_Trigger_Return_Zero(usart_send_bytes_t,uint8_t addr, uint8_t o_mode, bool snF);
//改变细分
void Emm_V5_Change_XF(usart_send_bytes_t,uint8_t addr,bool save ,uint8_t XF);
//读取参数
void Emm_V5_Read_Sys_Params(usart_send_bytes_t,uint8_t addr, SysParams_t s);
//请求实时脉冲
void WRead_Pul(usart_send_bytes_t usart_send_bytes,uint8_t addr);

//实时转速 
void Read_Val(uint8_t *data);
//读取实时位置
void Read_Pos(uint8_t *data);
//读取实时脉冲
void Read_Pul(uint8_t *data);


#endif
