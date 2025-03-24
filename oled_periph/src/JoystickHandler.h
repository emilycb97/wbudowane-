/*
 * JoystickHandler.c
 *
 *  Created on: 24 mar 2025
 *      Author: student
 */
#ifndef JOYSTICK_HANDLER_H
#define JOYSTICK_HANDLER_H

#include "lpc17xx_gpio.h"
#include "lpc17xx_rtc.h"
#include "joystick.h"
//#include "buzzer.h" // Dodaj obsługę buzzera
#include <stdint.h>
#include <stdbool.h>

void joystick_init(void);
uint8_t joystick_read(void);
bool joystick_checkAlarm(void);



#endif
