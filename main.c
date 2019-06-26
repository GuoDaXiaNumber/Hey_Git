#include "stm32f10x.h"
#include "all_init.h"
#include "fun.h"
#include "timer.h"
#include "uart.h"

//u16 Coordinate_X=102,Coordinate_Y=123;	
//u8    disbuf[8]={1,2,3,4,5,6,7,8};


//void NVIC_Configuration(void)
//{
//	NVIC_InitTypeDef NVIC_InitStructure;

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//	NVIC_Init(&NVIC_InitStructure);		
//	
//}

//*******************������********************************************
int main(void)
{  
	u16 PWM_X=1700,PWM_Y=1700;
	all_init();     		//����/LED��ʼ��   
	RCC_Configuration();	//ʱ�ӳ�ʼ��
//	SysTick_Config(SystemCoreClock /10000);  //����Ϊ1000΢��
////	NVIC_Configuration();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);			
//	TIM1_PWM_Init(1999,719);	 //����Ƶ��PWMƵ��=72000000/((7199+1)*(199+1))=50hz	
//	TIM2_PWM_Init(1999,719); 	//50hz   1950-1850-1750
	TIM4_PWM_Init(1999,719);
	TIM3_PWM_Init(1999,719); 	//50hz   1950-1850-1750
//	TIM2_PWM_Init(1999,359);   //100hz  1900-1700-1500
	
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);  //���������
//  GPIO_SetBits(GPIOB,GPIO_Pin_1);	//Ϩ�������
	while(1)
	{
//		Coordinate_X=recvalue/1000;
//		Coordinate_Y=recvalue%1000;
//		PWM_X = 1840-Coordinate_X;
//		PWM_Y = 1840-Coordinate_Y;
//		if(PWM_X>=1950)PWM_X=1750;	
//		TIM_SetCompare2(TIM3,PWM_X);	
//		if(PWM_Y>=1950)PWM_Y=1750;	
//		TIM_SetCompare1(TIM4,PWM_Y);	
			show_number(0);
	}
} 
			
// 
//void SysTick_Handler(void)    //һ��С��ʱ�ж�//1ms  //�ж�������
//{
//	static u8 count=0;
//  if(++count==2)	
//  {	
//			count=0;
//			if(recvalue) 
//			{ 
//				disbuf[7]=Coordinate_Y%10;           //��λ
//				disbuf[6]=Coordinate_Y/10%10;         //ʮλ
//				disbuf[5]=Coordinate_Y/100%10;        //��λ
//				disbuf[4]=Coordinate_X/1000%10;       //ǧλ
//				disbuf[3]=Coordinate_X/10000%10;      //��λ
//				disbuf[2]=Coordinate_X/100000%10; 
//				//disbuf[1]=num/1000000%10;      //��λ
//				//disbuf[0]=num/10000000%10; 
//			} 		 
//	}               
//		
//  display(disbuf);
//	
//}  

