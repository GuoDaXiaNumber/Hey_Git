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

//*******************主程序********************************************
int main(void)
{  
	u16 PWM_X=1700,PWM_Y=1700;
	all_init();     		//按键/LED初始化   
	RCC_Configuration();	//时钟初始化
//	SysTick_Config(SystemCoreClock /10000);  //周期为1000微秒
////	NVIC_Configuration();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);			
//	TIM1_PWM_Init(1999,719);	 //不分频。PWM频率=72000000/((7199+1)*(199+1))=50hz	
//	TIM2_PWM_Init(1999,719); 	//50hz   1950-1850-1750
	TIM4_PWM_Init(1999,719);
	TIM3_PWM_Init(1999,719); 	//50hz   1950-1850-1750
//	TIM2_PWM_Init(1999,359);   //100hz  1900-1700-1500
	
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);  //点亮数码管
//  GPIO_SetBits(GPIOB,GPIO_Pin_1);	//熄灭数码管
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

/*测试更改
*input:null
*output:null
*return:null
*note:注释掉，用不到
*/
//void SysTick_Handler(void)    //一个小定时中断//1ms  //中断向量表
//{
//	static u8 count=0;
//  if(++count==2)	
//  {	
//			count=0;
//			if(recvalue) 
//			{ 
//				disbuf[7]=Coordinate_Y%10;           //个位
//				disbuf[6]=Coordinate_Y/10%10;         //十位
//				disbuf[5]=Coordinate_Y/100%10;        //百位
//				disbuf[4]=Coordinate_X/1000%10;       //千位
//				disbuf[3]=Coordinate_X/10000%10;      //万位
//				disbuf[2]=Coordinate_X/100000%10; 
//				//disbuf[1]=num/1000000%10;      //万位
//				//disbuf[0]=num/10000000%10; 
//			} 		 
//	}               
//		
//  display(disbuf);
//	
//}  
