#ifndef MCU_RCC_H
#define MCU_RCC_H


#include "stm32wbaxx.h"


/*================== AHBx and APBx peripherals ==============================*/
/* RCC peripherals used within the scope of the project */
/* For minimal flash size and control over the low power behavior, and RCC  layer small and tested.*/

/* AHBx Peripherals */
typedef enum
{
	GpioA = RCC_AHB2ENR_GPIOAEN_Pos,
	GpioB = RCC_AHB2ENR_GPIOBEN_Pos,
	GpioC = RCC_AHB2ENR_GPIOCEN_Pos,
}MCU_RCC_AHB2Peripherals_t;

typedef enum
{
	Pwr = RCC_AHB4ENR_PWREN_Pos,
}MCU_RCC_AHB4Peripherals_t;

typedef enum
{
	Radio = RCC_AHB5ENR_RADIOEN_Pos,
}MCU_RCC_AHB5Peripherals_t;

typedef enum
{
	Tim2 = RCC_APB1ENR1_TIM2EN_Pos,
	Tim3 = RCC_APB1ENR1_TIM3EN_Pos,
	Wwdg = RCC_APB1ENR1_WWDGEN_Pos,
	Usart2 = RCC_APB1ENR1_USART2EN_Pos,
	I2c1 = RCC_APB1ENR1_I2C1EN_Pos,
}MCU_RCC_APB1Reg1Peripherals_t;

typedef enum
{
	Lptim2 = RCC_APB1ENR2_LPTIM2EN_Pos,		// belongs to RCC_APB1ENR2
}MCU_RCC_APB1Reg2Peripherals_t;

typedef enum
{
	Usart1 = RCC_APB2ENR_USART1EN_Pos,
}MCU_RCC_APB2Peripherals_t;

typedef enum
{
	I2c3 = RCC_APB7ENR_I2C3EN_Pos,
}MCU_RCC_APB7Peripherals_t;

/* AHB2 peripherals - GPIOA, GPIOB, GPIOC */
ResultStatus RCC_SetPeripheralClk_AHB2(MCU_RCC_AHB2Peripherals_t peripheralPos, FunctionalState state);
ResultStatus RCC_ResetPeripheralClk_AHB2(MCU_RCC_AHB2Peripherals_t peripheralPos);

/* AHB4 peripherals - EXTI, RCC, PWR */
ResultStatus RCC_SetPeripheralClk_AHB4(MCU_RCC_AHB4Peripherals_t peripheralPos, FunctionalState state);

/* AHB5 peripherals - radio */
ResultStatus RCC_SetPeripheralClk_AHB5(MCU_RCC_AHB5Peripherals_t peripheralPos, FunctionalState state);
ResultStatus RCC_ResetPeripheralClk_AHB5(MCU_RCC_AHB5Peripherals_t peripheralPos);

/* APB1ENR1 peripherals - tim2, tim3, IWDG, WWDG, USART2, I2C1 */
ResultStatus RCC_SetPeripheralClk_APB1ENR1(MCU_RCC_APB1Reg1Peripherals_t peripheralPos, FunctionalState state);
ResultStatus RCC_ResetPeripheralClk_APB1RSTR1(MCU_RCC_APB1Reg1Peripherals_t peripheralPos);

/* APB1ENR2 peripherals - lptim2 */
ResultStatus RCC_SetPeripheralClk_APB1ENR2(MCU_RCC_APB1Reg2Peripherals_t peripheralPos, FunctionalState state);
ResultStatus RCC_ResetPeripheralClk_APB1RSTR2(MCU_RCC_APB1Reg2Peripherals_t peripheralPos);

/* APB2 peripherals - USART1 */
ResultStatus RCC_SetPeripheralClk_APB2(MCU_RCC_APB2Peripherals_t peripheralPos, FunctionalState state);
ResultStatus RCC_ResetPeripheralClk_APB2(MCU_RCC_APB2Peripherals_t peripheralPos);

/* APB7 peripherals - I2C3 */
ResultStatus RCC_SetPeripheralClk_APB7(MCU_RCC_APB7Peripherals_t peripheralPos, FunctionalState state);
ResultStatus RCC_ResetPeripheralClk_APB7(MCU_RCC_APB7Peripherals_t peripheralPos);

#endif
