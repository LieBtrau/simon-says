#ifndef QTOUCHADC_H
#define QTOUCHADC_H
#include "Arduino.h"
#include "core_adc.h"

class QtouchAdc
{
public:
    QtouchAdc(byte sensorPin, byte partnerPin);
    ~QtouchAdc();
private:
    // ADC constants
    static const byte ADMUX_MASK   =0b00001111;    // mask the mux bits in the ADMUX register
    static const byte MUX_GND      =0b00001111;    // mux value for connecting the ADC unit internally to GND
    static const byte MUX_REF_VCC  =0b01000000;    // value to set the ADC reference to Vcc
    static const byte CHARGE_DELAY =5;             // time it takes for the capacitor to get charged/discharged in microseconds
    static const byte TRANSFER_DELAY=5;            // time it takes for the capacitors to exchange charge
    byte _sensorPin;
    byte _partnerPin;
};

#endif // QTOUCHADC_H
