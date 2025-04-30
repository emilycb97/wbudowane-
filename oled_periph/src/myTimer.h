/*
 * myTimer.h
 *
 *  Created on: 30 kwi 2025
 *      Author: student
 */

#ifndef MYTIMER_H_
#define MYTIMER_H_

void timer_init(LPC_TIM_TypeDef *TIMx);
void timer_set_time(void);
void timer_get_time(RTC_TIME_Type* time);

#endif /* MYTIMER_H_ */
