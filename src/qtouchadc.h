#ifndef QTOUCHADC_H
#define QTOUCHADC_H
#include "Arduino.h"
#include "core_adc.h"

class QtouchAdc
{
public:
    QtouchAdc(adc_ic_t sensorPinADC, adc_ic_t partnerPinADC, word wTouchLimit);
    ~QtouchAdc();
    bool isButtonTouched(int &iTouchValue);
    int touchProbe2();

private:
    // ADC constants
    static const byte TRANSFER_DELAY=30;            // time it takes for the capacitors to exchange charge
    adc_ic_t _sensorBitnr;
    adc_ic_t _partnerBitnr;
    int _iTouchLimit;
    byte _pinMask;
};

#endif // QTOUCHADC_H
