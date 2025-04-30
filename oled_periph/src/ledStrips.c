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
    if (strip->cnt < 16)
        strip->ledOn |= (1 << strip->cnt);
    if (strip->cnt > 15)
        strip->ledOn &= ~(1 << (strip->cnt - 16));

    if (strip->cnt > 15)
        strip->ledOff |= (1 << (strip->cnt - 16));
    if (strip->cnt < 16)
        strip->ledOff &= ~(1 << strip->cnt);

    pca9532_setLeds(strip->ledOn, strip->ledOff);

    if (strip->dir) {
        if (strip->cnt == 0)
            strip->cnt = 31;
        else
            strip->cnt--;
    } else {
        strip->cnt++;
        if (strip->cnt >= 32)
            strip->cnt = 0;
    }
}
