#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"
#include "Timer.h"

extern uint16_t Num;//extern声明一个外部变量，就可以使用别的文件里面定义的变量了

int main(void)
{
	OLED_Init();
	Timer_Init();
	
	OLED_ShowString(1,1,"Num=");
	while(1)
	{
		OLED_ShowNum(1,7,Num,5);
  }
}
