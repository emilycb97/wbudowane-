/*
 * myTimer.c
 *
 *  Created on: 30 kwi 2025
 *      Author: student
 */
#include "../headers/myTimer.h"
#include <lpc17xx_timer.h>
#include <stdbool.h>
/*********************************************************************//**
 * @brief       Initializes a hardware timer to generate an interrupt every 1 second.
 * @param[in]   TIMx    Pointer to the timer peripheral (e.g., LPC_TIM0, LPC_TIM1, etc.)
 * @return      None
 *
 * This function sets up the timer with a 1 ms tick using a prescaler,
 * and configures it to generate an interrupt every 1000 ticks (1 second).
 **********************************************************************/
void timer_init(LPC_TIM_TypeDef *TIMx) {
    TIM_TIMERCFG_Type timerCfg;
    TIM_MATCHCFG_Type matchCfg;

    // Timer configuration: 1 ms tick
    timerCfg.PrescaleOption = TIM_PRESCALE_USVAL;
    timerCfg.PrescaleValue = 1000;

    TIM_Init(TIMx, TIM_TIMER_MODE, &timerCfg);

    // Match configuration for 1 second interrupt
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


/*********************************************************************//**
 * @brief       Handles countdown logic in a timer interrupt.
 * @param[in]   TIMx        Timer peripheral that triggered the interrupt
 * @param[in]   time2       Pointer to the RTC_TIME_Type structure to decrement
 * @param[in]   timerState  ENABLE to process countdown, DISABLE to ignore
 * @return      None
 *
 * This function checks for a match interrupt on MR0 and, if the timer is
 * active, decrements the provided time structure (HH:MM:SS).
 **********************************************************************/
bool timer_interrupt_handler(LPC_TIM_TypeDef *TIMx, RTC_TIME_Type *time2,
                             FunctionalState timerState) {

    bool finished = false;

    if (timerState == ENABLE) {
        if (TIM_GetIntStatus(TIMx, TIM_MR0_INT)) {
            if ((time2->SEC > 0) || (time2->MIN > 0) || (time2->HOUR > 0)) {
                if (time2->SEC == 0) {
                    time2->SEC = 59;
                    if (time2->MIN == 0) {
                        time2->MIN = 59;
                        if (time2->HOUR > 0) {
                            time2->HOUR--;
                        }
                    } else {
                        time2->MIN--;
                    }
                } else {
                    time2->SEC--;
                    if ((time2->HOUR == 0) && (time2->MIN == 0) && (time2->SEC == 0)) {
                        finished = true;
                    }
                }
            }
        }
        TIM_ClearIntPending(TIMx, TIM_MR0_INT);
    }

    return finished;
}