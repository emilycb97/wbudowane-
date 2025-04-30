#include "../headers/myRtc.h"

/*********************************************************************//**
 * @brief       Initializes the Real-Time Clock (RTC) peripheral and sets default time.
 * @param       None
 * @return      None
 *
 * This function initializes the RTC, enables it, and sets the default time
 * using the rtc_set_time() function.
 **********************************************************************/
void rtc_init(void) {
    RTC_Init(LPC_RTC); // Initialize RTC
    RTC_Cmd(LPC_RTC, ENABLE); // Enable RTC
    rtc_set_time(); // Set initial time
}


/*********************************************************************//**
 * @brief       Sets the RTC to a predefined date and time.
 * @param       None
 * @return      None
 *
 * This function sets the RTC time to 14:30:00 on 20th March 2025.
 **********************************************************************/
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


/*********************************************************************//**
 * @brief       Retrieves the current time from the RTC.
 * @param[out]  time    Pointer to an RTC_TIME_Type structure to store the current time.
 * @return      None
 **********************************************************************/
void rtc_get_time(RTC_TIME_Type *time) {
    RTC_GetFullTime(LPC_RTC, time);
}
