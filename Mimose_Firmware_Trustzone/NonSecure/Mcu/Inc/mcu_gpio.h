#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>

#include "stm32wbaxx.h"


/*==================================================Peripherals used in Schematics=======================================================*/
/*
 * The entire sensor code sits on the non secure code.
 * There are Non Secure peripheral address that only work if the permission is set from the secure side.
 * The access is given in the Secure code*/

/*GPIO Ports*/
/*#define GPIO_A 		GPIOA_NS
#define GPIO_B		GPIOB_NS
#define GPIO_C		GPIOC_NS
*/

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
	Reserved = 3

}GPIO_OutputSpeed_t;

typedef enum
{
	NoPullupPulldown = 0,
	PullUp = 1,
	PullDown = 2,
	Reserved = 3,

}GPIO_PuPdTypes_t;

void GPIO_RCCClk_Enable(GPIO_TypeDef* port, FunctionalState pinNum);
void GPIO_Init()
#endif
