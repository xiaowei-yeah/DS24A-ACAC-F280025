/*
* File: 	systick.c
* Date: 	2025Äê9ÔÂ29ÈÕ
* Author: 	jinjiale

* Description: 	
* Version: 		
*/

//------------------------------------------Include----------------------------------------

#include "projectall.h"

//------------------------------------Function declaration---------------------------------

//--------------------------------------Value declaration----------------------------------

//--------------------------------------Value definition-----------------------------------

static uint32_t tick;

//------------------------------------Function definition----------------------------------

/****************************************************************
* Function:     tick_Update
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void tick_Update(void)
 {
     if(CPUTimer_getTimerOverflowStatus(CpuTimer0_BASE) == true)
      {
         CPUTimer_clearOverflowFlag(CpuTimer0_BASE);
         tick++;
      }
 }
/****************************************************************
* Function:     tick_Get
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
uint32_t tick_Get()
{
    return tick;
}

//---------------------------------------------end of this file----------------------------------------------
