#ifndef MUSIC_H_
#define MUSIC_H_

#include <stdint.h>
/* Music configuration structure */
typedef struct {
    uint32_t startFromByte;  /* Starting byte position in audio data */
    uint32_t sampleRate;     /* Audio sample rate in Hz */
    uint32_t delay;          /* Delay between samples in microseconds */
} MUSIC_CONFIG;

/* Function declarations with full prototypes */
void setupMusic(MUSIC_CONFIG *musicConfig);
void playMusic(MUSIC_CONFIG *musicConfig);



#endif /* MUSIC_H_ */
