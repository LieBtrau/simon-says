#ifndef QTOUCHADC_H
#define QTOUCHADC_H
#include "Arduino.h"
#include "core_adc.h"

class QtouchAdc
{
public:
    QtouchAdc(adc_ic_t sensorPinADC, adc_ic_t partnerPinADC, byte touchLimit);
    ~QtouchAdc();
    bool isButtonTouched();
    void touchProbe2(word &diff, unsigned long &sum);
    void debug(word &diff, unsigned long &avg);
private:
    // ADC constants
    static const byte TRANSFER_DELAY=30;            // time it takes for the capacitors to exchange charge
    adc_ic_t _sensorBitnr;
    adc_ic_t _partnerBitnr;
    byte _pinMask;
    byte _yTouchLimit;
};

#endif // QTOUCHADC_H
