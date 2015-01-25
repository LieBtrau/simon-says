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
#include <Arduino.h>
#include "main.h"
/*
  Turns on an LED on for one second, then off for one second, repeatedly.
*/


// Define the pin where the led is connected
const byte PIN_LED_GREEN=7;
const byte PIN_LED_RED=10;
const byte PIN_LED_ORANGE=9;
const byte PIN_LED_YELLOW=8;
byte iCtr=0;

void setup()
{
    // Initialize Arduino Librairies
    init();
    pinMode(PIN_LED_GREEN, OUTPUT);
    pinMode(PIN_LED_RED, OUTPUT);
    pinMode(PIN_LED_ORANGE, OUTPUT);
    pinMode(PIN_LED_YELLOW, OUTPUT);
}

void loop()
{
    digitalWrite(PIN_LED_GREEN, LOW);
    digitalWrite(PIN_LED_RED, LOW);
    digitalWrite(PIN_LED_ORANGE, LOW);
    digitalWrite(PIN_LED_YELLOW, LOW);
    delay(100);
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
    delay(100);
}



