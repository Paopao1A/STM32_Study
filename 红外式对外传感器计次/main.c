#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"
#include "CountSensor.h"

int main(void)
{
	OLED_Init();
	CountSensor_Init();
	OLED_ShowString(1,3,"HelloWorld");
	
	while(1)
	{
	OLED_ShowNum(2,7,getnumber(),5);

  }
}
