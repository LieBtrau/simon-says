#include "music.h"
#include "avr/pgmspace.h"
#include "pitches.h"

//Mario main theme melody
const word melody[] PROGMEM = {
    NOTE_E7, NOTE_E7, 0, NOTE_E7,
    0, NOTE_C7, NOTE_E7, 0,
    NOTE_G7, 0, 0,  0,
    NOTE_G6, 0, 0, 0,

    NOTE_C7, 0, 0, NOTE_G6,
    0, 0, NOTE_E6, 0,
    0, NOTE_A6, 0, NOTE_B6,
    0, NOTE_AS6, NOTE_A6, 0,

    NOTE_G6, NOTE_E7, NOTE_G7,
    NOTE_A7, 0, NOTE_F7, NOTE_G7,
    0, NOTE_E7, 0, NOTE_C7,
    NOTE_D7, NOTE_B6, 0, 0,

    NOTE_C7, 0, 0, NOTE_G6,
    0, 0, NOTE_E6, 0,
    0, NOTE_A6, 0, NOTE_B6,
    0, NOTE_AS6, NOTE_A6, 0,

    NOTE_G6, NOTE_E7, NOTE_G7,
    NOTE_A7, 0, NOTE_F7, NOTE_G7,
    0, NOTE_E7, 0, NOTE_C7,
    NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
const byte tempo[] PROGMEM = {
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    9, 9, 9,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    9, 9, 9,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,
};

Music::Music(byte pinNr):_pinNr(pinNr)
{

}

Music::~Music()
{

}

void Music::playTone(word freq, word duration){
    tone(_pinNr, freq, duration);
}

void Music::playMusic(){
    sing(melody, tempo, 78);
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

void Music::sing(const word* tones, const byte* tempos, int size) {
    for (int thisNote = 0; thisNote < size; thisNote++) {

        // to calculate the note duration, take one second
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / pgm_read_byte(&tempos[thisNote]);

        tone(_pinNr, pgm_read_word(&tones[thisNote]), noteDuration);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);

        // stop the tone playing:
        tone(_pinNr, 0, noteDuration);
    }
}
