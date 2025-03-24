/*
 * JoystickHandler.c
 *
 *  Created on: 24 mar 2025
 *      Author: student
 */
#include "JoystickHandler.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"

#define JOYSTICK_PORT 1
#define JOYSTICK_UP (1 << 23)
#define JOYSTICK_DOWN (1 << 25)
#define JOYSTICK_LEFT (1 << 26)
#define JOYSTICK_RIGHT (1 << 27)
#define JOYSTICK_CENTER (1 << 24)

static uint32_t alarmTime = 0; // Czas alarmu (sekundy)

void joystick_init(void) {
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = 0;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = JOYSTICK_PORT;

	for (int pin = 23; pin <= 27; pin++) {
		PinCfg.Pinnum = pin;
		PINSEL_ConfigPin(&PinCfg);
		GPIO_SetDir(JOYSTICK_PORT, (1 << pin), 0); // Ustawiamy jako wejście
	}
}

uint8_t joystick_read(void) {
	return GPIO_ReadValue(JOYSTICK_PORT)
			& (JOYSTICK_UP | JOYSTICK_DOWN | JOYSTICK_LEFT | JOYSTICK_RIGHT
					| JOYSTICK_CENTER);
}

bool joystick_checkAlarm(void) {
	RTC_TIME_Type time;
	rtc_get_time(&time);

	uint32_t currentTime = time.HOUR * 3600 + time.MIN * 60 + time.SEC;

	if (currentTime >= alarmTime && alarmTime != 0) {
		alarmTime = 0; // Resetujemy alarm po uruchomieniu
		return true;
	}
	return false;
}

void joystick_setAlarm(void) {
	RTC_TIME_Type time;
	rtc_get_time(&time);

	alarmTime = time.HOUR * 3600 + time.MIN * 60 + time.SEC + 10; // Ustawiamy alarm na 10 sekund do przodu
}

