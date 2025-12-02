#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int16_t Encoder_Count=0;   //创建个带符号变量用于正反转的显示

void Encoder_Init(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
		GPIO_InitTypeDef GPIO_structure;
		GPIO_structure.GPIO_Mode=GPIO_Mode_IPU;
		GPIO_structure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1;
		GPIO_structure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_structure);
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);//配置AFIO
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
		EXTI_InitTypeDef EXTI_InitStructure; 											//配置EXTI
		EXTI_InitStructure.EXTI_Line=EXTI_Line0 | EXTI_Line1;
		EXTI_InitStructure.EXTI_LineCmd=ENABLE;
		EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
		EXTI_Init(&EXTI_InitStructure);
		
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//配置NVIC的抢占和响应
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//配置抢占优先级，在先前写的第二组里面选（NVIC_PriorityGroup_2）
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//配置中断优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//配置抢占优先级，在先前写的第二组里面选（NVIC_PriorityGroup_2）
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;//配置中断优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}

int16_t getnumber(void)
{
	uint16_t TEMP;
	TEMP=Encoder_Count;
	Encoder_Count=0;
	return TEMP;
}

void EXTI0_IRQHandler(void)
{	
	if(EXTI_GetITStatus(EXTI_Line0)==SET)//查一下EXTI0的中断标志位是否置1了
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)//根据旋转编码器的波形判断，如果A相的下降沿触发了中断，那么B相为低电平认定为正转
		{
			Encoder_Count --; //中断程序最好不要有延时函数，中断最重要的是执行迅速
		}
		EXTI_ClearITPendingBit(EXTI_Line0);//如果中断标志位不置0，那中断程序会一直申请，会死循环，所以执行完中断程序需要把标志位置0
	}
}

void EXTI1_IRQHandler(void)
{	
	if(EXTI_GetITStatus(EXTI_Line1)==SET)//查一下EXTI1的中断标志位是否置1了
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)//同理，如果B相的下降沿触发了中断，那么A相为低电平认定为反转
		{
			Encoder_Count ++;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);//如果中断标志位不置0，那中断程序会一直申请，会死循环，所以执行完中断程序需要把标志位置0
	}
}
