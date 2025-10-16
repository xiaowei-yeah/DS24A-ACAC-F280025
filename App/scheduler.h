/*
* File: 	scheduler.h
* Date: 	2025Äê9ÔÂ29ÈÕ
* Author: 	jin

* Description: 	
* Version: 		
*/
#ifndef APP_FUNC_SCHEDULER_H_
#define APP_FUNC_SCHEDULER_H_

//------------------------------------------Include----------------------------------------

//--------------------------------------typedef definition-----------------------------------

typedef struct
{
    void(*task_func)(void);
    uint16_t rate_hz;
    uint16_t interval_ticks;
    uint32_t last_run;
}sched_task_TypeDef;

//------------------------------------Function declaration---------------------------------

void Scheduler_Setup(void);
void Scheduler_Run(void);



#endif /* APP_FUNC_SCHEDULER_H_ */

//---------------------------------------------end of this file----------------------------------------------
