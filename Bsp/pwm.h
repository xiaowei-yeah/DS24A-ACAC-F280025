/*
* File: 	pwm.h
* Date: 	2025Äê10ÔÂ14ÈÕ
* Author: 	jin

* Description: 	
* Version: 		
*/
#ifndef BSP_PWM_H_
#define BSP_PWM_H_

//--------------------------Include----------------------------------------

//---------------------------Macro-----------------------------------

//--------------------Function declaration---------------------------------

void pwm_alloff();
void pwm_allon();
void pwm_setduty_a(float duty);
void pwm_setduty_b(float duty);

#endif /* BSP_PWM_H_ */
//---------------------------------------------end of this file----------------------------------------------
