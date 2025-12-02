#include "stm32f10x.h"                  // Device header

void Sensor_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct_B;//配置PB13
	GPIO_InitStruct_B.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct_B.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_13;
	GPIO_InitStruct_B.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct_B);
}

uint8_t Sensor_Num(void)
{
  uint8_t SensorNum=0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0)
	{
		SensorNum=1;//光敏电阻电阻值大，光弱
	}
	else
	{
		SensorNum=2;//光敏电阻电阻值小，光强
	}
return SensorNum;
}
