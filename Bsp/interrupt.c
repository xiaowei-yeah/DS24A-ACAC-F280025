/*
* File:     samp.c
* Date:     2025Äê10ÔÂ14ÈÕ
* Author:   jin

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
* Function:     ISR
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
__interrupt void INT_ADC_C_1_ISR(void)
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

float Duty = 0;
float Am = 0;
float wt = 0;
float step = 2*3.1415926/20000*50;
uint16_t OpenloopFlg = 0;
uint16_t firstOnflg = 0;

float ADCBuff[400];

__interrupt void INT_DMA_C_ISR(void)
{
    if(OpenloopFlg)
    {
        if(firstOnflg == 1)
        {
            pwm_allon();
            firstOnflg = 0;
        }
        Duty = (Am * sinf(wt))*0.5+0.5;
        wt += step;
        if(wt >= 3.1415926*2)
        {
            wt = wt - 3.1415926*2;
        }
        pwm_setduty_a(0);
        pwm_setduty_b(Duty);
    }
    else
    {
        firstOnflg = 1;
        pwm_alloff();
    }
    samp_UpdateAll();
    static uint16_t cnt = 0;
    if(cnt>=400)cnt=0;
    ADCBuff[cnt] = samp_getReal(eVolt_OutA);
    cnt++;

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}


__interrupt void INT_ePWM_Ap_TZ_ISR(void)
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP2);
}

//---------------------------------------------end of this file----------------------------------------------
