#include "mcu_rcc.h"

/* Global Declaration Section*/

#define MCU_RCC_REGISTER_SIZE			32U

/* AHB2 peripherals - GPIOA, GPIOB, GPIOC */
ResultStatus RCC_SetPeripheralClk_AHB2(MCU_RCC_AHB2Peripherals_t peripheralPos, FunctionalState state)
{
	if(peripheralPos >= MCU_RCC_REGISTER_SIZE)
		return STATUS_ERROR;

	if(state==ENABLE)
		RCC_NS->AHB2ENR |= (1U << peripheralPos);
	else if(state==DISABLE)
		RCC_NS->AHB2ENR &= ~(1U << peripheralPos);
	return STATUS_OK;
}

ResultStatus RCC_ResetPeripheralClk_AHB2(MCU_RCC_AHB2Peripherals_t peripheralPos)
{
	if(peripheralPos >= MCU_RCC_REGISTER_SIZE)
		return STATUS_ERROR;

	RCC_NS->AHB2RSTR |= (1U << peripheralPos);
	RCC_NS->AHB2RSTR &= ~(1U << peripheralPos);
	// writing 0 directly does not make any difference to reset effect
	// writing 0 is registered by HW but makes sense only after writing 1
	// it is like button press(write 1 for reset) and release(write 0 to release reset)
	return STATUS_OK;
}

/* AHB4 peripherals - EXTI, RCC, PWR */
/* RCC Clk needs to be enabled only for PWR*/
ResultStatus RCC_SetPeripheralClk_AHB4(MCU_RCC_AHB4Peripherals_t peripheralPos, FunctionalState state)
{
	if(peripheralPos >= MCU_RCC_REGISTER_SIZE)
		return STATUS_ERROR;

	if(state==ENABLE)
		RCC_NS->AHB4ENR |= (1U << peripheralPos);
	else if(state==DISABLE)
		RCC_NS->AHB4ENR &= ~(1U << peripheralPos);
	return STATUS_OK;

}

/* PWR does not have a bit pos in reset reg*/

/* AHB5 peripherals - radio */
ResultStatus RCC_SetPeripheralClk_AHB5(MCU_RCC_AHB5Peripherals_t peripheralPos, FunctionalState state)
{
	if(peripheralPos >= MCU_RCC_REGISTER_SIZE)
		return STATUS_ERROR;

	if(state==ENABLE)
		RCC_NS->AHB5ENR |= (1U << peripheralPos);
	else if(state==DISABLE)
		RCC_NS->AHB5ENR &= ~(1U << peripheralPos);
	return STATUS_OK;

}

ResultStatus RCC_ResetPeripheralClk_AHB5(MCU_RCC_AHB5Peripherals_t peripheralPos)
{
	if(peripheralPos >= MCU_RCC_REGISTER_SIZE)
			return STATUS_ERROR;

	RCC_NS->AHB5RSTR |= (1U << peripheralPos);
	RCC_NS->AHB5RSTR &= ~(1U << peripheralPos);
	return STATUS_OK;

}

/* APB1ENR1 peripherals - tim2, tim3, IWDG, WWDG, USART2, I2C1 */
/* Here IWDG would be used over WWDG for Low power modes for STOPx mode*/

ResultStatus RCC_SetPeripheralClk_APB1ENR1(MCU_RCC_APB1Reg1Peripherals_t peripheralPos, FunctionalState state)
{
	// APB1 has ENR1 and ENR2. LPTIM2 is the only peripheral in ENR2
	if(peripheralPos >= MCU_RCC_REGISTER_SIZE)
			return STATUS_ERROR;

	if(state==ENABLE)
		RCC_NS->APB1ENR1 |= (1U << peripheralPos);
	else if(state==DISABLE)
		RCC_NS->APB1ENR1 &= ~(1U << peripheralPos);
	return STATUS_OK;
}

ResultStatus RCC_ResetPeripheralClk_APB1RSTR1(MCU_RCC_APB1Reg1Peripherals_t peripheralPos)
{
	if(peripheralPos >= MCU_RCC_REGISTER_SIZE)
		return STATUS_ERROR;

	RCC_NS->APB1RSTR1 |= (1U << peripheralPos);
	RCC_NS->APB1RSTR1 &= ~(1U << peripheralPos);

	return STATUS_OK;
}

/* APB1ENR2 peripherals - lptim2 */
ResultStatus RCC_SetPeripheralClk_APB1ENR2(MCU_RCC_APB1Reg2Peripherals_t peripheralPos, FunctionalState state)
{
	// APB1 has ENR1 and ENR2. LPTIM2 is the only peripheral in ENR2
	if(peripheralPos >= MCU_RCC_REGISTER_SIZE)
			return STATUS_ERROR;

	if(state==ENABLE)
		RCC_NS->APB1ENR2 |= (1U << peripheralPos);
	else if(state==DISABLE)
		RCC_NS->APB1ENR2 &= ~(1U << peripheralPos);
	return STATUS_OK;
}

ResultStatus RCC_ResetPeripheralClk_APB1RSTR2(MCU_RCC_APB1Reg2Peripherals_t peripheralPos)
{
	if(peripheralPos >= MCU_RCC_REGISTER_SIZE)
		return STATUS_ERROR;

	RCC_NS->APB1RSTR2 |= (1U << peripheralPos);
	RCC_NS->APB1RSTR2 &= ~(1U << peripheralPos);

	return STATUS_OK;
}

/* APB2 peripherals - USART1 */
ResultStatus RCC_SetPeripheralClk_APB2(MCU_RCC_APB2Peripherals_t peripheralPos, FunctionalState state)
{
	if(peripheralPos >= MCU_RCC_REGISTER_SIZE)
		return STATUS_ERROR;

	if(state==ENABLE)
		RCC_NS->APB2ENR |= (1U << peripheralPos);
	else if(state==DISABLE)
		RCC_NS->APB2ENR &= ~(1U << peripheralPos);
	return STATUS_OK;
}
ResultStatus RCC_ResetPeripheralClk_APB2(MCU_RCC_APB2Peripherals_t peripheralPos)
{
	if(peripheralPos >= MCU_RCC_REGISTER_SIZE)
		return STATUS_ERROR;

	RCC_NS->APB2RSTR |= (1U << peripheralPos);
	RCC_NS->APB2RSTR &= ~(1U << peripheralPos);
	return STATUS_OK;
}

/* APB7 peripherals - I2C3 */
ResultStatus RCC_SetPeripheralClk_APB7(MCU_RCC_APB7Peripherals_t peripheralPos, FunctionalState state)
{
	if(peripheralPos >= MCU_RCC_REGISTER_SIZE)
		return STATUS_ERROR;

	if(state==ENABLE)
		RCC_NS->APB7ENR |= (1U << peripheralPos);
	else if(state==DISABLE)
		RCC_NS->APB7ENR &= ~(1U << peripheralPos);
	return STATUS_OK;

}
ResultStatus RCC_ResetPeripheralClk_APB7(MCU_RCC_APB7Peripherals_t peripheralPos)
{
	if(peripheralPos >= MCU_RCC_REGISTER_SIZE)
		return STATUS_ERROR;

	RCC_NS->APB7RSTR |= (1U << peripheralPos);
	RCC_NS->APB7RSTR &= ~(1U << peripheralPos);
	return STATUS_OK;
}
