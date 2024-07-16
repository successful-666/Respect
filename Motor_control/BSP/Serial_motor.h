#ifndef	__SERIAL_MOTOR_H__
#define 	__SERIAL_MOTOR_H__

#include "ti_msp_dl_config.h"
#include "bsp_uart.h"

#define		ABS(x)		((x) > 0 ? (x) : -(x)) 


typedef enum {
	S_VER   = 0,			/* ��ȡ�̼��汾�Ͷ�Ӧ��Ӳ���汾 */
	S_RL    = 1,			/* ��ȡ��ȡ���������� */
	S_PID   = 2,			/* ��ȡPID���� */
	S_VBUS  = 3,			/* ��ȡ���ߵ�ѹ */
	S_CPHA  = 5,			/* ��ȡ����� */
	S_ENCL  = 7,			/* ��ȡ�������Ի�У׼��ı�����ֵ */
	S_CPUL  = 8,      /* ��ȡʵʱ������������ʵʱλ�ü���õ����������� */
	S_TPOS  = 9,			/* ��ȡ���Ŀ��λ�ýǶ� */
	S_VEL   = 10,			/* ��ȡ���ʵʱת�� */
	S_CPOS  = 11,			/* ��ȡ���ʵʱλ�ýǶ� */
	S_PERR  = 12,			/* ��ȡ���λ�����Ƕ� */
	S_FLAG  = 13,			/* ��ȡʹ��/��λ/��ת״̬��־λ */
	S_Conf  = 14,			/* ��ȡ�������� */
	S_State = 15,			/* ��ȡϵͳ״̬���� */
	S_ORG   = 16,     /* ��ȡ���ڻ���/����ʧ��״̬��־λ */
}SysParams_t;



typedef enum{
	CW 	= 	0, //˳ʱ��
	CCW	=	1,	//��ʱ�� 
}Dir;

struct Params
{
	int Cur_Pos;		//λ��
	int Cur_Val;		//�ٶ�
	int Cur_Pul;		//������
	uint8_t Cur_sta;	//״̬
};



//����ǰλ������
void Emm_V5_Reset_CurPos_To_Zero(usart_send_bytes_t usart_send_bytes,uint8_t addr);
//�ٶ�ģʽ
void Emm_V5_Vel_Control(usart_send_bytes_t,uint8_t addr, uint8_t dir, uint16_t vel, uint8_t acc, bool snF);
//λ��ģʽ
void Emm_V5_Pos_Control(usart_send_bytes_t,uint8_t addr, uint8_t dir, uint16_t vel, uint8_t acc, uint32_t clk, bool raF, bool snF);
//��ͣ
void Emm_V5_Stop_Now(usart_send_bytes_t,uint8_t addr, bool snF);
//�������
void Emm_V5_Origin_Set_Zero(usart_send_bytes_t,uint8_t addr, bool svF);
//��������
void Emm_V5_Origin_Trigger_Return_Zero(usart_send_bytes_t,uint8_t addr, uint8_t o_mode, bool snF);
//�ı�ϸ��
void Emm_V5_Change_XF(usart_send_bytes_t,uint8_t addr,bool save ,uint8_t XF);
//��ȡ����
void Emm_V5_Read_Sys_Params(usart_send_bytes_t,uint8_t addr, SysParams_t s);
//����ʵʱ����
void WRead_Pul(usart_send_bytes_t usart_send_bytes,uint8_t addr);

//ʵʱת�� 
void Read_Val(uint8_t *data);
//��ȡʵʱλ��
void Read_Pos(uint8_t *data);
//��ȡʵʱ����
void Read_Pul(uint8_t *data);


#endif
