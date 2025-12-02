#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		
		GPIO_InitTypeDef GPIO_instructure;
		GPIO_instructure.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_instructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_2;
		GPIO_instructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_instructure);
	
		GPIO_SetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_2);
}

void LED1_ON(void)
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
}

void LED1_OFF(void)
{
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
}

void LED1_turn(void) //按下点亮，再按一下熄灭
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0)==0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	}
}

void LED2_ON(void)
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}

void LED2_OFF(void)
{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
}

void LED2_turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2)==0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
}
