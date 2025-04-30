/*****************************************************************************
 * Stacja Pogodowa
 * Skład zespołu:
 * 1) Gabriela Szczuka (234983/251645) --LIDER--
 * 2) Amelka Garnys (251514)
 * 3) Emilia Szczerba (251643)
 * 4) Mikołaj Pawłoś (258681)
 ******************************************************************************/

#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_ssp.h"
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

static uint32_t msTicks = 0;
static uint8_t buf[10];

//lm75 stuff
#define I2CDEV LPC_I2C2
#define LM75_I2C_ADDR (0x4D)

//barometer stuff
#define BMP180_I2C_ADDR (0x77)

void SysTick_Handler(void) {
	msTicks++;
}

static uint32_t getTicks(void) {
	return msTicks;
}

static void init_ssp(void) {
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

int I2CRead(uint8_t addr, uint8_t *buf, uint32_t len) {
	I2C_M_SETUP_Type rxsetup;

	rxsetup.sl_addr7bit = addr;
	rxsetup.tx_data = NULL;	// Get address to read at writing address
	rxsetup.tx_length = 0;
	rxsetup.rx_data = buf;
	rxsetup.rx_length = len;
	rxsetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2CDEV, &rxsetup, I2C_TRANSFER_POLLING)
			== SUCCESS) {
		return (0);
	} else {
		return (-1);
	}
}

int I2CWrite(uint8_t addr, uint8_t *buf, uint32_t len) {
	I2C_M_SETUP_Type txsetup;

	txsetup.sl_addr7bit = addr;
	txsetup.tx_data = buf;
	txsetup.tx_length = len;
	txsetup.rx_data = NULL;
	txsetup.rx_length = 0;
	txsetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2CDEV, &txsetup, I2C_TRANSFER_POLLING)
			== SUCCESS) {
		return (0);
	} else {
		return (-1);
	}
}
void lm75_read(uint8_t *buf) {
	buf[0] = 0;
	buf[1] = 0;
	I2CRead(LM75_I2C_ADDR, buf, 2);
}

void barometer_readID(uint8_t *buf) {
	buf[0] = 0xD0;	// rejestr ID
	I2CWrite(BMP180_I2C_ADDR, buf, 1);
	I2CRead(BMP180_I2C_ADDR, buf, 1);
}

void handleInput(uint8_t joystickState, RTC_TIME_Type *time2, bool* timerOn) {
	if ((joystickState & JOYSTICK_CENTER) != 0) {
		// not used
	}

	if ((joystickState & JOYSTICK_DOWN) != 0) {
		time2->SEC = 0;
		time2->MIN = 00;
		time2->HOUR = 00;
	}

	if ((joystickState & JOYSTICK_LEFT) != 0) {
		time2->MIN--;

	}

	if ((joystickState & JOYSTICK_UP) != 0) {
		*timerOn = !*timerOn;
	}

	if ((joystickState & JOYSTICK_RIGHT) != 0) {
		time2->MIN++;

	}
}

int main(void) {
	//
	int value = 0;

	//

	init_ssp();

	//RTC CONFIG
	RTC_TIME_Type time;
	rtc_init();
	rtc_set_time();

	//I2C config
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = 2;
	PinCfg.Pinnum = 10;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 11;
	PINSEL_ConfigPin(&PinCfg);
	I2C_Init(LPC_I2C2, 100000);
	I2C_Cmd(LPC_I2C2, ENABLE);

	//LED STRIP CONFIG
	LED_STRIP_CONF ledStrip;
	ledStrip.dir = 0;
	ledStrip.cnt = 0;
	ledStrip.ledOn = 0;
	ledStrip.ledOff = 0;
	pca9532_init();

	oled_start();
	temp_init(&getTicks);

	if (SysTick_Config(SystemCoreClock / 1000)) {
		while (1)
			;  // Capture error
	}

	//buffers for internal termometer nad lm75 respectivley
	int32_t temperature = 0;
	uint8_t bufTemp[2] = { 0 };

	uint8_t barId;

	//joystick variables
	RTC_TIME_Type time2;
	time2.SEC = 0;
	time2.MIN = 00;
	time2.HOUR = 00;
	uint8_t joy = 0;
	joystick_init();
	bool timerOn = false;
	timer_init(LPC_TIM1);

	while (1) {

		//

		joy = joystick_read();

		handleInput(joy, &time2, &timerOn);

		/*get temperature multiplied by 10 */
		temperature = temp_read();
		lm75_read(bufTemp);
		TIMER0_IRQHandler(LPC_TIM1, &time2, timerOn);

		rtc_get_time(&time);

		oled_show_temp1(temperature, buf);
		oled_show_temp2(bufTemp, buf);
		oled_show_timer(time2, buf);
		oled_show_clock(time, buf);

		barometer_readID(&barId);
		sprintf(buf, "%d", barId);
		oled_putString(1, 52, buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);
		manageLedStrips(&ledStrip);

		/* delay */
		Timer0_Wait(200);
	}

}

void check_failed(uint8_t *file, uint32_t line) {
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
		;
}
