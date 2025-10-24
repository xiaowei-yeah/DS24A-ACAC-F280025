/*
* File: 	ctrl.h
* Date: 	2025Äê10ÔÂ24ÈÕ
* Author: 	jinjiale

* Description: 	
* Version: 		
*/
#ifndef APP_CTRL_H_
#define APP_CTRL_H_

//------------------------------------------Include----------------------------------------

//-------------------------------------------Macro-----------------------------------------

//--------------------------------------Struct And Type------------------------------------

/****************************************************************
* Description:
****************************************************************/
typedef struct ctrl_pi_TyprDef{

    float kp;
    float ki;
    float max;
    float min;
    float ts;

    float ref;
    float fbk;
    float vi;
    float out;


} ctrl_pi_TyprDef;


/****************************************************************
* Description:
****************************************************************/
typedef struct ctrl_2p2z_TyprDef{

    float b2;
    float b1;
    float b0;
    float a2;
    float a1;
    float max;
    float min;

    float ref;
    float fbk;
    float out;

} ctrl_2p2z_TyprDef;


/****************************************************************
* Description:
****************************************************************/
typedef struct ctrl_sogi_TyprDef{

    float ts;
    float w;
    float kp;
    float ui;
    float uo_a;
    float uo_b;
    float sum1;


} ctrl_sogi_TyprDef;


/****************************************************************
* Description:
****************************************************************/
typedef struct ctrl_spll_TyprDef{

    float               ui;
    float               wt;
    float               w;
    float               ud;
    float               uq;
    ctrl_sogi_TyprDef   sogi;
    ctrl_pi_TyprDef     pi;

} ctrl_spll_TyprDef;



//------------------------------------Function declaration---------------------------------


#endif /* APP_CTRL_H_ */

//--------------------------------------end of this file-----------------------------------
