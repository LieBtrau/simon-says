/*
Arduino template for Qt
Downloaded from http://www.lucidarme.me

In the menu Tools>Option set in the Terminal field : xterm -e

Set the following parameters in the project tab :
Build directory : add /src at the end of the path
Build steps : make all
Clean steps : make clean


*/


// Access to the Arduino Libraries
#include "Arduino.h"
#include "test.h"
#include "pitches.h"

/*
  Turns on an LED on for one second, then off for one second, repeatedly.
*/

// Define the pin where the led is connected
const byte PIN_LED_GREEN=4;
const byte PIN_LED_RED=0;
const byte PIN_LED_ORANGE=1;
const byte PIN_LED_YELLOW=2;
const byte PIN_SPEAKER=3;
byte iCtr=0;

//Mario main theme melody
int melody[] = {
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
int tempo[] = {
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

//Underworld melody
int underworld_melody[] = {
    NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
    NOTE_AS3, NOTE_AS4, 0,
    0,
    NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
    NOTE_AS3, NOTE_AS4, 0,
    0,
    NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
    NOTE_DS3, NOTE_DS4, 0,
    0,
    NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
    NOTE_DS3, NOTE_DS4, 0,
    0, NOTE_DS4, NOTE_CS4, NOTE_D4,
    NOTE_CS4, NOTE_DS4,
    NOTE_DS4, NOTE_GS3,
    NOTE_G3, NOTE_CS4,
    NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
    NOTE_GS4, NOTE_DS4, NOTE_B3,
    NOTE_AS3, NOTE_A3, NOTE_GS3,
    0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
    12, 12, 12, 12,
    12, 12, 6,
    3,
    12, 12, 12, 12,
    12, 12, 6,
    3,
    12, 12, 12, 12,
    12, 12, 6,
    3,
    12, 12, 12, 12,
    12, 12, 6,
    6, 18, 18, 18,
    6, 6,
    6, 6,
    6, 6,
    18, 18, 18, 18, 18, 18,
    10, 10, 10,
    10, 10, 10,
    3, 3, 3
};

void setup()
{
    // Initialize Arduino Librairies
    init();
    pinMode(PIN_LED_GREEN, OUTPUT);
    pinMode(PIN_LED_RED, OUTPUT);
    pinMode(PIN_LED_ORANGE, OUTPUT);
    pinMode(PIN_LED_YELLOW, OUTPUT);
    pinMode(PIN_SPEAKER, OUTPUT);
}

void loop()
{

    digitalWrite(PIN_LED_GREEN, LOW);
    digitalWrite(PIN_LED_RED, LOW);
    digitalWrite(PIN_LED_ORANGE, LOW);
    digitalWrite(PIN_LED_YELLOW, LOW);
    switch ((iCtr++)%4) {
    case 0:
        digitalWrite(PIN_LED_GREEN, HIGH);
        break;
    case 1:
        digitalWrite(PIN_LED_RED, HIGH);
        break;
    case 2:
        digitalWrite(PIN_LED_ORANGE, HIGH);
        break;
    case 3:
        digitalWrite(PIN_LED_YELLOW, HIGH);
        break;
    default:
        break;
    }
    //sing the tunes
    //sing(melody, tempo,sizeof(melody) / sizeof(int),PIN_SPEAKER);
    sing(underworld_melody, underworld_tempo, sizeof(underworld_melody) / sizeof(int),PIN_SPEAKER);
}

// Play the winner sound
// This is just a unique (annoying) sound we came up with, there is no magic to it
void winner_sound(void)
{
    // Toggle the buzzer at various speeds
    for (byte x = 250 ; x > 70 ; x--)
    {
        for (byte y = 0 ; y < 3 ; y++)
        {
            digitalWrite(PIN_SPEAKER, LOW);
            delayMicroseconds(x);

            digitalWrite(PIN_SPEAKER, HIGH);
            delayMicroseconds(x);
        }
    }
}

void sing(int* tones, int* tempos, int size, byte melodyPin) {
    for (int thisNote = 0; thisNote < size; thisNote++) {

        // to calculate the note duration, take one second
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / tempos[thisNote];

        tone(melodyPin, tones[thisNote], noteDuration);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);

        // stop the tone playing:
        tone(melodyPin, 0, noteDuration);
    }
}

void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000 / frequency/16; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 2000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
}

