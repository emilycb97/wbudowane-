/*****************************************************************************
 *   This example is is playing a WAV file
 *
 *   Copyright(C) 2010, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/

#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_timer.h"
#include <stdint.h>

extern const unsigned char sound_8k[];
extern int sound_sz;

int main (void)
{
	PINSEL_CFG_Type PinCfg;

    uint32_t cnt = 0;
    uint32_t off = 0;
    uint32_t sampleRate = 0;
    uint32_t delay = 0;

    GPIO_SetDir(2, 1<<0, 1);
    GPIO_SetDir(2, 1<<1, 1);

    GPIO_SetDir(0, 1<<27, 1);
    GPIO_SetDir(0, 1<<28, 1);
    GPIO_SetDir(2, 1<<13, 1);
    GPIO_SetDir(0, 1<<26, 1);

    GPIO_ClearValue(0, 1<<27); //LM4811-clk
    GPIO_ClearValue(0, 1<<28); //LM4811-up/dn
    GPIO_ClearValue(2, 1<<13); //LM4811-shutdn

	/*
	 * Init DAC pin connect
	 * AOUT on P0.26
	 */
	PinCfg.Funcnum = 2;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Pinnum = 26;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);

	/* init DAC structure to default
	 * Maximum	current is 700 uA
	 * First value to AOUT is 0
	 */
	DAC_Init(LPC_DAC);


    /* ChunkID */
    if (sound_8k[cnt] != 'R' && sound_8k[cnt+1] != 'I' &&
        sound_8k[cnt+2] != 'F' && sound_8k[cnt+3] != 'F')
    {
        return -1;
    }
    cnt+=4;

    /* skip chunk size*/
    cnt += 4;

    /* Format */
    cnt+=4;

    /* SubChunk1ID */
    cnt+=4;

    /* skip chunk size, audio format, num channels */
    cnt+= 8;

    sampleRate = (sound_8k[cnt] | (sound_8k[cnt+1] << 8) |
            (sound_8k[cnt+2] << 16) | (sound_8k[cnt+3] << 24));

    if (sampleRate != 8000) {
    	return -1;
    }

    delay = 1000000 / sampleRate;

    cnt+=4;

    /* skip byte rate, align, bits per sample */
    cnt += 8;

    /* SubChunk2ID */
    cnt += 4;

    /* skip chunk size */
    cnt += 4;

    off = cnt;


        cnt = off;
        while(cnt++ < sound_sz)
        {
        	DAC_UpdateValue ( LPC_DAC,(uint32_t)(sound_8k[cnt]));
        	Timer0_us_Wait(delay);
        }

    return 0 ;
}

void check_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while(1);
}
