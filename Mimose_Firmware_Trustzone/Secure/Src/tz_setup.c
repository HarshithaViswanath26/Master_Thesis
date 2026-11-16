#include "stdbool.h"
#include "tz_setup.h"

#define FULL_ACCESS_PRIVILEGE 	0x3U
#define SCB_NS_CPACR_CP10_Pos	20U
#define SCB_NS_CPACR_CP11_Pos	22U

#define NS_FLASH				0U			// Non Secure Flash
#define NSC_REGION				1U			// Non Secure Callables
#define NS_RAM					2U			// Non Secure RAM
#define NS_PERIPHERALS			3U			// Non Secure Peripherals

#define NS_FLASH_START_ADDR						0x08080000U   // Non Secure Flash
#define NS_FLASH_END_ADDR						0x080FFFFFU

#define NSC_REGION_START_ADDR					0x0C07E000U   // Non Secure Callables
#define NSC_REGION_END_ADDR						0x0C07FFFFU

#define NS_RAM_START_ADDR						0x20010000U   // Non Secure RAM
#define NS_RAM_END_ADDR							0x2001FFFFU

#define NS_PERIPHERALS_START_ADDR				0x40000000U   // Non Secure Peripherals
#define NS_PERIPHERALS_END_ADDR					0x4FFFFFFFU

#define SAU_NSC_DISABLE			0U
#define SAU_NSC_ENABLE			1U

static void TZ_FPUSetup(void);
static void TZ_SAUSetup(void);
static void TZ_SRAM2Setup(void);
static void TZ_PeripheralSetup(void);
static void TZ_InterruptSetup(void);

static void TZ_SAUConfig(uint8_t regNum, uint32_t startAddr, uint32_t endAddr, bool NSCEn);
static void TZ_SAUSetup(void);

static void TZ_FPUSetup(void)
{
	// Release co-processors 10/11 mainly used for FPU to non secure from secure side
	// set CP10 & CP11 bits
	SCB->NSACR |= (SCB_NSACR_CP10_Msk | SCB_NSACR_CP11_Msk);

	// Give FPU processors full access privilege both on secure and non secure sides
	// Non secure
	// Set 11 for full access privilege
	SCB_NS->CPACR |= (FULL_ACCESS_PRIVILEGE << SCB_NS_CPACR_CP10_Pos); // CP10
	SCB_NS->CPACR |= (FULL_ACCESS_PRIVILEGE << SCB_NS_CPACR_CP11_Pos); // CP11

	// Secure
	// Set 11 for full access privilege
	SCB->CPACR |= (FULL_ACCESS_PRIVILEGE << SCB_NS_CPACR_CP10_Pos); // CP10
	SCB->CPACR |= (FULL_ACCESS_PRIVILEGE << SCB_NS_CPACR_CP11_Pos); // CP11

	__DSB(); // data sync barrier
	__ISB(); // instruction sync barrier
}

static void TZ_SAUConfig(uint8_t regNum, uint32_t startAddr, uint32_t endAddr, bool NSCEn)
{
	// set the region
	SAU->RNR = (regNum << SAU_RNR_REGION_Pos);

	// set the start addr of the region
	SAU->RBAR = (startAddr & SAU_RBAR_BADDR_Msk);

	// if non secure callable should be accounted for the region enable that also
	if(NSCEn)
		SAU->RLAR = (endAddr & SAU_RLAR_LADDR_Msk) | (SAU_RLAR_NSC_Msk) | (SAU_RLAR_ENABLE_Msk);
	else
		SAU->RLAR = (endAddr & SAU_RLAR_LADDR_Msk) | (SAU_RLAR_ENABLE_Msk);
}

static void TZ_SAUSetup(void)
{
	TZ_SAUConfig(NS_FLASH, NS_FLASH_START_ADDR, NS_FLASH_END_ADDR, false);
	TZ_SAUConfig(NSC_REGION, NSC_REGION_START_ADDR, NSC_REGION_END_ADDR, true);
	TZ_SAUConfig(NS_RAM, NS_RAM_START_ADDR, NS_RAM_END_ADDR, false);
	TZ_SAUConfig(NS_PERIPHERALS, NS_PERIPHERALS_START_ADDR, NS_PERIPHERALS_END_ADDR, false);

	TZ_SAU_Enable();

	__DSB();
	__ISB();
}

static void TZ_SRAM2Setup(void)
{
	// Enable the clock for GTGC1
	RCC_S->AHB1ENR |= RCC_AHB1ENR_GTZC1EN;

	// set 0 for all the bits that account for 64KB (total 128 blocks of 512B)
	// this sets the 64KB of SRAM2 to be non secure
	for(uint8_t i = 0; i < 4; i++)
	{
		GTZC_MPCBB2_S->SECCFGR[i] = 0x00000000U;
	}

	// leave the GTZC peripheral clock on
	// unverified secure SRAM2 access will be blocked
	__DSB();
	__ISB();
}

static void TZ_PeripheralSetup(void)
{
	// Enable RCC clocks for GPIOA_S, GPIOB_S, GPIOC_S
	RCC_S->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN);

	// Release these peripherals to the non secure side via SECCFGR
	GPIOA_S->SECCFGR = 0x00U;
	GPIOB_S->SECCFGR = 0x00U;
	GPIOC_S->SECCFGR = 0x00U;

	// Disable the clock - power saving
	RCC_S->AHB2ENR &= ~(RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN);

	__DSB();
	__ISB();
}

static void TZ_InterruptSetup(void)
{
	// Release all the interrupts
	// There are 71 interrupts in total for stm32wba55cg
	uint32_t interrGrp = (SCnSCB->ICTR & SCnSCB_ICTR_INTLINESNUM_Msk);
	for(uint32_t i = 0; i < interrGrp+1; i++)
	{
		NVIC->ITNS[i] = 0xFFFFFFFFU;
	}

	__DSB();
	__ISB();
}

__attribute__((noreturn)) void TZ_jumpToNonSecure(void)
{
	uint32_t resetHandlerAddr_NS = (NS_FLASH_START_ADDR + 4U);

	SCB_NS->VTOR = NS_FLASH_START_ADDR;

	uint32_t SPVal_NS = (*(volatile uint32_t*)(NS_FLASH_START_ADDR));
	__TZ_set_MSP_NS(SPVal_NS);

	uint32_t resetHandlerVal_NS = (*(volatile uint32_t*)(resetHandlerAddr_NS));
	typedef void (*resetHandler_NS)(void) __attribute__((cmse_nonsecure_call));
	resetHandler_NS callAddr = cmse_nsfptr_create((resetHandler_NS)resetHandlerVal_NS);
	callAddr();
}

void TZ_setupSecureSection(void)
{
	TZ_FPUSetup();
	TZ_SAUSetup();
	TZ_SRAM2Setup();
	TZ_PeripheralSetup();
	TZ_InterruptSetup();

}
