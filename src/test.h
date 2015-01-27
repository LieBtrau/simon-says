#ifndef MAIN
#define MAIN
#ifdef __cplusplus
extern "C" {    //define avr-gcc compiled headers & sources here
#endif

void loop();
void setup();
void winner_sound(void);
void buzz(int targetPin, long frequency, long length);
void sing(int *tone, int *tempos, int size, byte melodyPin);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // MAIN

