//Adapted from http://wiki.sgmk-ssam.ch/index.php/CapSense_%28QTouchADC%29
//nice explanation of working principle of QTouchAdc can be found on:
//  http://tuomasnylund.fi/drupal6/content/capacitive-touch-sensing-avr-and-single-adc-pin

#include "qtouchadc.h"

QtouchAdc::QtouchAdc(adc_ic_t sensorPinADC, adc_ic_t partnerPinADC, byte touchLimit):
    _sensorBitnr(sensorPinADC), _partnerBitnr(partnerPinADC), _yTouchLimit(touchLimit)
{
    _pinMask=_BV(_sensorBitnr) | _BV(_partnerBitnr);
}

QtouchAdc::~QtouchAdc()
{
    ADC_SetVoltageReference(ADC_Reference_VCC);
    ADC_PrescalerSelect(ADC_Prescaler_Value_8);//ADC clock=125kHz, best resolution with 50kHz to 200kHz
    ADC_Enable();
    ADC_SetInputChannel(ADC_Input_ADC0);
    while(ADC_ConversionInProgress());
}

void QtouchAdc::debug(word &diff, unsigned long &avg){
    touchProbe2(diff, avg);
}

bool QtouchAdc::isButtonTouched(){
    word diff;
    unsigned long avg;
    touchProbe2(diff, avg);
    return avg/diff < _yTouchLimit;
}

//Don't try to use digitalWrite & pinMode, they influence the measurement result
void QtouchAdc::touchProbe2(word& diff, unsigned long &sum){
    const byte CTR=2;//pick a value from 0 to 7 for the loop counter.  Number of loops is 2^CTR
    int idiff=0;
    sum=0;

    for(byte i=0;i<_BV(CTR);i++){
        ADC_SetInputChannel(_partnerBitnr);
        bitSet(PORTA, (i&1)==0 ? _sensorBitnr : _partnerBitnr);
        DDRA|=_pinMask;

        delayMicroseconds(TRANSFER_DELAY);
        DDRA&=~_pinMask;
        PORTA&=~_pinMask;
        ADC_SetInputChannel(_sensorBitnr);
        ADC_StartConversion();
        while(ADC_ConversionInProgress());
        int adcVal=ADC_GetDataRegister();
        idiff=((i&1)==0 ? idiff+adcVal : idiff-adcVal);
        sum+=adcVal;
    }
    diff=abs(idiff)>>(CTR-1);
}
