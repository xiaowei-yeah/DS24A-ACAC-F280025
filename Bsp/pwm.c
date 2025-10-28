/*
* File: 	pwm.c
* Date: 	2025Äê10ÔÂ14ÈÕ
* Author: 	jin

* Description: 	
* Version: 		
*/

//--------------------------------------include-----------------------------------------

#include "projectall.h"

//---------------------------------------Macro-----------------------------------------

//--------------------------------Function declaration---------------------------------

//----------------------------------Value declaration----------------------------------

//----------------------------------Value definition-----------------------------------

//--------------------------------Function definition----------------------------------

/****************************************************************
* Function: 	pwm_alloff
* Description:
* Input: 
* Output: None
* Return: None
****************************************************************/
void pwm_alloff()
{
    GPIO_writePin(PWM_EN, 1);
    EPWM_forceTripZoneEvent(ePWM_Ap_BASE,EPWM_TZ_FORCE_EVENT_DCAEVT1);
    EPWM_forceTripZoneEvent(ePWM_Bp_BASE,EPWM_TZ_FORCE_EVENT_DCAEVT1);
}

/****************************************************************
* Function:     pwm_alloff
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void pwm_allon()
{
    GPIO_writePin(PWM_EN, 0);
    EPWM_clearTripZoneFlag(ePWM_Ap_BASE,EPWM_TZ_FORCE_EVENT_DCAEVT1);
    EPWM_clearTripZoneFlag(ePWM_Ap_BASE,EPWM_TZ_FORCE_EVENT_OST);

    EPWM_clearTripZoneFlag(ePWM_Bp_BASE,EPWM_TZ_FORCE_EVENT_DCAEVT1);
    EPWM_clearTripZoneFlag(ePWM_Bp_BASE,EPWM_TZ_FORCE_EVENT_OST);
}

/****************************************************************
* Function:     pwm_setduty_a
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void pwm_setduty_a(float duty)
{
    duty = duty > 0 ? duty : 0;
    duty = duty < 0.999f ? duty : 0.999f;
    EPWM_setCounterCompareValue(ePWM_Ap_BASE,EPWM_COUNTER_COMPARE_A,duty * 2500);
}
void pwm_setduty_b(float duty)
{
    duty = duty > 0 ? duty : 0;
    duty = duty < 0.999f ? duty : 0.999f;
    EPWM_setCounterCompareValue(ePWM_Bp_BASE,EPWM_COUNTER_COMPARE_A,duty * 2500);
}



//---------------------------------------------end of this file----------------------------------------------
