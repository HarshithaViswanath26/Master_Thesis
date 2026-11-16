#include "mcu_gpio.h"
#include "mcu_rcc.h"

#define LED_ON		1U


void GPIO_RCCClk_Enable(GPIO_TypeDef* port, FunctionalState state)
{
	uint8_t bitPos;
	if(state == ENABLE)
	{
		if(port==GPIOA_NS)
			bitPos = GpioA;
		else if(port==GPIOB_NS)
			bitPos = GpioB;
		else if(port==GPIOC_NS)
			bitPos = GpioC;
		else
			return;

		RCC_SetPeripheralClk_AHB2(bitPos, ENABLE);
	}
}

void GPIO_Init(GPIO_Handle_t* pHandle)
{
	// mode in MODER
	// clear the default reset state and then set the bit
	pHandle->port->MODER &= ~(0x3U << (2*pHandle->pin.pinNum)); //1U is not the mask here
	pHandle->port->MODER |= (pHandle->pin.mode << (2*pHandle->pin.pinNum));

	// output type in OTYPER
	pHandle->port->OTYPER |= (pHandle->pin.outputType << pHandle->pin.pinNum);

	// output speed in OSPEEDR
	pHandle->port->OSPEEDR |= (pHandle->pin.outputSpeed << (2*pHandle->pin.pinNum));

	// resistor type - pullup/pulldown in PUPDR
	pHandle->port->PUPDR |= (pHandle->pin.puPdType << (2*pHandle->pin.pinNum));

	// AFx in AFRL or AFRH
	uint8_t regPos, bitPos;

	regPos = pHandle->pin.pinNum / 8;
	bitPos = (4*(pHandle->pin.pinNum % 8));

	pHandle->port->AFR[regPos] |= (pHandle->pin.pinAFType << bitPos);
}

void GPIO_WriteReg(GPIO_TypeDef* port, uint8_t pinNum, BitValue val)
{
	port->ODR |= (val << pinNum);
}

uint8_t GPIO_ReadIDR(GPIO_TypeDef* port, uint8_t pinNum)
{
	return ((port->IDR >> pinNum)&1U);
}

uint8_t GPIO_ReadODR(GPIO_TypeDef* port, uint8_t pinNum)
{
	return ((port->ODR >> pinNum)&1U);
}

void GPIO_LEDOn(GPIO_TypeDef* port, uint8_t pinNum)
{
	port->ODR |= (1U << pinNum);
}

void GPIO_LEDOff(GPIO_TypeDef* port, uint8_t pinNum)
{
	port->ODR &= ~(1U << pinNum);
}

void GPIO_LEDToggle(GPIO_TypeDef* port, uint8_t pinNum)
{
	port->ODR ^= (1U << pinNum);
}

