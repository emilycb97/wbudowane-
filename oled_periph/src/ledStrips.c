#include "../headers/ledStrips.h"
#include "pca9532.h"

/*********************************************************************//**
 * @brief       Initializes the LED strip configuration structure.
 * @param[in]   ledStrip    Pointer to the LED_STRIP_CONF structure to initialize.
 * @return      None
 **********************************************************************/
void ledStripInit(LED_STRIP_CONF *ledStrip) {
    ledStrip->dir = 0;
    ledStrip->cnt = 0;
    ledStrip->ledOn = 0;
    ledStrip->ledOff = 0;
}


/*********************************************************************//**
 * @brief       Manages LED strip animation by updating the LED state and direction.
 * @param[in]   strip   Pointer to the LED_STRIP_CONF structure holding animation state.
 * @return      None
 *
 * This function cycles through 32 LEDs, updating which LEDs are on or off
 * based on the current count and direction. It also updates the LED strip
 * via the PCA9532 I/O expander.
 **********************************************************************/
void manageLedStrips(LED_STRIP_CONF *strip) {
    if (strip->cnt < (uint8_t)16) {
        strip->ledOn |= (uint32_t)1U << strip->cnt;
    }
    if (strip->cnt > (uint8_t)15) {
        strip->ledOn &= ~(uint32_t)(1UL << (strip->cnt - 16U));
    }
    if (strip->cnt > (uint8_t)15) {
        strip->ledOff |= (uint32_t)(1UL << (strip->cnt - 16U));
    }
    if (strip->cnt < (uint8_t)16) {
        strip->ledOff &= ~(uint32_t)(1UL << strip->cnt);
    }

    pca9532_setLeds(strip->ledOn, strip->ledOff);

    if (strip->dir) {
        if (strip->cnt == (uint8_t)0) {
            strip->cnt = 31;
        }
        else {
            strip->cnt--;
        }
    } else {
        strip->cnt++;
        if (strip->cnt >= (uint8_t)32) {
            strip->cnt = 0;
        }
    }
}