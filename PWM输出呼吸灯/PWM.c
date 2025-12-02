#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//配置GPIOA，可以看STM32的引脚功能，就知道TIM2的CH1（OC1）复用在了PA0，只能用PA0输出
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//我们要选择复用推挽输出，复用模式才可以接入片上外设进行输出控制，普通推挽或者开漏输出只能接内核
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);//1073后面那几个都是选择时钟的函数，这里我们选择RCC内部时钟
	
	TIM_TimeBaseInitTypeDef Time_Initstructure;
	Time_Initstructure.TIM_ClockDivision=TIM_CKD_DIV1;
	Time_Initstructure.TIM_CounterMode=TIM_CounterMode_Up;
	Time_Initstructure.TIM_Period=100-1;//自动重装寄存器
	Time_Initstructure.TIM_Prescaler=720-1;//预分频器。需要输出1000HZ，预分频器给720-1
	Time_Initstructure.TIM_RepetitionCounter=0;//重复计数器，高级计数器TIM1才有，不需要
	TIM_TimeBaseInit(TIM2,&Time_Initstructure);//这个函数会手动生成一个更新事件，所以计数从1开始，后面加一个标志位清除就可以了
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	TIM_Cmd(TIM2,ENABLE);
	
	TIM_OCInitTypeDef PWM_Initstructure;//有些成员用不着，比如带N的，但是我们不赋值又会出问题，所以需要给结构体赋初始值
	TIM_OCStructInit(&PWM_Initstructure);//给结构体赋初始值，其实就是写一个函数给每个成员一个值。库函数已经有了这个函数
	PWM_Initstructure.TIM_OCMode=TIM_OCMode_PWM1;//输出比较模式选择，选择PWM模式
	PWM_Initstructure.TIM_OCPolarity=TIM_OCPolarity_High;//选择极性，高极性意思就是输出不反转电平，详细可以去看输出比较寄存器的工作电路
	PWM_Initstructure.TIM_OutputState=TIM_OutputState_Enable ;//输出使能
	PWM_Initstructure.TIM_Pulse=50;
	TIM_OC1Init(TIM2,&PWM_Initstructure);//我们准备使用PA0进行PWM输出，PA0对应的输出比较口是OC1
	
}

void setPWM(uint16_t input)
{
	TIM_SetCompare1(TIM2,input);
}
