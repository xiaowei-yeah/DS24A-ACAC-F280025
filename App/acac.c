/*
* File: 	acac.c
* Date: 	2025年10月24日
* Author: 	jinjiale

* Description: 	
* Version: 		
*/
//------------------------------------------Include----------------------------------------

#include "projectall.h"
#include "ctrl.h"

//-------------------------------------------Macro-----------------------------------------

#define mPi     (3.141592654f)
#define m2Pi    (6.283185308f)
#define mPi2    (1.570796327f)
#define mPi3    (1.047197551f)
#define mSqrt2  (1.414213562f)
#define m2Sqrt2 (2.828427125f)
#define mSqrt3  (1.732050808f)
#define m2Sqrt3 (3.464101615f)
#define m3Sqrt3 (5.196152423f)

//------------------------------------Function declaration---------------------------------

//--------------------------------------Struct And Type------------------------------------

typedef struct {

    float       inputVolt;
    float       inputCurr;
    float       ouputVolt;
    float       ouputCurr;

    float       targetVoltAm;
    float       targetCurrAm;

    float       targetVolt;
    float       targetCurr;

    float       wm;

    float       baseSin;

    float       wn;
    float       ts;

    enum en_dis_enum    en;
    enum en_dis_enum    iflg;
    enum en_dis_enum    vflg;

    ctrl_spll_TyprDef       spll;
//    ctrl_2p2z_TyprDef       ctrl_iPR;
    ctrl_pi_TyprDef         ctrl_iPI;
    ctrl_pi_TyprDef         ctrl_vPI;

}acac_TypeDef;

acac_TypeDef acac;

//-------------------------------------------Value-----------------------------------------

//------------------------------------Function definition----------------------------------

/****************************************************************
* Function: 
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void acac_init(acac_TypeDef *self)
{
    self->inputVolt = 0;
    self->inputCurr = 0;
    self->ouputVolt = 0;
    self->ouputCurr = 0;
    self->targetVolt = 0;
    self->targetCurr = 0;
    self->targetVoltAm = 0;
    self->targetCurrAm = 0;
    self->ts = (1.0f / 20000.0f);
    self->wn = (m2Pi * 50);
    self->wm = 0;
    self->baseSin = 0;

    self->en = eDisable;
    self->iflg = eDisable;
    self->vflg = eDisable;

    ctrl_spll_Init(&self->spll,self->ts,self->wn);
    ctrl_pi_Init(&self->ctrl_iPI,1,0,100,-100,self->ts);
    ctrl_pi_Init(&self->ctrl_vPI,1,0,100,-100,self->ts);

}
void acac_Init()
{
    acac_init(&acac);
}

/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void acac_func(acac_TypeDef *self)
{
    // 锁相
    ctrl_spll_Run(&self->spll,self->inputVolt);

    self->baseSin = -cosf(self->spll.wt);

    static uint16_t first;

    if(self->en)
    {
        if(first == 1)
        {
            first = 0;
            pwm_allon();
        }

        // 电压环
        if(self->vflg)
        {
            self->targetVolt = self->targetVoltAm * self->baseSin;
            float ctrl_out = ctrl_pi_Run(&self->ctrl_vPI,self->targetVolt,self->ouputVolt);
            self->wm = (ctrl_out + self->ouputVolt) / self->inputVolt;

        }
        // 电流环
        if(self->iflg)
        {
            self->targetCurr = self->targetCurrAm * self->baseSin;
            float ctrl_out = ctrl_pi_Run(&self->ctrl_iPI,self->targetCurr,self->ouputCurr);
            self->wm = (ctrl_out + self->ouputVolt) / self->inputVolt;
        }

        // 调制输出
        if(self->baseSin > 0)
        {
            pwm_setduty_a(self->wm);
            pwm_setduty_b(0);
        }
        else
        {
            pwm_setduty_a(0);
            pwm_setduty_b(self->wm);
        }

    }
    else    // !en
    {
        if(first == 0)
        {
            pwm_alloff();
            acac_Init();
            first = 1;
        }
    }

}
void acac_Func()
{
    acac_func(&acac);
}



//--------------------------------------end of this file-----------------------------------
