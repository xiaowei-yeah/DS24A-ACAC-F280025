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

#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules. 
// Call this function in your application if you wish to do all module 
// initialization.
// If you wish to not use some of the initializations, instead of the 
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
	EALLOW;

	PinMux_init();
	SYNC_init();
	CPUTIMER_init();
	EPWM_init();
	GPIO_init();

	EDIS;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
	//
	// PinMux for modules assigned to CPU1
	//
	
	//
	// EPWM2 -> ePWM_Ap Pinmux
	//
	GPIO_setPinConfig(ePWM_Ap_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(ePWM_Ap_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(ePWM_Ap_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(ePWM_Ap_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(ePWM_Ap_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(ePWM_Ap_EPWMB_GPIO, GPIO_QUAL_SYNC);

	// GPIO5 -> LED1_GPIO Pinmux
	GPIO_setPinConfig(GPIO_5_GPIO5);
	// GPIO45 -> LED2_GPIO Pinmux
	GPIO_setPinConfig(GPIO_45_GPIO45);

}


//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
void CPUTIMER_init(){
	CpuTimer0_init();
}

void CpuTimer0_init(){
	CPUTimer_setEmulationMode(CpuTimer0_BASE, CPUTIMER_EMULATIONMODE_RUNFREE);
	CPUTimer_setPreScaler(CpuTimer0_BASE, 99U);
	CPUTimer_setPeriod(CpuTimer0_BASE, 999U);
	CPUTimer_disableInterrupt(CpuTimer0_BASE);
	CPUTimer_stopTimer(CpuTimer0_BASE);

	CPUTimer_reloadTimerCounter(CpuTimer0_BASE);
	CPUTimer_startTimer(CpuTimer0_BASE);
}

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
void EPWM_init(){
    EPWM_setClockPrescaler(ePWM_Ap_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(ePWM_Ap_BASE, 2500);	
    EPWM_setTimeBaseCounter(ePWM_Ap_BASE, 0);	
    EPWM_setTimeBaseCounterMode(ePWM_Ap_BASE, EPWM_COUNTER_MODE_UP_DOWN);	
    EPWM_setCountModeAfterSync(ePWM_Ap_BASE, EPWM_COUNT_MODE_UP_AFTER_SYNC);	
    EPWM_disablePhaseShiftLoad(ePWM_Ap_BASE);	
    EPWM_setPhaseShift(ePWM_Ap_BASE, 0);	
    EPWM_setCounterCompareValue(ePWM_Ap_BASE, EPWM_COUNTER_COMPARE_A, 1000);	
    EPWM_setCounterCompareShadowLoadMode(ePWM_Ap_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(ePWM_Ap_BASE, EPWM_COUNTER_COMPARE_B, 0);	
    EPWM_setCounterCompareShadowLoadMode(ePWM_Ap_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_disableActionQualifierShadowLoadMode(ePWM_Ap_BASE, EPWM_ACTION_QUALIFIER_A);	
    EPWM_setActionQualifierShadowLoadMode(ePWM_Ap_BASE, EPWM_ACTION_QUALIFIER_A, EPWM_AQ_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_disableActionQualifierShadowLoadMode(ePWM_Ap_BASE, EPWM_ACTION_QUALIFIER_B);	
    EPWM_setActionQualifierShadowLoadMode(ePWM_Ap_BASE, EPWM_ACTION_QUALIFIER_B, EPWM_AQ_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setDeadBandDelayPolarity(ePWM_Ap_BASE, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);	
    EPWM_setDeadBandDelayMode(ePWM_Ap_BASE, EPWM_DB_RED, true);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(ePWM_Ap_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(ePWM_Ap_BASE);	
    EPWM_setRisingEdgeDelayCount(ePWM_Ap_BASE, 200);	
    EPWM_setDeadBandDelayMode(ePWM_Ap_BASE, EPWM_DB_FED, true);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(ePWM_Ap_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(ePWM_Ap_BASE);	
    EPWM_setFallingEdgeDelayCount(ePWM_Ap_BASE, 200);	
    EPWM_setTripZoneAction(ePWM_Ap_BASE, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(ePWM_Ap_BASE, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_LOW);	
    EPWM_enableTripZoneSignals(ePWM_Ap_BASE, EPWM_TZ_SIGNAL_DCAEVT1);	
    EPWM_enableADCTrigger(ePWM_Ap_BASE, EPWM_SOC_A);	
    EPWM_setADCTriggerSource(ePWM_Ap_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO_OR_PERIOD);	
    EPWM_enableADCTrigger(ePWM_Ap_BASE, EPWM_SOC_B);	
    EPWM_setADCTriggerSource(ePWM_Ap_BASE, EPWM_SOC_B, EPWM_SOC_TBCTR_ZERO);	
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init(){
	LED1_GPIO_init();
	LED2_GPIO_init();
}

void LED1_GPIO_init(){
	GPIO_setPadConfig(LED1_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(LED1_GPIO, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(LED1_GPIO, GPIO_DIR_MODE_OUT);
}
void LED2_GPIO_init(){
	GPIO_setPadConfig(LED2_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(LED2_GPIO, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(LED2_GPIO, GPIO_DIR_MODE_OUT);
}

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************
void SYNC_init(){
	SysCtl_setSyncOutputConfig(SYSCTL_SYNC_OUT_SRC_EPWM1SYNCOUT);
	//
	// SOCA
	//
	SysCtl_enableExtADCSOCSource(0);
	//
	// SOCB
	//
	SysCtl_enableExtADCSOCSource(0);
}
