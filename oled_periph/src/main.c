/*****************************************************************************
 *   Peripherals such as temp sensor, light sensor, accelerometer,
 *   and trim potentiometer are monitored and values are written to
 *   the OLED display.
 *
 *   Copyright(C) 2010, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/



#include "lpc17xx_pinsel.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_ssp.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_rtc.h"


#include "light.h"
#include "oled.h"
#include "temp.h"
#include "acc.h"

#include "./myRtc.h"

static uint32_t msTicks = 0;
static uint8_t buf[10];

void SysTick_Handler(void) {
    msTicks++;
}

static uint32_t getTicks(void)
{
    return msTicks;
}

static void init_ssp(void)
{
	SSP_CFG_Type SSP_ConfigStruct;
	PINSEL_CFG_Type PinCfg;

	/*
	 * Initialize SPI pin connect
	 * P0.7 - SCK;
	 * P0.8 - MISO
	 * P0.9 - MOSI
	 * P2.2 - SSEL - used as GPIO
	 */
	PinCfg.Funcnum = 2;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 7;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 8;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 9;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Funcnum = 0;
	PinCfg.Portnum = 2;
	PinCfg.Pinnum = 2;
	PINSEL_ConfigPin(&PinCfg);

	SSP_ConfigStructInit(&SSP_ConfigStruct);

	// Initialize SSP peripheral with parameter given in structure above
	SSP_Init(LPC_SSP1, &SSP_ConfigStruct);

	// Enable SSP peripheral
	SSP_Cmd(LPC_SSP1, ENABLE);

}

// 100 razy na sekunde

int main (void)
{
    int32_t t = 0;

    init_ssp();
    joystick_init();
    rtc_init();
    rtc_set_time();

    oled_init();


    temp_init (&getTicks);


	if (SysTick_Config(SystemCoreClock / 1000)) {
		    while (1);  // Capture error
	}


    light_enable();
    light_setRange(LIGHT_RANGE_4000);

    oled_clearScreen(OLED_COLOR_WHITE);

    oled_putString(1,1,  (uint8_t*)"Temp   : ", OLED_COLOR_BLACK, OLED_COLOR_WHITE);


    while(1) {


        /* Temperature */
        t = temp_read();


        /* output values to OLED display */

        sprintf(buf, "%02d.%d C", t/10, t%10);
        //oled_fillRect((1+9*6),1, 80, 8, OLED_COLOR_WHITE);
        oled_putString((1+9*6),1, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
        RTC_TIME_Type time;
        rtc_get_time(&time);

        sprintf(buf, "%02d:%02d:%02d", time.HOUR, time.MIN, time.SEC);
        //oled_fillRect(1, 10, 120, 26, OLED_COLOR_WHITE);
        oled_putString(1, 10, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);

        sprintf(buf, "%02d/%02d/%04d", time.DOM, time.MONTH, time.YEAR);
        //oled_fillRect(1, 19, 120, 35, OLED_COLOR_WHITE);
        oled_putString(1, 19, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);

        /* delay */
        Timer0_Wait(200);
    }

}

void check_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while(1);
}
