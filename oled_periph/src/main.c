/*****************************************************************************
 * Stacja Pogodowa
 * Skład zespołu:
 * 1) Gabriela Szczuka (234983/251645) --LIDER--
 * 2) Amelka Garnys (251514)
 * 3) Emilia Szczerba (251643)
 * 4) Mikołaj Pawłoś (258681)
 ******************************************************************************/


#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_rtc.h"
#include "lpc17xx_i2c.h"

#include "light.h"
#include "oled.h"
#include "temp.h"
#include "acc.h"
#include "joystick.h"
#include "pca9532.h"
#include <stdio.h>
#include <stdbool.h>
#include "../headers/myRtc.h"
#include "../headers/ledStrips.h"
#include "../headers/screenManagment.h"
#include "../headers/myTimer.h"
#include "../headers/spi_i2c.h"
#include "../headers/music.h"

static uint32_t msTicks = 0;
static uint8_t buf[10];

//lm75 stuff
#define LM75_I2C_ADDR (0x49)

void SysTick_Handler(void) {
    msTicks++;
}

static uint32_t getTicks(void) {
    return msTicks;
}

void lm75_read(uint8_t *buf) {
    buf[0] = 0;
    buf[1] = 0;
    I2CRead(LM75_I2C_ADDR, buf, 2);
}

void handleInput(uint8_t joystickState, RTC_TIME_Type *time2, bool* timerOn) {
    if ((joystickState & JOYSTICK_CENTER) != 0) {
        // not used
    }

    if ((joystickState & JOYSTICK_DOWN) != 0) {
        time2->SEC = 0;
        time2->MIN = 0;
        time2->HOUR = 0;
    }

    if ((joystickState & JOYSTICK_LEFT) != 0) {
        if(time2->MIN > 0) {
            time2->MIN--;
        }

    }

    if ((joystickState & JOYSTICK_UP) != 0) {
        *timerOn = !*timerOn;
    }

    if ((joystickState & JOYSTICK_RIGHT) != 0) {
        if(time2->MIN < 59) {
            time2->MIN++;
            time2->SEC++;
        }

    }
}



int main(void) {

    init_ssp();

    //RTC CONFIG
    RTC_TIME_Type time;
    rtc_init();

    enableI2C();

    //LED STRIP CONFIG
    LED_STRIP_CONF ledStrip;
    ledStripInit(&ledStrip);
    pca9532_init();

    oled_start();
    temp_init(&getTicks);

    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1) {
            ;
        }
    }

    //buffers for internal termometer nad lm75 respectivley
    //int32_t temperature = 0;
    uint8_t bufTemp[2] = { 0 };

    //joystick variables
    RTC_TIME_Type time2;
    time2.SEC = 0;
    time2.MIN = 0;
    time2.HOUR = 0;
    //uint8_t joy = 0;
    joystick_init();
    bool timerOn = false;
    timer_init(LPC_TIM1);

    MUSIC_CONFIG musicConf;
    setupMusic(&musicConf);

    while (1) {

        uint8_t joy = joystick_read();

        handleInput(joy, &time2, &timerOn);

        /*get temperature multiplied by 10 */
        int32_t temperature = temp_read();
        lm75_read(bufTemp);
        bool timerFinished = timer_interrupt_handler(LPC_TIM1, &time2, timerOn);
        rtc_get_time(&time);

        oled_show_temp1(temperature, buf);
        oled_show_temp2(bufTemp, buf);
        oled_show_timer(&time2, buf);
        oled_show_clock(&time, buf);

        if(timerFinished) {
            playMusic(&musicConf);
        }

        manageLedStrips(&ledStrip);

        /* delay */
        Timer0_Wait(200);
    }

}
