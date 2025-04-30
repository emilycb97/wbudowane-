#include "../headers/ledStrips.h"
#include "pca9532.h"

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
