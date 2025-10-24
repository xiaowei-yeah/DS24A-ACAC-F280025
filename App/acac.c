/*
* File: 	acac.c
* Date: 	2025Äê10ÔÂ24ÈÕ
* Author: 	jinjiale

* Description: 	
* Version: 		
*/
//------------------------------------------Include----------------------------------------

#include "projectall.h"
#include "ctrl.h"

//-------------------------------------------Macro-----------------------------------------

//------------------------------------Function declaration---------------------------------

//--------------------------------------Struct And Type------------------------------------

typedef struct {

    float       inputVolt;
    float       inputCurr;
    float       ouputVolt;
    float       ouputCurr;

    float       targetVolt;
    float       targetCurr;


//    SPLL_1ph_SOGI_F             spll;
    ctrl_2p2z_TyprDef           ctrlPR;
    ctrl_pi_TyprDef     ctrlPI;
}acac_TypeDef;

//-------------------------------------------Value-----------------------------------------

//------------------------------------Function definition----------------------------------

/****************************************************************
* Function: 
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/





//--------------------------------------end of this file-----------------------------------
