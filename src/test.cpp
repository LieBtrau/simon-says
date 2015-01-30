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
#include "debugsend.h"
#include "music.h"

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
DebugSend ds(4);
Music ms(PIN_SPEAKER);


void setup()
{
    // Initialize Arduino Librairies
    init();
    pinMode(PIN_LED_GREEN, OUTPUT);
    pinMode(PIN_LED_RED, OUTPUT);
    pinMode(PIN_LED_ORANGE, OUTPUT);
    pinMode(PIN_LED_YELLOW, OUTPUT);
    pinMode(PIN_SPEAKER, OUTPUT);
    ms.playMusic();
}

void loop()
{
    //digitalWrite(PIN_LED_GREEN, LOW);
    digitalWrite(PIN_LED_RED, LOW);
    digitalWrite(PIN_LED_ORANGE, LOW);
    digitalWrite(PIN_LED_YELLOW, LOW);
    switch ((iCtr++)%4) {
    case 0:
        //digitalWrite(PIN_LED_GREEN, HIGH);
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
}
