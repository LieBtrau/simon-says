#include "music.h"
#include "avr/pgmspace.h"
#include "pitches.h"
#include "core_timers.h"

//Octave 9 frequencies
//                     C9    C#9,  D9    D#9   E9     F9     F#9    G9     G#9    A9     A#9    B9
const word freqs[]={0, 8372, 8870, 9397, 9956, 10548, 11175, 11840, 12544, 13290, 14080, 14917, 15804};

//Super Mario Overworld theme by Koji Kondo
const word melody1[] PROGMEM = {
    N_OFF|L1_8, N_E|O7|L1_8, N_E|O7|L1_4, N_OFF|L1_8, N_E|O7|L1_4, N_OFF|L1_8, N_C|O7|L1_8, N_E|O7|L1_4, N_OFF|L1_8,
    N_G|O7|L1_4, N_OFF|L1_8, N_OFF|L1_4, N_G|O6|L1_4, N_OFF|L1_4, N_OFF|L1_8, N_OFF|L1_4,
};

const word melody2[] PROGMEM = {
    N_OFF|L1_8,N_C|O7|L1_8, N_OFF|L1_4, N_G|O6|L1_8, N_OFF|L1_4, N_E|O6|L1_8,N_OFF|L1_8,
    N_OFF|L1_8,N_A|O6|L1_8, N_OFF|L1_8, N_B|O6|L1_8, N_OFF|L1_8, N_AS|O6|L1_8, N_A|O6|L1_8,N_OFF|L1_8,
    N_G|O6|L1_8, N_OFF|L1_8, N_E|O7|L1_8, N_OFF|L1_8, N_G|O7|L1_8, N_OFF|L1_8, N_A|O7|L1_8, N_OFF|L1_8, N_F|O7|L1_8, N_G|O7|L1_8,
    N_OFF|L1_8, N_E|O7|L1_8, N_OFF|L1_8,  N_C|O7|L1_8, N_D|O7|L1_8,
    N_B|O6|L1_8, N_OFF|L1_4,
};

const word melody3[] PROGMEM = {
    N_OFF|L1_4, N_G|O7|L1_8, N_FS|O7|L1_8, N_F|O7|L1_8, N_DS|O7|L1_4, N_OFF|L1_8, N_E|O7|L1_8,
    N_OFF|L1_8, N_GS|O6|L1_8, N_A|O6|L1_8, N_C|O7|L1_8, N_OFF|L1_8, N_A|O6|L1_8, N_C|O7|L1_8, N_D|O7|L1_8
};

const word melody4[] PROGMEM = {
    N_OFF|L1_4, N_G|O7|L1_8, N_FS|O7|L1_8, N_F|O7|L1_8, N_DS|O7|L1_4, N_OFF|L1_8, N_E|O7|L1_8,
    N_OFF|L1_8, N_C|O8|L1_8, N_OFF|L1_8, N_C|O8|L1_4, N_C|O8|L1_8, N_OFF|L1_8, N_OFF|L1_4,
};
const word melody5[] PROGMEM = {
    N_OFF|L1_4, N_DS|O7|L1_4,  N_OFF|L1_8, N_OFF|L1_8, N_D|O7|L1_4, N_OFF|L1_4, N_C|O7|L1_2,
    N_OFF|L1_8, N_OFF|L1_4, N_OFF|L1_2
};

void Music::sing(const word* tones, int size) {
    for (int thisNote = 0; thisNote < size; thisNote++)
    {
        word note=pgm_read_word(&tones[thisNote]);
        word noteDuration = 2000U;

        //Calculate notelength
        noteDuration>>=(note & LENGTHMASK)>>8;
        if(note & _D){
            noteDuration+=noteDuration>>1;
        }
        //Calculate frequency
        word frequency=freqs[(note & NOTEMASK)>>4];
        frequency>>=(note & OCTAVEMASK);
        tone(frequency, noteDuration);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration seems to work well:
        delay(200);
    }
}


Music::Music(byte pinNr):_pinNr(pinNr)
{

}

Music::~Music()
{

}

void Music::playTone(word freq, word duration){
    tone(freq, duration);
}

void Music::playMusic(){
    sing(melody2, sizeof(melody2)/sizeof(word));
    sing(melody2, sizeof(melody2)/sizeof(word));
    sing(melody3, sizeof(melody3)/sizeof(word));
    sing(melody4, sizeof(melody4)/sizeof(word));
    sing(melody3, sizeof(melody3)/sizeof(word));
    sing(melody5, sizeof(melody5)/sizeof(word));
}

// Play the winner sound
// This is just a unique (annoying) sound we came up with, there is no magic to it
void Music::winner_sound(void)
{
    // Toggle the buzzer at various speeds
    for (byte x = 250 ; x > 70 ; x--)
    {
        for (byte y = 0 ; y < 3 ; y++)
        {
            digitalWrite(_pinNr, LOW);
            delayMicroseconds(x);

            digitalWrite(_pinNr, HIGH);
            delayMicroseconds(x);
        }
    }
}

void Music::tone(word freq, word duration){
    //focr=fclk/(N*(1+TOP)) => TOP = fclk / (focr * N) - 1 = 1MHz / (freq*1)-1
    word ocrA;
    if(freq)
    {
        ocrA=1e6/freq-1;
        Timer1_SetOutputCompareMatchA(ocrA);
        Timer1_SetOutputCompareMatchB(ocrA>>1);     //Set OCRB to OCRA/2 to generate 50% duty cycle
        Timer1_SetCompareOutputModeB(Timer1_Clear); //Connect OCRB to output 5
    }
    delay(duration);
    Timer1_SetCompareOutputModeB(Timer1_Disconnected);//Disconnect OCRB from output 5
}

void Music::init(){
    pinMode(_pinNr, OUTPUT);
    Timer1_ClockSelect(Timer1_Prescale_Value_1);
    Timer1_SetWaveformGenerationMode(Timer1_Fast_PWM_OCR);
    Timer1_SetCompareOutputModeB(Timer1_Disconnected);
}
