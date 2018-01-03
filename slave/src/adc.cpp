// Author:
// Net ID:
// Date:
// Assignment:
//
// Description:
//----------------------------------------------------------------------//
#include "adc.h"
#include <avr/io.h>
//  Analog to Digital Converter
void initADC0(){
  //  set AVCC as positive reference
  ADMUX |= (1 << REFS0);
  //  Disables ADC0 input pin as digital
  DIDR0 |= (1 << ADC0D);
  //  ADC Auto Trigger Source
  // Turns on ADC, starts conversion mode (free running), enables auto trigger, enables interrupt
  ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);// | (1 << ADIE);
}
//comment'
