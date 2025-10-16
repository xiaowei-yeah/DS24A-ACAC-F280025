/*
* File:     pwm.h
* Date:     2025Äê10ÔÂ14ÈÕ
* Author:   jin

* Description:
* Version:
*/
#ifndef APP_SAMP_H_
#define APP_SAMP_H_

//--------------------------Include----------------------------------------

//---------------------------Macro-----------------------------------

typedef enum
{
  eCurr_OutA     = 0,
  eCurr_OutB     = 1,
  eCurr_OutC     = 2,
  eVolt_OutA     = 3,
  eVolt_OutB     = 4,
  eVolt_OutC     = 5,
  eVolt_InA      = 6,
  eVolt_InB      = 7,
  eVolt_InC      = 8,
  eSocName_End
}AdcSocName_enum;

//--------------------Function declaration---------------------------------

void samp_Init();
uint16_t samp_Adc2Real_Update(AdcSocName_enum id,uint16_t ad);
float samp_GetReal(AdcSocName_enum id);
float samp_GetPu(AdcSocName_enum id);
float samp_GetAd(AdcSocName_enum id);

#endif /* APP_SAMP_H_ */
//---------------------------------------------end of this file----------------------------------------------
