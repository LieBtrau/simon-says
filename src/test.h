#ifndef MAIN
#define MAIN

#include "pitches.h"
#include "music.h"
#include "qtouchadc.h"
#include "TinyDebugSerial.h"

#ifdef __cplusplus
extern "C" {    //define avr-gcc compiled headers & sources here
#endif
enum{
    CHOICE_OFF=0,
    CHOICE_RED=1,
    CHOICE_GREEN=2,
    CHOICE_BLUE=4,
    CHOICE_YELLOW=8
}CHOICE;
byte CHOICE_NONE=0;

void loop();
void setup();
void attractMode(void);
void setLEDs(byte leds);
boolean play_memory(void);
void playMoves(void);
byte wait_for_button(void);
void toner(byte which, int buzz_length_ms);
byte checkButton(void);
void play_winner(void);
void play_loser(void);





#ifdef __cplusplus
} // extern "C"
#endif

#endif // MAIN

