/*
* File: 	ctrl.c
* Date: 	2025Äê10ÔÂ24ÈÕ
* Author: 	jinjiale

* Description: 	
* Version: 		
*/
//------------------------------------------Include----------------------------------------

#include "ctrl.h"

//-------------------------------------------Macro-----------------------------------------

//------------------------------------Function declaration---------------------------------

void ctrl_sogi_Init(ctrl_sogi_TyprDef *self, float kp ,float ts,float wn);
void ctrl_sogi_Run(ctrl_sogi_TyprDef *self, float ui);

void ctrl_spll_Init(ctrl_spll_TyprDef *self, float ts, float wn);
void ctrl_spll_Run(ctrl_spll_TyprDef *self, float ui);

void ctrl_pi_Init(ctrl_pi_TyprDef *self, float kp,float ki,float max,float min,float ts);
float ctrl_pi_Run(ctrl_pi_TyprDef *self, float ref,float fbk);

void ctrl_2p2z_Init(ctrl_2p2z_TyprDef *self, float b0,float b1,float b2,float a1,float a2,float max,float min);
float ctrl_2p2z_Run(ctrl_2p2z_TyprDef *self, float ref,float fbk);

//--------------------------------------Struct And Type------------------------------------

//-------------------------------------------Value-----------------------------------------

ctrl_spll_TyprDef spll;

//------------------------------------Function definition----------------------------------

/****************************************************************
* Function: 
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void ctrl_sogi_Init(ctrl_sogi_TyprDef *self, float kp ,float ts,float wn)
{
    self->kp = kp;
    self->ts = ts;
    self->w = wn;
    self->ui = 0;
    self->uo_a = 0;
    self->uo_b = 0;
    self->sum1 = 0;
}
/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void ctrl_sogi_Run(ctrl_sogi_TyprDef *self, float ui)
{
    self->ui = ui;
    self->uo_a += ((self->ui - self->uo_a) * self->kp - self->uo_b) * self->w * self->ts;
    self->sum1 += self->uo_a * self->ts;
    self->uo_b = self->sum1 * self->w;
}

/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void ctrl_spll_Init(ctrl_spll_TyprDef *self, float ts, float wn)
{
    self->ui = 0;
    self->wt = 0;

    ctrl_sogi_Init(&self->sogi,0.5,ts,wn);
    ctrl_pi_Init(&self->pi,1,0,1,-1,ts);
}
/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void ctrl_spll_Run(ctrl_spll_TyprDef *self, float ui)
{
    ctrl_sogi_Run(&self->sogi,ui);

}
/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void ctrl_pi_Init(ctrl_pi_TyprDef *self, float kp,float ki,float max,float min,float ts)
{
    self->ki = ki;
    self->kp = kp;
    self->max = max;
    self->min = min;
    self->ts = ts;
    self->fbk = 0;
    self->ref = 0;
    self->vi = 0;
    self->out = 0;
}
/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
float ctrl_pi_Run(ctrl_pi_TyprDef *self, float ref,float fbk)
{
    self->ref = ref;
    self->fbk = fbk;
    float err = self->ref - self->fbk;
    self->vi = err * self->ki * self->ts;
    float uo = err * self->kp + self->vi;

    uo = uo > self->max ? self->max : uo;
    uo = uo < self->min ? self->min : uo;
    self->out = uo;

    return self->out;
}

/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void ctrl_2p2z_Init(ctrl_2p2z_TyprDef *self, float b0,float b1,float b2,float a1,float a2,float max,float min)
{
    self->b0 = b0;
    self->b1 = b1;
    self->b2 = b2;
    self->a1 = a1;
    self->a2 = a2;
    self->max = max;
    self->min = min;
    self->fbk = 0;
    self->ref = 0;
    self->out = 0;
}
/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
float ctrl_2p2z_Run(ctrl_2p2z_TyprDef *self, float ref,float fbk)
{
    return self->out;
}



//--------------------------------------end of this file-----------------------------------
