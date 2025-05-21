#ifndef SCREENMANAGMENT_H_
#define SCREENMANAGMENT_H_
#include <stdint.h>
#include "lpc17xx_rtc.h"
#include "oled.h"
#include <stdio.h>

void oled_start(void);

void oled_show_temp1(int32_t temperature, uint8_t* buf);

void oled_show_temp2(const uint8_t bufTemp[2], uint8_t* buf);

void oled_show_timer(const RTC_TIME_Type* time2, uint8_t* buf);

void oled_show_clock(const RTC_TIME_Type* time, uint8_t* buf);

#endif /* SCREENMANAGMENT_H_ */




