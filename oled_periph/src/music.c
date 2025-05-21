#include "../headers/music.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_timer.h"
#include <stdint.h>

extern const uint8_t sound_8k[];
extern const uint32_t sound_sz;

void setupMusic(MUSIC_CONFIG *musicConfig)
{
    PINSEL_CFG_Type PinCfg;
    uint32_t gpioMask = 0U;

    if (musicConfig == NULL)
    {
        return;
    }

    musicConfig->startFromByte = 0U;
    musicConfig->sampleRate = 0U;
    musicConfig->delay = 0U;


    /* Configure GPIO pins */
    gpioMask = (1U << 0U);
    GPIO_SetDir(2U, gpioMask, 1U);

    gpioMask = (1U << 1U);
    GPIO_SetDir(2U, gpioMask, 1U);

    gpioMask = (1U << 27U);
    GPIO_SetDir(0U, gpioMask, 1U);
    GPIO_ClearValue(0U, gpioMask);

    gpioMask = (1U << 28U);
    GPIO_SetDir(0U, gpioMask, 1U);
    GPIO_ClearValue(0U, gpioMask);

    gpioMask = (1U << 13U);
    GPIO_SetDir(2U, gpioMask, 1U);
    GPIO_ClearValue(2U, gpioMask);

    gpioMask = (1U << 26U);
    GPIO_SetDir(0U, gpioMask, 1U);

    /* Configure DAC */
    PinCfg.Funcnum = 2U;
    PinCfg.OpenDrain = 0U;
    PinCfg.Pinmode = 0U;
    PinCfg.Pinnum = 26U;
    PinCfg.Portnum = 0U;
    PINSEL_ConfigPin(&PinCfg);

    DAC_Init(LPC_DAC);

    musicConfig->startFromByte = 20U;

    {
        uint32_t rateOffset = musicConfig->startFromByte;
        uint32_t sr0 = (uint32_t)sound_8k[rateOffset];
        uint32_t sr1 = (uint32_t)sound_8k[rateOffset + 1U] << 8U;
        uint32_t sr2 = (uint32_t)sound_8k[rateOffset + 2U] << 16U;
        uint32_t sr3 = (uint32_t)sound_8k[rateOffset + 3U] << 24U;
        musicConfig->sampleRate = sr0 | sr1 | sr2 | sr3;
    }


    musicConfig->delay = 1000000U / musicConfig->sampleRate;
    musicConfig->startFromByte = 44U;
}

void playMusic(MUSIC_CONFIG *musicConfig)
{
    uint32_t currentByte = 0U;

    currentByte = musicConfig->startFromByte;

    while (musicConfig->startFromByte < sound_sz)
    {
        DAC_UpdateValue(LPC_DAC, (uint32_t)sound_8k[musicConfig->startFromByte]);
        Timer0_us_Wait(musicConfig->delay);
        musicConfig->startFromByte++;
    }

    musicConfig->startFromByte = currentByte;
}

