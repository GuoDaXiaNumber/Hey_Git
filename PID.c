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
	int SetPoint;			//期望的位置
	uint32_t Kp; 			//比例
	uint32_t Ki;			//积分
	uint32_t Kd;			//微分

	int32_t Error;				//此次偏差
	int32_t LastError; 		// Error[-1] 上一次偏差
	int32_t PrevError; 		// Error[-2] 上上次偏差
	float SumError;		 	  // 总的偏差

}PID;

u32 servo_A_control_PWM,servo_B_control_PWM;//舵机A的最终PWM，舵机B的最终PWM
PID pid_servo_A;
PID pid_servo_B;
float SP_A,SI_A,SD_A;
float SP_B,SI_B,SD_B;

float SError_P_A,SError_I_A,SError_D_A;


u16 partial_X=0,partial_Y=0;//分解后的X，Y坐标

void PID_Init_servo_A(int Point,uint32_t kp,uint32_t ki,uint32_t kd)//舵机A的PID函数
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

void servo_A_control(void)/////舵机A控制函数
{
	pid_servo_A.Error = pid_servo_A.SetPoint - partial_X ;//舵机A的偏差

	SError_P_A = pid_servo_A.Error - pid_servo_A.LastError;
	SError_I_A = pid_servo_A.Error;
	SError_D_A = pid_servo_A.Error - 2*pid_servo_A.LastError + pid_servo_A.PrevError;
	pid_servo_A.SumError = SP_A*SError_P_A + SI_A*SError_I_A + SD_A*SError_D_A;	
	servo_A_control_PWM = (int)pid_servo_A.SumError + servo_A_control_PWM; 

	pid_servo_A.PrevError=pid_servo_A.LastError;
	pid_servo_A.LastError=pid_servo_A.Error;
	//////舵机A限幅///////
	if(servo_A_control_PWM > servo_A_MAX) servo_A_control_PWM = servo_A_MAX;
	if(servo_A_control_PWM < servo_A_MIN) servo_A_control_PWM = servo_A_MIN;
	//////改变舵机PWM/////
	TIM_SetCompare2(TIM3,servo_A_control_PWM);
}



