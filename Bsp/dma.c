/*
* File:     dma.c
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

#pragma DATA_SECTION(AdcC_Destination_buff,"ramgs0");
static uint16_t AdcC_Destination_buff[32];

const void *Dma_SourceAddr = (uint16_t *)&AdcaResultRegs.ADCRESULT0;
const void *Dma_DestinationAddr = AdcC_Destination_buff;


//--------------------------------Function definition----------------------------------

/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
uint16_t dma_getBuff(uint16_t p)
{
    return AdcC_Destination_buff[p];
}






//---------------------------------------------end of this file----------------------------------------------
