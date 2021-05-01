#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "delay.h"
#include "pwm.h"



int main(void)
{
	HAL_Init();

	initUSART2(115200);
	initSYSTIM();
	initPWM();

	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	uint16_t pwm[19] = {0,2,5,11,23,50,109,235,509,999,509,235,109,50,23,11,5,2,0};
	uint8_t pwm_cnt = 0;
	while(1)
	{
		// uint16_t duty_cycle = pwm[pwm_cnt++];
		// if(pwm_cnt >= 19)
		// {
		// 	pwm_cnt = 0;
			printUSART2("pwm cnt %d",pwm_cnt);
		// }
		setAngleSG90(90);
		delay_ms(2000);
		setAngleSG90(0);
		delay_ms(2000);
		setAngleSG90(-90);
		delay_ms(2000);
		setAngleSG90(0);
		delay_ms(2000);
	}
}


