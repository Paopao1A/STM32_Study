#include "stm32f10x.h"                  // Device header
#include "Delay.h"

uint8_t CountSensor_Count=0;   //创建个变量用于每次中断之后加一

void CountSensor_Init(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//请求中端需要配置GPIO(APB2外设),AFIO（APB2外设）,EXTI（时钟始终打开）,NVIC（时钟始终打开，内核外设都是始终打开的）
	//GPIO请求输入
	//AFIO主要是筛选中断的引脚，GPIOA,GPIOB都有32个引脚了，PA0和PB0同时都可以响应的话占空间，因此需要筛选
	//EXTI外部中断的控制，主要是选择边沿的触发方式（上升沿或者下降沿触发）以及触发响应方式（中断响应和事件响应）
	//NVIC（内核外设，CPU的小助手）是给中断选择一个合适的优先级，通过NVIC后就可以把中断信号传给CPU了
		GPIO_InitTypeDef GPIO_structure;
		GPIO_structure.GPIO_Mode=GPIO_Mode_IPD;
		GPIO_structure.GPIO_Pin=GPIO_Pin_14;
		GPIO_structure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_structure);
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);//配置AFIO
	
		EXTI_InitTypeDef EXTI_InitStructure; 											//配置EXTI
		EXTI_InitStructure.EXTI_Line=EXTI_Line14;
		EXTI_InitStructure.EXTI_LineCmd=ENABLE;
		EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
		EXTI_Init(&EXTI_InitStructure);
		
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//配置NVIC的抢占和响应
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//配置抢占优先级，在先前写的第二组里面选（NVIC_PriorityGroup_2）
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//配置中断优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		
}

uint8_t getnumber(void)
{
	return CountSensor_Count;
}

void EXTI15_10_IRQHandler(void)//EXTI10-15的中断函数名，在启动文件startup_stm32f10x_md.s可以找到
{	
	if(EXTI_GetITStatus(EXTI_Line14)==SET)//查一下EXTI14的中断标志位是否置1了,函数的返回值SET/RESET，通道14置1我们才可以进行中断程序
	{
		Delay_ms(20);
		CountSensor_Count ++;
		EXTI_ClearITPendingBit(EXTI_Line14);//如果中断标志位不置0，那中断程序会一直申请，会死循环，所以执行完中断程序需要把标志位置0
	}
}
