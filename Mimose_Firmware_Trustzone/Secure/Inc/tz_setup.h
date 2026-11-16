#ifndef TZ_SETUP_H
#define TZ_SETUP_H

#include "stm32wbaxx.h"
#include <arm_cmse.h>

void TZ_setupSecureSection(void);
void TZ_jumpToNonSecure(void) __attribute__((noreturn));


#endif
