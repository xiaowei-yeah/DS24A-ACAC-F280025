/*
* File: 	ctrl.c
* Date: 	2025Äê10ÔÂ24ÈÕ
* Author: 	jinjiale

* Description: 	
* Version: 		
*/
//------------------------------------------Include----------------------------------------

#include "ctrl.h"
#include "math.h"

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
void ctrl_spll_Init(ctrl_spll_TyprDef *self, float ts, float wn)
{
    self->ui = 0;
    self->wt = 0;
    self->w = 0;
    self->wn = 314.15926f;
    self->ud = 0;
    self->uq = 0;
    ctrl_sogi_Init(&self->sogi,1,ts,wn);
    ctrl_pi_Init(&self->pi,2,60,1000,-1000,ts);
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

    self->ud = self->sogi.uo_a * cosf(self->wt) + self->sogi.uo_b * sinf(self->wt);
    self->uq = self->sogi.uo_b * cosf(self->wt) - self->sogi.uo_a * sinf(self->wt);

    ctrl_pi_Run(&self->pi,0,self->uq);

    self->w = self->wn + self->pi.out;
    self->wt += self->w * self->pi.ts;
    self->wt = self->wt >= 2*3.1415926f ? self->wt - 2*3.1415926f : self->wt;
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
    self->imin = min;
    self->fbk = 0;
    self->ref = 0;
    self->out = 0;
    self->err = 0;
    self->out1 = 0;
    self->err1 = 0;
    self->out2 = 0;
    self->err2 = 0;

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

    self->err = self->ref - self->fbk;
    self->out = (self->a2*self->out2) + (self->a1 *self->out1) + (self->b2 *self->err2)
                    + (self->b1 * self->err1) + (self->b0 * self->err);

    self->err2 = self->err1;
    self->err1 = self->err;

    self->out = (self->out < self->max) ? self->out : self->max;
    self->out = (self->out > self->imin) ? self->out : self->imin;

    self->out2 = self->out1;
    self->out1 = self->out;

    self->out = ((self->out > self->min) ? self->out : self->min);

    return self->out;
}



//--------------------------------------end of this file-----------------------------------
