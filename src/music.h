#ifndef MUSIC_H
#define MUSIC_H
#include "Arduino.h"

class Music
{
public:
    Music(byte pinNr);
    ~Music();
    void playTone(word freq, word duration);
    void winner_sound(void);
    void playMusic();
private:
    void sing(const word* tones, const byte* tempos, int size);
    byte _pinNr;
};

#endif // MUSIC_H
