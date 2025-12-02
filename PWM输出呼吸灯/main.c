#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"
#include "PWM.h"

uint16_t i;

int main(void)
{
	OLED_Init();
	PWM_Init();
	
	while(1)
	{
	for(i=0;i<100;i++)
	{
		setPWM(i);
		Delay_ms(20);//设置20ms延时，要大于PWM的周期
	}
}
}
