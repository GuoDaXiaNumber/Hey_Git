#include "PID.h"
#include "stm32f10x.h"

#define servo_A_MAX		1900
#define servo_A_MIN		1800
#define servo_A_BASE 	1890
#define servo_B_MAX  	1900
#define servo_B_MIN  	1800
#define servo_B_BASE	1895

typedef struct 
{
	int SetPoint;			//������λ��
	uint32_t Kp; 			//����
	uint32_t Ki;			//����
	uint32_t Kd;			//΢��

	int32_t Error;				//�˴�ƫ��
	int32_t LastError; 		// Error[-1] ��һ��ƫ��
	int32_t PrevError; 		// Error[-2] ���ϴ�ƫ��
	float SumError;		 	  // �ܵ�ƫ��

}PID;

u32 servo_A_control_PWM,servo_B_control_PWM;//���A������PWM�����B������PWM
PID pid_servo_A;
PID pid_servo_B;
float SP_A,SI_A,SD_A;
float SP_B,SI_B,SD_B;

float SError_P_A,SError_I_A,SError_D_A;


u16 partial_X=0,partial_Y=0;//�ֽ���X��Y����

void PID_Init_servo_A(int Point,uint32_t kp,uint32_t ki,uint32_t kd)//���A��PID����
{
	pid_servo_A.SetPoint =Point;	                                	
	pid_servo_A.SumError = 0;
	
	pid_servo_A.Kp=kp;
	pid_servo_A.Ki=ki;
	pid_servo_A.Kd=kd;
	
	pid_servo_A.Error=0;     
	pid_servo_A.LastError=0; //Error[-1]
	pid_servo_A.PrevError=0; //Error[-2]

	SP_A=pid_servo_A.Kp/10.f;
	SI_A=pid_servo_A.Ki/10.f;
	SD_A=pid_servo_A.Kd/10.f;	
}

void servo_A_control(void)/////���A���ƺ���
{
	pid_servo_A.Error = pid_servo_A.SetPoint - partial_X ;//���A��ƫ��

	SError_P_A = pid_servo_A.Error - pid_servo_A.LastError;
	SError_I_A = pid_servo_A.Error;
	SError_D_A = pid_servo_A.Error - 2*pid_servo_A.LastError + pid_servo_A.PrevError;
	pid_servo_A.SumError = SP_A*SError_P_A + SI_A*SError_I_A + SD_A*SError_D_A;	
	servo_A_control_PWM = (int)pid_servo_A.SumError + servo_A_control_PWM; 

	pid_servo_A.PrevError=pid_servo_A.LastError;
	pid_servo_A.LastError=pid_servo_A.Error;
	//////���A�޷�///////
	if(servo_A_control_PWM > servo_A_MAX) servo_A_control_PWM = servo_A_MAX;
	if(servo_A_control_PWM < servo_A_MIN) servo_A_control_PWM = servo_A_MIN;
	//////�ı���PWM/////
	TIM_SetCompare2(TIM3,servo_A_control_PWM);
}



