#include "../headers/screenManagment.h"


void oled_start() {
	oled_init();
	oled_clearScreen(OLED_COLOR_WHITE);
	oled_putString(1, 1, (uint8_t*) "Temp   : ", OLED_COLOR_BLACK,
			OLED_COLOR_WHITE);
	oled_putString(1, 28, (uint8_t*) "Timer   : ", OLED_COLOR_BLACK,
					OLED_COLOR_WHITE);
}

void oled_show_temp1(int32_t temperature, uint8_t* buf) {
	sprintf(buf, "%02d.%d C", temperature / 10, temperature % 10);
	oled_putString((1 + 9 * 6), 1, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}

void oled_show_temp2(uint8_t bufTemp[], uint8_t* buf) {
	sprintf(buf, "%02d.%02d C", bufTemp[0], bufTemp[1]);
	oled_putString(1, 44, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}

void oled_show_timer(RTC_TIME_Type time2, uint8_t* buf) {
	sprintf(buf, "%02d:%02d:%02d", time2.HOUR, time2.MIN, time2.SEC);
	oled_putString(1, 36, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
}

void oled_show_clock(RTC_TIME_Type time, uint8_t* buf){
	sprintf(buf, "%02d:%02d:%02d", time.HOUR, time.MIN, time.SEC);
	oled_putString(1, 10, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);

	sprintf(buf, "%02d/%02d/%04d", time.DOM, time.MONTH, time.YEAR);
	oled_putString(1, 19, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);

}

