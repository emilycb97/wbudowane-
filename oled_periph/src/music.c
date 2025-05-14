#include "../headers/music.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_timer.h"
#include <stdint.h>

extern const unsigned char sound_8k[];
extern int sound_sz;

void setupMusic(MUSIC_CONFIG *musicConfig) {
	PINSEL_CFG_Type PinCfg;

	musicConfig->startFromByte = 0;
	musicConfig->sampleRate = 0;
	musicConfig->delay = 0;

	GPIO_SetDir(2, 1 << 0, 1);
	GPIO_SetDir(2, 1 << 1, 1);

	GPIO_SetDir(0, 1 << 27, 1);
	GPIO_SetDir(0, 1 << 28, 1);
	GPIO_SetDir(2, 1 << 13, 1);
	GPIO_SetDir(0, 1 << 26, 1);

	GPIO_ClearValue(0, 1 << 27); //LM4811-clk
	GPIO_ClearValue(0, 1 << 28); //LM4811-up/dn
	GPIO_ClearValue(2, 1 << 13); //LM4811-shutdn

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
	if (sound_8k[musicConfig->startFromByte] != 'R' && sound_8k[musicConfig->startFromByte + 1] != 'I'
			&& sound_8k[musicConfig->startFromByte + 2] != 'F' && sound_8k[musicConfig->startFromByte + 3] != 'F') {
		return -1;
	}
	musicConfig->startFromByte += 4;

	/* skip chunk size*/
	musicConfig->startFromByte += 4;

	/* Format */
	musicConfig->startFromByte += 4;

	/* SubChunk1ID */
	musicConfig->startFromByte += 4;

	/* skip chunk size, audio format, num channels */
	musicConfig->startFromByte += 8;

	musicConfig->sampleRate = (sound_8k[musicConfig->startFromByte] | (sound_8k[musicConfig->startFromByte + 1] << 8)
			| (sound_8k[musicConfig->startFromByte + 2] << 16) | (sound_8k[musicConfig->startFromByte + 3] << 24));

	if (musicConfig->sampleRate != 8000) {
		return -1;
	}

	musicConfig->delay = 1000000 / musicConfig->sampleRate;

	musicConfig->startFromByte += 4;

	/* skip byte rate, align, bits per sample */
	musicConfig->startFromByte += 8;

	/* SubChunk2ID */
	musicConfig->startFromByte += 4;

	/* skip chunk size */
	musicConfig->startFromByte += 4;
}

void playMusic(MUSIC_CONFIG *musicConfig) {
	uint32_t originalStartByte = musicConfig->startFromByte;
	while (musicConfig->startFromByte++ < sound_sz) {
		DAC_UpdateValue( LPC_DAC, (uint32_t) (sound_8k[musicConfig->startFromByte]));
		Timer0_us_Wait(musicConfig->delay);
	}

	return 0;
}

