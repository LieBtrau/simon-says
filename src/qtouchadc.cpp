#include "qtouchadc.h"

QtouchAdc::QtouchAdc(byte sensorPin, byte partnerPin): _sensorPin(sensorPin), _partnerPin(partnerPin)
{

}

QtouchAdc::~QtouchAdc()
{
    ADC_SetVoltageReference(ADC_Reference_VCC);
    ADC_PrescalerSelect(ADC_Prescaler_Value_2);//ADC clock=500kHz, best resolution with 50kHz to 200kHz
    ADC_Enable();
    ADC_SetInputChannel(ADC_Input_ADC0);
    while(ADC_ConversionInProgress());
}

//unsigned int adc1, adc2; // store the avarage of the charge resp. discharge measurement
//int probe_val; // store the resulting touch measurement

//uint16_t touch_probe(uint8_t pin, uint8_t partner, bool dir) {
//  uint8_t mask= _BV(pin) | _BV(partner);

//  DDRC|= mask; // config pins as push-pull output
//  if(dir)
//    PORTC= (PORTC & ~_BV(pin)) | _BV(partner); // set partner high to charge the  s&h cap and pin low to discharge touch probe cap
//  else
//    PORTC= (PORTC & ~_BV(partner)) | _BV(pin); // set pin high to charge the touch probe and pin low to discharge s&h cap cap

//  // charge/discharge s&h cap by connecting it to partner
//  ADMUX = MUX_REF_VCC | partner; // select partner as input to the ADC unit

//  delayMicroseconds(CHARGE_DELAY); // wait for the touch probe and the s&h cap to be fully charged/dsicharged

//  DDRC&= ~mask; // config pins as input
//  PORTC&= ~mask; // disable the internal pullup to make the ports high Z

//  // connect touch probe cap to s&h cap to transfer the charge
//  ADMUX= MUX_REF_VCC | pin; // select pin as ADC input

//  delayMicroseconds(TRANSFER_DELAY); // wait for charge to be transfered

//  // measure
//  ADCSRA|= (1<<ADSC); // start measurement
//  while(ADCSRA & (1<<ADSC)){  } // wait for conversion to complete
//  return ADC; // return conversion result
//}

//void setup() {
//  Serial.begin(9600); // standard serial setup
//  touch_setup();
//}

//void loop() {
//  unsigned long time;
//  time= micros();

//  // 4 measurements are taken and averaged to improve noise immunity
//  for (int i=0; i<4; i++) {
//    // first measurement: charge touch probe, discharge ADC s&h cap, connect the two, measure the volage
//    adc1+= touch_probe(TPIN1, TPIN2, false); // accumulate the results for the averaging

//    // second measurement:discharge touch probe, charge ADC s&h cap, connect the two, measure the volage
//    adc2+= touch_probe(TPIN1, TPIN2, true); // accumulate the results for the averaging
//  }
//  adc1>>=2; // divide the accumulated measurements by 16
//  adc2>>=2;

//  time= micros() - time;

//  // resulting raw touch value
//  probe_val= adc1-adc2; // the value of adc1 (probe charged) gets higher when the probe ist touched, the value of adc2 (s&h charged) gets lower when the probe ist touched, so, it has to be be subtracted to amplify the detection accuracy

//  // calculate the index to the LED fading table
//  int16_t idx= (probe_val-TOUCH_VALUE_BASELINE); // offset probe_val by value of untouched probe
//  if(idx<0) idx= 0; // limit the index!!!
//  idx/= TOUCH_VALUE_SCALE; // scale the index
//  if(idx>31) idx= 31; // limit the index!!!

//  // print some info to the serial
//  Serial.print(time);
//  Serial.print('|');
//  Serial.print(adc1);
//  Serial.print('|');
//  Serial.print(adc2);
//  Serial.print('|');
//  Serial.print(probe_val);
//  Serial.print('|');
//  Serial.println(idx);


//  adc1= 0; // clear the averaging variables for the next run
//  adc2= 0;
//  delay(10); // take 100 measurements per second
//}
