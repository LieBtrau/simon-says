#ifndef MUSIC_H
#define MUSIC_H
#include "Arduino.h"

class Music
{
public:
    Music(byte pinNr);
    ~Music();
    void init();
    void playTone(word freq, word duration);
    void winner_sound(void);
    void playMusic();
private:
    void sing(const word* tones, const byte* tempos, int size);
    void tone(word freq, byte duration);
    byte _pinNr;
    word _tword_m;  // dds tuning word m

};

#endif // MUSIC_H
