/*
* File: 	acac.h
* Date: 	2025Äê10ÔÂ24ÈÕ
* Author: 	jinjiale

* Description: 	
* Version: 		
*/
#ifndef APP_ACAC_H_
#define APP_ACAC_H_

//------------------------------------------Include----------------------------------------

//-------------------------------------------Macro-----------------------------------------

//--------------------------------------Struct And Type------------------------------------

//------------------------------------Function declaration---------------------------------
void acac_Init();
void acac_Func(float Io ,float Vo ,float Vin);
void acac_Start(void);
void acac_Stop(void);
void acac_SetVoltLoop(void);
void acac_SetCurrLoop(void);
uint16_t acac_GetSpllState(void);
uint16_t acac_GetSpllState(void);
void acac_SetTargetVoltAm(float v);
float acac_GetTargetVoltAm();
void acac_SetTargetCurrAm(float v);
float acac_GetTargetCurrAm();
#endif /* APP_ACAC_H_ */

//--------------------------------------end of this file-----------------------------------
