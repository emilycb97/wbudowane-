#include "../headers/screenManagment.h"
#include <stdio.h>
#include <string.h>

/*********************************************************************//**
 * @brief       Initializes the OLED display
 **********************************************************************/
void oled_start(void) {
    static const uint8_t temp_label[] = "Temp   : ";
    static const uint8_t timer_label[] = "Timer   : ";

    oled_init();
    oled_clearScreen(OLED_COLOR_WHITE);
    oled_putString(1, 1, temp_label, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
    oled_putString(1, 28, timer_label, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}

/*********************************************************************//**
 * @brief       Displays scaled temperature
 **********************************************************************/
void oled_show_temp1(int32_t temperature, uint8_t* buf) {
    if (buf != NULL) {
        (void)snprintf((char*)buf, 16U, "%02ld.%ld C",
                       temperature / 10L,
                       temperature % 10L);
        oled_putString((1U + (9U * 6U)), 1U, buf,
                       OLED_COLOR_BLACK, OLED_COLOR_WHITE);
    }
}

/*********************************************************************//**
 * @brief       Displays raw temperature data
 **********************************************************************/
void oled_show_temp2(const uint8_t bufTemp[2], uint8_t* buf) {
    if ((bufTemp != NULL) && (buf != NULL)) {
        (void)snprintf((char*)buf, 16U, "%02u.%02u C",
                       bufTemp[0], bufTemp[1]);
        oled_putString(1U, 44U, buf,
                       OLED_COLOR_BLACK, OLED_COLOR_WHITE);
    }
}

/*********************************************************************//**
 * @brief       Displays countdown timer
 **********************************************************************/
void oled_show_timer(const RTC_TIME_Type* time2, uint8_t* buf) {
    if ((time2 != NULL) && (buf != NULL)) {
        (void)snprintf((char*)buf, 16U, "%02u:%02u:%02u",
                       time2->HOUR, time2->MIN, time2->SEC);
        oled_putString(1U, 36U, buf,
                       OLED_COLOR_BLACK, OLED_COLOR_WHITE);
    }
}

/*********************************************************************//**
 * @brief       Displays current time and date
 **********************************************************************/
void oled_show_clock(const RTC_TIME_Type* time, uint8_t* buf) {
    if ((time != NULL) && (buf != NULL)) {
        (void)snprintf((char*)buf, 16U, "%02u:%02u:%02u",
                       time->HOUR, time->MIN, time->SEC);
        oled_putString(1U, 10U, buf,
                       OLED_COLOR_BLACK, OLED_COLOR_WHITE);

        (void)snprintf((char*)buf, 16U, "%02u/%02u/%04u",
                       time->DOM, time->MONTH, time->YEAR);
        oled_putString(1U, 19U, buf,
                       OLED_COLOR_BLACK, OLED_COLOR_WHITE);
    }
}