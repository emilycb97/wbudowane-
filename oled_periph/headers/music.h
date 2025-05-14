#ifndef MUSIC_H_
#define MUSIC_H_
#include <stdint.h>

void setupMusic();
void playMusic();

typedef struct {
    uint32_t startFromByte;
    uint32_t sampleRate;
    uint32_t delay;
} MUSIC_CONFIG;

#endif
