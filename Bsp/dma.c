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

#pragma DATA_SECTION(AdcA_Destination_buff,"ramgs0");
static uint16_t AdcA_Destination_buff[32];

const void *Dma_SourceAddr = (uint16_t *)&AdcaResultRegs.ADCRESULT0;
const void *Dma_DestinationAddr = AdcA_Destination_buff;


//--------------------------------Function definition----------------------------------

/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/







//---------------------------------------------end of this file----------------------------------------------
