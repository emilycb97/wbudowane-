/*
 * myTimer.c
 *
 *  Created on: 30 kwi 2025
 *      Author: student
 */
#include "./myTimer.h"
#include <lpc17xx_timer.h>

void timer_init(LPC_TIM_TypeDef *TIMx) {
	TIM_TIMERCFG_Type timerCfg;
	TIM_MATCHCFG_Type matchCfg;

	// Timer configuration: use default settings
	timerCfg.PrescaleOption = TIM_PRESCALE_USVAL;
	timerCfg.PrescaleValue = 1000; // Timer tick every 1 ms (assuming 1 MHz PCLK)

	TIM_Init(TIMx, TIM_TIMER_MODE, &timerCfg);

	// Match configuration: interrupt and reset on match
	matchCfg.MatchChannel = 0;
	matchCfg.IntOnMatch = ENABLE;
	matchCfg.ResetOnMatch = ENABLE;
	matchCfg.StopOnMatch = DISABLE;
	matchCfg.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	matchCfg.MatchValue = 1000; // 1000 ms = 1 second

	TIM_ConfigMatch(TIMx, &matchCfg);

	// Start timer
	TIM_Cmd(TIMx, ENABLE);
}

void TIMER0_IRQHandler(LPC_TIM_TypeDef *TIMx, RTC_TIME_Type *time2,
		FunctionalState timerState) {
	if (timerState == ENABLE) {
		if (TIM_GetIntStatus(TIMx, TIM_MR0_INT)) {

			if (time2->SEC > 0 || time2->MIN > 0 || time2->HOUR > 0) {
				if (time2->SEC == 0) {
					time2->SEC = 59;
					if (time2->MIN == 0) {
						time2->MIN = 59;
						if (time2->HOUR > 0)
							time2->HOUR--;
					} else {
						time2->MIN--;
					}
				} else {
					time2->SEC--;
				}
			}
		}
		TIM_ClearIntPending(TIMx, TIM_MR0_INT);
	}
}

