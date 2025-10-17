/*
* File:     samp.c
* Date:     2025��10��14��
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
__interrupt void INT_ADC_A_1_ISR(void)
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}


__interrupt void INT_DMA_A_ISR(void)
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}


__interrupt void INT_ePWM_Ap_TZ_ISR(void)
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP2);
}

//---------------------------------------------end of this file----------------------------------------------
