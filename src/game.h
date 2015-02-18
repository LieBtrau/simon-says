#ifndef MAIN
#define MAIN

#include "pitches.h"
#include "music.h"
#include "qtouchadc.h"
#include "TinyDebugSerial.h"
#include <avr/sleep.h>

#ifdef __cplusplus
extern "C" {    //define avr-gcc compiled headers & sources here
#endif
enum{
    CHOICE_OFF=0,
    CHOICE_RED=1,
    CHOICE_BLUE=2,
    CHOICE_YELLOW=4,
    CHOICE_GREEN=8
}CHOICE;
byte CHOICE_NONE=0;

void loop();
void setup();
void attractMode(void);
void setLEDs(byte leds);
boolean play_memory(void);
void playMoves(byte *gameBoard, byte gameRound);
byte wait_for_button(void);
void toner(byte which, int buzz_length_ms);
byte checkButton(void);
void play_winner(void);
void play_loser(void);
void sleepMcu();

#ifdef __cplusplus
} // extern "C"
#endif

#endif // MAIN

