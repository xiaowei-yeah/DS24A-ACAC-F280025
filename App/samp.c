/*
* File:     samp.c
* Date:     2025Äê10ÔÂ14ÈÕ
* Author:   jin

* Description:
* Version:
*/

//--------------------------------------include-----------------------------------------

#include "projectall.h"

//---------------------------------------Macro-----------------------------------------

#define cADC_SOCx_NUM       (eSocName_End)
#define cADC_COMDE_FULL     (4095)
#define cADC_VREF           (3.3f)

#define cSAMP_GAIN_VOLT     (1)
#define cSAMP_GAIN_CURR     (1)

typedef struct {
    float Ad;
    float Pu;
    float Real;
    float Gain_A2R;
    float Offset;
    float Cali_A;
    float Cali_B;
}AdcCali_typedef;

//--------------------------------Function declaration---------------------------------

//----------------------------------Value declaration----------------------------------

//----------------------------------Value definition-----------------------------------

static AdcCali_typedef Ain[cADC_SOCx_NUM];

//--------------------------------Function definition----------------------------------

/****************************************************************
* Function:     samp_Init
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void samp_Init()
{
    for(uint16_t i = 0; i < cADC_SOCx_NUM; i++)
    {
        Ain[i].Gain_A2R = 1;
        Ain[i].Offset = -cADC_COMDE_FULL/2;
        Ain[i].Cali_A = 1;
        Ain[i].Cali_B = 0;
    }

    Ain[eCurr_OutA].Gain_A2R = cSAMP_GAIN_CURR;
    Ain[eCurr_OutB].Gain_A2R = cSAMP_GAIN_CURR;
    Ain[eCurr_OutC].Gain_A2R = cSAMP_GAIN_CURR;
    Ain[eVolt_OutA].Gain_A2R = cSAMP_GAIN_VOLT;
    Ain[eVolt_OutB].Gain_A2R = cSAMP_GAIN_VOLT;
    Ain[eVolt_OutC].Gain_A2R = cSAMP_GAIN_VOLT;
    Ain[eVolt_InA].Gain_A2R = cSAMP_GAIN_VOLT;
    Ain[eVolt_InB].Gain_A2R = cSAMP_GAIN_VOLT;
    Ain[eVolt_InC].Gain_A2R = cSAMP_GAIN_VOLT;
}
/****************************************************************
* Function:     samp_updateAdc2Real_
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
uint16_t samp_updateAdc2Real_(AdcSocName_enum id,uint16_t ad)
{
    if(id >= cADC_SOCx_NUM)
    {
        return 0;
    }
    Ain[id].Ad = ad;
    Ain[id].Real = (Ain[id].Ad + Ain[id].Offset) * Ain[id].Gain_A2R \
                    * Ain[id].Cali_A + Ain[id].Cali_B;
    return 1;
}
/****************************************************************
* Function:     samp_set
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
uint16_t samp_setCaliPara(AdcSocName_enum id,float a,float b)
{
    if(id >= cADC_SOCx_NUM)
    {
        return 0;
    }
    Ain[id].Cali_A = a;
    Ain[id].Cali_B = b;
    return 1;
}
/****************************************************************
* Function:     samp_Get
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
float samp_getReal(AdcSocName_enum id)
{
    return Ain[id].Real;
}

float samp_getPu(AdcSocName_enum id)
{
    return Ain[id].Pu;
}

float samp_getAd(AdcSocName_enum id)
{
    return Ain[id].Ad;
}

//---------------------------------------------end of this file----------------------------------------------
