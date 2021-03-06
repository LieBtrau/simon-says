/*
Based on code from Spark Fun Electronics, Nathan Seidle
*/

// Access to the Arduino Libraries
#include "game.h"
// Define game parameters
const byte ROUNDS_TO_WIN=13;        //Number of rounds to succesfully remember before you win. 13 is do-able.
const word ENTRY_TIME_LIMIT=5000;   //Amount of time to press a button before game times out. 3000ms = 3 sec

// Define the pin where the led is connected
const byte LED_RED=0;
const byte LED_BLUE=1;
const byte LED_YELLOW=2;
const byte LED_GREEN=3;

const byte PIN_SPEAKER=5;
TinyDebugSerial mySerial = TinyDebugSerial();
Music ms(PIN_SPEAKER);
//Touch limit values are average of untouched and touched conditions.  These are determined by testing each pad.
QtouchAdc qtBLUE(ADC_Input_ADC0, ADC_Input_ADC1, 15);
QtouchAdc qtRED(ADC_Input_ADC1, ADC_Input_ADC2, 15);
QtouchAdc qtGREEN(ADC_Input_ADC2, ADC_Input_ADC3, 15);
QtouchAdc qtYELLOW(ADC_Input_ADC3, ADC_Input_ADC0, 15);

void setup()
{
    // Initialize Arduino Librairies
    init();
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    ms.init();
    DIDR0=0xFF;
    mySerial.begin(9600);
    //ms.playMusic();
}

//void loop(){
//    wait_for_button();
//}

//void loop()
//{
//    word diff;
//    unsigned long avg;
//    qtRED.debug(diff, avg);
//    mySerial.print(avg/diff);
//    mySerial.print(" ");
//    qtGREEN.debug(diff, avg);
//    mySerial.print(avg/diff);
//    mySerial.print(" ");

//    qtBLUE.debug(diff, avg);
//    mySerial.print(avg/diff);
//    mySerial.print(" ");

//    qtYELLOW.debug(diff, avg);
//    mySerial.print(avg/diff);
//    mySerial.println(" ");
//    delay(500);
//}


void loop()
{
    attractMode(); // Blink lights while waiting for user to press a button

    // Indicate the start of game play
    setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW); // Turn all LEDs on
    delay(1000);
    setLEDs(CHOICE_OFF); // Turn off LEDs
    delay(250);
    if(checkButton()==CHOICE_RED){
        ms.playMusic();
    }

    // Play memory game and handle result
    if (play_memory() == true)
        play_winner(); // Player won, play winner tones
    else
        play_loser(); // Player lost, play loser tones
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//The following functions are related to game play only

// Play the regular memory game
// Returns 0 if player loses, or 1 if player wins
boolean play_memory(void)
{
    // Game state variables
    byte gameBoard[32]; //Contains the combination of buttons as we advance
    byte gameRound = 0; //Counts the number of succesful rounds the player has made it through

    randomSeed(millis()); // Seed the random generator with random amount of millis()
    
    for(gameRound=0; gameRound < ROUNDS_TO_WIN; gameRound++)
    {
        gameBoard[gameRound] = 1<<random(0, 4); //min (included), max (exluded) // Add this new button to the game array
        playMoves(gameBoard, gameRound); // Play back the current game board
        // Then require the player to repeat the sequence.
        for (byte currentMove = 0 ; currentMove <= gameRound ; currentMove++)
        {
            byte choice = wait_for_button(); // See what button the user presses
            if (choice == 0) return false; // If wait timed out, player loses
            if (choice != gameBoard[currentMove]) return false; // If the choice is incorect, player loses
        }
        delay(1000); // Player was correct, delay before playing moves
    }
    return true; // Player made it through all the rounds to win!
}

