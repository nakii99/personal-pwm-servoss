#include "pwm.h"


TIM_HandleTypeDef TIM3_HandleStruct;
void initPWM(void)
{
	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	//Initialize pin
	//-------------------------------------------------------------------------------
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	//Configure timer
	//-------------------------------------------------------------------------------
	__HAL_RCC_TIM3_CLK_ENABLE();

	TIM_Base_InitTypeDef TIM_Base_InitStruct;
	TIM_Base_InitStruct.Prescaler = 84;
	TIM_Base_InitStruct.CounterMode = TIM_COUNTERMODE_UP;
	TIM_Base_InitStruct.Period = 19999;
	TIM_Base_InitStruct.ClockDivision =	TIM_CLOCKDIVISION_DIV1;
	TIM_Base_InitStruct.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

	TIM3_HandleStruct.Instance = TIM3;
	TIM3_HandleStruct.Init = TIM_Base_InitStruct;

	HAL_TIM_PWM_Init(&TIM3_HandleStruct);

	TIM_OC_InitTypeDef TIM_OC_InitStruct;
	TIM_OC_InitStruct.OCMode = TIM_OCMODE_PWM1;
	TIM_OC_InitStruct.Pulse = 0;
	TIM_OC_InitStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
	TIM_OC_InitStruct.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&TIM3_HandleStruct, &TIM_OC_InitStruct, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&TIM3_HandleStruct,TIM_CHANNEL_1);


}
void setPWM(uint32_t ccr1)
{
	__HAL_TIM_SET_COMPARE(&TIM3_HandleStruct,TIM_CHANNEL_1,ccr1);
}



void setAngleSG90(uint32_t angle) {
	if (angle == 0) {
		setPWM(1500);
	} else if (angle == 90) {
		setPWM(2400);
	} else if (angle == -90) {
		setPWM(500);
	} else {
		printUSART2("Can't move to that angle");
	}
}