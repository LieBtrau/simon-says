#ifndef MUSIC_H
#define MUSIC_H
#include "Arduino.h"


//Octave number ranging from C(-1) to C(9): 11 octaves: 4bit
const word OCTAVEMASK=0xF;
typedef enum{
    O9, O8, O7, O6, O5, O4, O3, O2, O1, O0, OMIN1
}OCTAVES;

//12-tone chromatic scale: 4bit
const word NOTEMASK=0xF0;
typedef enum{
    N_OFF=0,
    N_C=0x10,
    N_CS=0x20,
    N_D=0x30,
    N_DS=0x40,
    N_E=0x50,
    N_F=0x60,
    N_FS=0X70,
    N_G=0x80,
    N_GS=0x90,
    N_A=0xA0,
    N_AS=0xB0,
    N_B=0xC0
}NOTES;


//length of notes could be expressed in 5 bits
const word LENGTHMASK=0xF00;
typedef enum{
    L8=0x000, L4=0x100, L2=0x200, L1=0x300, L1_2=0x400, L1_4=0x500, L1_8=0x600, L1_16=0x700,
    L1_32=0x800, L1_64=0x900, L1_128=0xA00
}NOTE_LENGTH;
const word _D=0x1000; //dotted note length = length + 1/2 length

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
    void sing(const word* tones, int size);
    void tone(word freq, word duration);
    byte _pinNr;
    word _tword_m;  // dds tuning word m

};

#endif // MUSIC_H
