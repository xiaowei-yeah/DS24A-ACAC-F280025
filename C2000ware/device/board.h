/*
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************

//
// EPWM2 -> ePWM_Ap Pinmux
//
//
// EPWM2_A - GPIO Settings
//
#define GPIO_PIN_EPWM2_A 2
#define ePWM_Ap_EPWMA_GPIO 2
#define ePWM_Ap_EPWMA_PIN_CONFIG GPIO_2_EPWM2_A
//
// EPWM2_B - GPIO Settings
//
#define GPIO_PIN_EPWM2_B 3
#define ePWM_Ap_EPWMB_GPIO 3
#define ePWM_Ap_EPWMB_PIN_CONFIG GPIO_3_EPWM2_B
//
// GPIO5 - GPIO Settings
//
#define LED1_GPIO_GPIO_PIN_CONFIG GPIO_5_GPIO5
//
// GPIO45 - GPIO Settings
//
#define LED2_GPIO_GPIO_PIN_CONFIG GPIO_45_GPIO45

//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
#define CpuTimer0_BASE CPUTIMER0_BASE
void CpuTimer0_init();

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
#define ePWM_Ap_BASE EPWM2_BASE
#define ePWM_Ap_TBPRD 2500
#define ePWM_Ap_COUNTER_MODE EPWM_COUNTER_MODE_UP_DOWN
#define ePWM_Ap_TBPHS 0
#define ePWM_Ap_CMPA 1000
#define ePWM_Ap_CMPB 0
#define ePWM_Ap_CMPC 0
#define ePWM_Ap_CMPD 0
#define ePWM_Ap_DBRED 200
#define ePWM_Ap_DBFED 200
#define ePWM_Ap_TZA_ACTION EPWM_TZ_ACTION_LOW
#define ePWM_Ap_TZB_ACTION EPWM_TZ_ACTION_LOW
#define ePWM_Ap_OSHT_SOURCES EPWM_TZ_SIGNAL_DCAEVT1
#define ePWM_Ap_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define LED1_GPIO 5
void LED1_GPIO_init();
#define LED2_GPIO 45
void LED2_GPIO_init();

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	CPUTIMER_init();
void	EPWM_init();
void	GPIO_init();
void	SYNC_init();
void	PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
