#include "../headers/screenManagment.h"


/*********************************************************************//**
 * @brief       Initializes the OLED display and prints static labels.
 * @param       None
 * @return      None
 *
 * Clears the OLED screen and displays labels for temperature and timer.
 **********************************************************************/
void oled_start() {
    oled_init();
    oled_clearScreen(OLED_COLOR_WHITE);
    oled_putString(1, 1, (uint8_t*) "Temp   : ", OLED_COLOR_BLACK, OLED_COLOR_WHITE);
    oled_putString(1, 28, (uint8_t*) "Timer   : ", OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}


/*********************************************************************//**
 * @brief       Displays temperature (scaled by 10) on the OLED.
 * @param[in]   temperature Temperature value multiplied by 10 (e.g., 235 = 23.5°C)
 * @param[out]  buf         Pointer to a buffer for formatted string output
 * @return      None
 **********************************************************************/
void oled_show_temp1(int32_t temperature, uint8_t* buf) {
    sprintf(buf, "%02d.%d C", temperature / 10, temperature % 10);
    oled_putString((1 + 9 * 6), 1, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}


/*********************************************************************//**
 * @brief       Displays raw temperature data from a buffer on the OLED.
 * @param[in]   bufTemp     2-byte array where bufTemp[0] is integer part,
 *                          bufTemp[1] is decimal part
 * @param[out]  buf         Pointer to a buffer for formatted string output
 * @return      None
 **********************************************************************/
void oled_show_temp2(uint8_t bufTemp[], uint8_t* buf) {
    sprintf(buf, "%02d.%02d C", bufTemp[0], bufTemp[1]);
    oled_putString(1, 44, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}


/*********************************************************************//**
 * @brief       Displays a countdown timer (HH:MM:SS) on the OLED.
 * @param[in]   time2       RTC_TIME_Type structure holding countdown time
 * @param[out]  buf         Pointer to a buffer for formatted string output
 * @return      None
 **********************************************************************/
void oled_show_timer(RTC_TIME_Type time2, uint8_t* buf) {
    sprintf(buf, "%02d:%02d:%02d", time2.HOUR, time2.MIN, time2.SEC);
    oled_putString(1, 36, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}


/*********************************************************************//**
 * @brief       Displays the current clock time and date on the OLED.
 * @param[in]   time        RTC_TIME_Type structure holding current time
 * @param[out]  buf         Pointer to a buffer for formatted string output
 * @return      None
 **********************************************************************/
void oled_show_clock(RTC_TIME_Type time, uint8_t* buf){
    sprintf(buf, "%02d:%02d:%02d", time.HOUR, time.MIN, time.SEC);
    oled_putString(1, 10, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);

    sprintf(buf, "%02d/%02d/%04d", time.DOM, time.MONTH, time.YEAR);
    oled_putString(1, 19, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}

