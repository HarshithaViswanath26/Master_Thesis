#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>

#include "stm32wbaxx.h"


/*==================================================Peripherals used in Schematics=======================================================*/
/*
 * The entire sensor code sits on the non secure code.
 * There are Non Secure peripheral address that only work if the permission is set from the secure side.
 * The access is given in the Secure code*/

/*GPIO Pins*/
#define PIN_0		0
#define PIN_1		1
#define PIN_2		2
#define PIN_3		3
#define PIN_4		4
#define PIN_5		5
#define PIN_6		6
#define PIN_7		7
#define PIN_8		8
#define PIN_9		9
#define PIN_10		10
#define PIN_11		11
#define PIN_12		12
#define PIN_13		13
#define PIN_14		14
#define PIN_15		15


/* Alternate functionalities for a GPIO pin*/
#define AF0			0
#define AF1			1
#define AF2			2
#define AF3			3
#define AF4			4
#define AF5			5
#define AF6			6
#define AF7			7
#define AF8			8
#define AF9			9
#define AF10		10
#define AF11		11
#define AF12		12
#define AF13		13
#define AF14		14
#define AF15		15


typedef enum
{
	InputMode = 0,
	OutputMode = 1,
	AlternateFunctionMode = 2,
	AnalogMode = 3,

}GPIO_ModeTypes_t;

typedef enum
{
	PushPull = 0,
	OpenDrain = 1,

}GPIO_OutputTypes_t;

typedef enum
{
	LowSpeed = 0,
	MediumSpeed = 1,
	HighSpeed = 2,
	SpeedReserved = 3

}GPIO_OutputSpeed_t;

typedef enum
{
	NoPuPd = 0,
	PullUp = 1,
	PullDown = 2,
	PupdReserved = 3,

}GPIO_PuPdTypes_t;

typedef enum
{
	PinLow = 0,
	PinHigh = !PinLow
}GPIO_PinStates_t;

typedef struct
{
	uint8_t pinNum;
	GPIO_ModeTypes_t mode;
	GPIO_OutputSpeed_t outputSpeed;
	GPIO_OutputTypes_t outputType;
	GPIO_PuPdTypes_t puPdType;
	uint8_t pinAFType;
}GPIO_PinConfig_t;

typedef struct
{
	GPIO_TypeDef* port;
	GPIO_PinConfig_t pin;

}GPIO_Handle_t;

void GPIO_RCCClk_Enable(GPIO_TypeDef* port, FunctionalState state);
void GPIO_Init(GPIO_Handle_t* pHandle);
void GPIO_WriteReg(GPIO_TypeDef* port, uint8_t pinNum, BitValue val);
uint8_t GPIO_ReadIDR(GPIO_TypeDef* port, uint8_t pinNum);
uint8_t GPIO_ReadODR(GPIO_TypeDef* port, uint8_t pinNum);

void GPIO_LEDToggle(GPIO_TypeDef* port, uint8_t pinNum);
void GPIO_LEDOn(GPIO_TypeDef* port, uint8_t pinNum);
void GPIO_LEDOff(GPIO_TypeDef* port, uint8_t pinNum);




#endif