// Plays the current contents of the game moves
void playMoves(byte* gameBoard, byte gameRound)
{
    for (byte currentMove = 0 ; currentMove <= gameRound ; currentMove++)
    {
        toner(gameBoard[currentMove], 150);
        // Wait some amount of time between button playback
        // Shorten this to make game harder
        delay(150); // 150 works well. 75 gets fast.
    }
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//The following functions control the hardware

// Lights a given LEDs
// Pass in a byte that is made up from CHOICE_RED, CHOICE_YELLOW, etc
void setLEDs(byte leds)
{
    digitalWrite(LED_RED, (leds & CHOICE_RED) ? HIGH : LOW);
    digitalWrite(LED_GREEN, (leds & CHOICE_GREEN) ? HIGH : LOW);
    digitalWrite(LED_YELLOW, (leds & CHOICE_YELLOW) ? HIGH : LOW);
    digitalWrite(LED_BLUE, (leds & CHOICE_BLUE) ? HIGH : LOW);
}

// Wait for a button to be pressed.
// Returns one of LED colors (LED_RED, etc.) if successful, 0 if timed out
byte wait_for_button(void)
{
    long startTime = millis(); // Remember the time we started the this loop
    
    while ( (millis() - startTime) < ENTRY_TIME_LIMIT) // Loop until too much time has passed
    {
        byte button = checkButton();
        if (button != CHOICE_NONE)
        {
            toner(button, 150); // Play the button the user just pressed
            while(checkButton() != CHOICE_NONE) ;  // Now let's wait for user to release button
            delay(10); // This helps with debouncing and accidental double taps
            return button;
        }
    }
    return CHOICE_NONE; // If we get here, we've timed out!
}

// Returns a '1' bit in the position corresponding to CHOICE_RED, CHOICE_GREEN, etc.
byte checkButton(void)
{
    if(qtRED.isButtonTouched()){
        return CHOICE_RED;
    }
    if(qtBLUE.isButtonTouched()){
        return CHOICE_BLUE;
    }
    if(qtYELLOW.isButtonTouched()){
        return CHOICE_YELLOW;
    }
    if(qtGREEN.isButtonTouched()){
        return CHOICE_GREEN;
    }
    return(CHOICE_OFF); // If no button is pressed, return none
}

// Light an LED and play tone
// Red, upper left:     440Hz - 2.272ms - 1.136ms pulse
// Green, upper right:  880Hz - 1.136ms - 0.568ms pulse
// Blue, lower left:    587.33Hz - 1.702ms - 0.851ms pulse
// Yellow, lower right: 784Hz - 1.276ms - 0.638ms pulse
void toner(byte which, int buzz_length_ms)
{
    setLEDs(which); //Turn on a given LED
    
    //Play the sound associated with the given LED
    switch(which)
    {
    case CHOICE_RED:
        ms.playTone(1136, buzz_length_ms);
        break;
    case CHOICE_GREEN:
        ms.playTone(568, buzz_length_ms);
        break;
    case CHOICE_BLUE:
        ms.playTone(851, buzz_length_ms);
        break;
    case CHOICE_YELLOW:
        ms.playTone(638, buzz_length_ms);
        break;
    }
    
    setLEDs(CHOICE_OFF); // Turn off all LEDs
}

// Play the winner sound and lights
void play_winner(void)
{
    setLEDs(CHOICE_GREEN | CHOICE_BLUE);
    ms.winner_sound();
    setLEDs(CHOICE_RED | CHOICE_YELLOW);
    ms.winner_sound();
    setLEDs(CHOICE_GREEN | CHOICE_BLUE);
    ms.winner_sound();
    setLEDs(CHOICE_RED | CHOICE_YELLOW);
    ms.winner_sound();
}


// Play the loser sound/lights
void play_loser(void)
{
    setLEDs(CHOICE_RED | CHOICE_GREEN);
    ms.playTone(1500, 255);
    
    setLEDs(CHOICE_BLUE | CHOICE_YELLOW);
    ms.playTone(1500, 255);
    
    setLEDs(CHOICE_RED | CHOICE_GREEN);
    ms.playTone(1500, 255);
    
    setLEDs(CHOICE_BLUE | CHOICE_YELLOW);
    ms.playTone(1500, 255);
}

// Show an "attract mode" display while waiting for user to press button.
void attractMode(void)
{
    const unsigned long SLEEPTIMEOUT=30000;
    unsigned long ulStartTime=millis();
    while(millis()-ulStartTime < SLEEPTIMEOUT)
    {
        setLEDs(CHOICE_RED);
        delay(100);
        if (checkButton() != CHOICE_NONE) return;
        
        setLEDs(CHOICE_BLUE);
        delay(100);
        if (checkButton() != CHOICE_NONE) return;
        
        setLEDs(CHOICE_GREEN);
        delay(100);
        if (checkButton() != CHOICE_NONE) return;
        
        setLEDs(CHOICE_YELLOW);
        delay(100);
        if (checkButton() != CHOICE_NONE) return;
    }
    sleepMcu();
}

void sleepMcu(){
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    cli();
    //Try to limit current consumption as much as possible by turning off as much as possible
    for(byte i=0;i<=10;i++){
        pinMode(i, INPUT);
    }
    bitClear(ADCSRA, ADEN); //disable ADC
    bitSet(ACSR, ACD); //disable Analog comparator
    DIDR0=0xFF;//disable digital input buffer for analog pins
    PRR=0x0F;
    MCUCR |= _BV(BODS) | _BV(BODSE);
    sleep_enable();
    sleep_cpu();
    //Sleep forever. (until power is cycled, or a reset condition occurs)
}
