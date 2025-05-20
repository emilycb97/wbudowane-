/*
 * ledStrips.h
 *
 *  Created on: 2 kwi 2025
 *      Author: student
 */

#ifndef LEDSTRIPS_H_
#define LEDSTRIPS_H_
#include <stdint.h>

typedef struct{
    uint8_t dir;
    uint32_t cnt;
    uint16_t ledOn;
    uint16_t ledOff;
}LED_STRIP_CONF;


void manageLedStrips(LED_STRIP_CONF *strip);
void ledStripInit(LED_STRIP_CONF *strip);

#endif /* LEDSTRIPS_H_ */
