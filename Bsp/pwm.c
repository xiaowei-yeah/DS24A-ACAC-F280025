/*
* File: 	pwm.c
* Date: 	2025Äê10ÔÂ14ÈÕ
* Author: 	jinjiale

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
    EPWM_forceTripZoneEvent(ePWM_Ap_BASE,EPWM_TZ_FORCE_EVENT_DCAEVT1);
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
    EPWM_clearTripZoneFlag(ePWM_Ap_BASE,EPWM_TZ_FORCE_EVENT_DCAEVT1);
    EPWM_clearTripZoneFlag(ePWM_Ap_BASE,EPWM_TZ_FORCE_EVENT_OST);
}

/****************************************************************
* Function:     pwm_setduty_a
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void pwm_setduty_a(uint16_t duty)
{
    EPWM_setCounterCompareValue(ePWM_Ap_BASE,EPWM_COUNTER_COMPARE_A,duty);
}



//---------------------------------------------end of this file----------------------------------------------
