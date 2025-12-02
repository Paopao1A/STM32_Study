#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"
#include "Encoder.h"

int16_t Num;

int main(void)
{
	OLED_Init();
	Encoder_Init();
	OLED_ShowString(1,3,"HelloWorld");
	
	while(1)
	{
		
	Num += getnumber();
	OLED_ShowSignedNum(2,7,Num,5);

  }
}
