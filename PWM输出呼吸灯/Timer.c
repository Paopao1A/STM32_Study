#include "stm32f10x.h"                  // Device header

uint16_t Num;

void Timer_Init(void)
{
	//定时器中断配置流程
	//RCC内部时钟
	//配置时钟的模式（内部时钟，外部时钟）
	//配置时基单元（预分频器、计数器、自动重装器）
	//中断输出控制，允许输出中断到NVIC
	//配置NVIC
	//使能一下计数器，不然不会工作
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	
	TIM_InternalClockConfig(TIM2);//1073后面那几个都是选择时钟的函数，这里我们选择RCC内部时钟
	
	TIM_TimeBaseInitTypeDef Time_Initstructure;
	Time_Initstructure.TIM_ClockDivision=TIM_CKD_DIV1;
	Time_Initstructure.TIM_CounterMode=TIM_CounterMode_Up;
	Time_Initstructure.TIM_Period=10000-1;//自动重装寄存器
	Time_Initstructure.TIM_Prescaler=7200-1;//预分频器。假如我们需要1s的定时，那就（10000-1+1）*（7200-1+1）/72M
	Time_Initstructure.TIM_RepetitionCounter=0;//重复计数器，高级计数器TIM1才有，不需要
	TIM_TimeBaseInit(TIM2,&Time_Initstructure);//这个函数会手动生成一个更新事件，所以计数从1开始，后面加一个标志位清除就可以了
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_Initstructure;
	NVIC_Initstructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_Initstructure);
	
	TIM_Cmd(TIM2,ENABLE);
}


//uint16_t getnumber(void)
//{

//	return Num;
//}

void TIM2_IRQHandler(void)//TIM2的中断函数，在start文件里找
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //检查中断标志位是否置1,TIM_IT_Update是看更新中断，定时器有很多中断，所以需要选择
	{
		Num ++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}