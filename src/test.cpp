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
#include "test.h"

/*
  Turns on an LED on for one second, then off for one second, repeatedly.
*/

// Define the pin where the led is connected
const byte PIN_LED_D1=4;
const byte PIN_LED_D2=0;
const byte PIN_LED_D3=1;
const byte PIN_LED_D4=2;
const byte PIN_SPEAKER=3;
byte iCtr=0;
TinyDebugSerial mySerial = TinyDebugSerial();
Music ms(PIN_SPEAKER);
//returns for bare copper: 72 untouched to 860 touched
//returns for copper covered with plastic tape: 20 untouched to 320 touched
//Touch limit values are average of untouched and touched conditions.  These are determined by testing each pad.
QtouchAdc qtTP1(ADC_Input_ADC0, ADC_Input_ADC1, 200);
QtouchAdc qtTP2(ADC_Input_ADC1, ADC_Input_ADC2, 200);
QtouchAdc qtTP3(ADC_Input_ADC2, ADC_Input_ADC3, 200);
QtouchAdc qtTP4(ADC_Input_ADC3, ADC_Input_ADC0, 200);

void setup()
{
    // Initialize Arduino Librairies
    init();
    pinMode(PIN_LED_D1, OUTPUT);
    pinMode(PIN_LED_D2, OUTPUT);
    pinMode(PIN_LED_D3, OUTPUT);
    pinMode(PIN_LED_D4, OUTPUT);
    pinMode(PIN_SPEAKER, OUTPUT);
    ms.playMusic();
}

void loop()
{
    int value;
    digitalWrite(PIN_LED_D3,qtTP1.isButtonTouched(value) ? HIGH : LOW);
    digitalWrite(PIN_LED_D2,qtTP2.isButtonTouched(value) ? HIGH : LOW);
    digitalWrite(PIN_LED_D1,qtTP3.isButtonTouched(value) ? HIGH : LOW);
    digitalWrite(PIN_LED_D4,qtTP4.isButtonTouched(value) ? HIGH : LOW);
    if(qtTP1.isButtonTouched(value)){
        ms.playTone(2794, 100);
    }
    if(qtTP2.isButtonTouched(value)){
        ms.playTone(2093, 100);
    }
    if(qtTP3.isButtonTouched(value)){
        ms.playTone(2349, 100);
    }
    if(qtTP4.isButtonTouched(value)){
        ms.playTone(2637, 100);
    }
}
