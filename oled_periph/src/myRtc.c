#include "./myRtc.h"

void rtc_init(void) {
RTC_Init(LPC_RTC); // Inicjalizacja RTC
RTC_Cmd(LPC_RTC, ENABLE); // Włączenie RTC
}


void rtc_set_time(void) {
RTC_TIME_Type time;

time.SEC = 0;
time.MIN = 30;
time.HOUR = 14;
time.DOM = 20;
time.MONTH = 3;
time.YEAR = 2025;

RTC_SetFullTime(LPC_RTC, &time);
}


void rtc_get_time(RTC_TIME_Type* time) {
RTC_GetFullTime(LPC_RTC, time);
}
