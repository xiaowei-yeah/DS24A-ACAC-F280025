/*
* File:     acac.c
* Date:     2025年10月24日
* Author:   jin

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
    float       lastSin;

    float       wn;
    float       ts;

    enum en_dis_enum    en;
    enum en_dis_enum    currflg;
    enum en_dis_enum    voltflg;
    enum en_dis_enum    openloopflg;

    enum en_dis_enum    firstOverZeroflg;

    ctrl_spll_TyprDef       spll;
    ctrl_pi_TyprDef         ctrl_iPI;
    ctrl_pi_TyprDef         ctrl_vPI;
    ctrl_pi_TyprDef         ctrl_vRmsPI;

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
    self->lastSin = 0;

    self->en = eDisable;

    acac.firstOverZeroflg = eDisable;

    ctrl_spll_Init(&self->spll,self->ts,self->wn);
    ctrl_pi_Init(&self->ctrl_iPI,10,0,100,-100,self->ts);
    ctrl_pi_Init(&self->ctrl_vPI,2,15,100,-100,self->ts);
    ctrl_pi_Init(&self->ctrl_vRmsPI,1.4,100,50,0,self->ts);

}
void acac_Init()
{
    acac_init(&acac);
    acac.currflg = eEnable;
    acac.voltflg = eDisable;
    acac.openloopflg = eDisable;
}

/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
#pragma CODE_SECTION(acac_func,".TI.ramfunc");
void acac_func(acac_TypeDef *self ,float Io ,float Vo ,float Vin)
{

    static uint16_t first;

    self->ouputCurr = Io;
    self->ouputVolt = Vo;
    self->inputVolt = Vin == 0 ? 0.000001f : Vin;   // 防除零

#define INPUT_AC    1

#if INPUT_AC    //正常工况 交流输入

    ctrl_spll_Run(&self->spll,self->inputVolt);
    self->baseSin = -cosf(self->spll.wt);

    // 锁相完成,启动后检测首次过零
    if(self->en == eEnable && self->firstOverZeroflg == eDisable && self->spll.ok)
    {
        if(self->baseSin >= 0 && self->lastSin < 0)
        {
            self->firstOverZeroflg = eEnable;
        }
        self->lastSin = self->baseSin;
    }

#else           //测试工况 直流输入

    static float wt1;
    wt1 += 0.01571f;
    if(wt1 > m2Pi)
    {
        wt1 = wt1 - m2Pi;
    }
    self->baseSin = sinf(wt1) * 0.5f + 0.5f;

    // 直接跳过正常的检测，置位各标志位
    if(self->en == eEnable && self->firstOverZeroflg == eDisable)
    {
        self->firstOverZeroflg = eEnable;
        self->spll.ok = eEnable;
    }

#endif



    // 控制算法
    if(self->en == eEnable && self->firstOverZeroflg == eEnable && self->spll.ok)    // 过零点开始运行，冲击小。
    {
        if(first == 1)
        {
            first = 0;
            pwm_allon();
        }

        // 电压环
        if(self->voltflg)
        {
            float ctrlRms_out = ctrl_pi_Run(&self->ctrl_vRmsPI,self->targetVoltAm*0.707,samp_getRms(eVolt_OutA));

            self->targetVolt = ctrlRms_out * self->baseSin;
            float ctrl_out = ctrl_pi_Run(&self->ctrl_vPI,self->targetVolt,self->ouputVolt);
            self->wm = (ctrl_out + self->ouputVolt) / (-self->spll.ud * self->baseSin);

        }
        // 电流环
        if(self->currflg)
        {
            self->targetCurr = self->targetCurrAm * self->baseSin;
            float ctrl_out = ctrl_pi_Run(&self->ctrl_iPI,self->targetCurr,self->ouputCurr);
            self->wm = (ctrl_out + self->ouputVolt) / (50 * self->baseSin);
        }
        // 开环
        if(self->openloopflg)
        {
            self->wm = self->targetVoltAm * self->baseSin / (50 * self->baseSin);
        }

        // 调制输出
        if(self->baseSin >= 0)
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
        pwm_alloff();   //关闭PWM引脚

        if(first == 0)  // 首次关闭，初始化控制器
        {
            acac_init(self);
            first = 1;
        }
    }

}
#pragma CODE_SECTION(acac_Func,".TI.ramfunc");
void acac_Func(float Io ,float Vo ,float Vin)
{
    acac_func(&acac,Io,Vo,Vin);
}

/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void acac_Start(void)
{
    acac.en = eEnable;
}

void acac_Stop(void)
{
    acac.en = eDisable;
}

void acac_SetVoltLoop(void)
{
    acac.en = eDisable;
    acac.openloopflg = eDisable;
    acac.currflg = eDisable;
    acac.voltflg = eEnable;
}
void acac_SetCurrLoop(void)
{
    acac.en = eDisable;
    acac.openloopflg = eDisable;
    acac.voltflg = eDisable;
    acac.currflg = eEnable;
}
uint16_t acac_GetSpllState(void)
{
    return acac.spll.ok;
}

void acac_SetTargetVoltAm(float v)
{
    v = v > 50 ? 50 : v;
    v = v < 0 ? 0 : v;
    acac.targetVoltAm = v;
}
float acac_GetTargetVoltAm()
{
    return acac.targetVoltAm;
}
void acac_SetTargetCurrAm(float v)
{
    v = v > 2 ? 2 : v;
    v = v < 0 ? 0 : v;
    acac.targetCurrAm = v;
}
float acac_GetTargetCurrAm()
{
    return acac.targetCurrAm;
}
//--------------------------------------end of this file-----------------------------------
