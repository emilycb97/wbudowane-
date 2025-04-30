/*
 * myTimer.h
 *
 *  Created on: 30 kwi 2025
 *      Author: student
 */

#ifndef MYTIMER_H_
#define MYTIMER_H_
#include <lpc17xx_rtc.h>
#include <lpc17xx_timer.h>

void timer_init(LPC_TIM_TypeDef *TIMx);
void TIMER0_IRQHandler(LPC_TIM_TypeDef *TIMx, RTC_TIME_Type* time2, FunctionalState timerState);
void timer_set_time(void);
void timer_get_time(RTC_TIME_Type* time);

#endif /* MYTIMER_H_ */
