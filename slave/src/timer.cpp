// Author:
// Net ID:
// Date:
// Assignment:
//
// Description:
//----------------------------------------------------------------------//
#include "timer.h"
#define SAMPLE_RATE 10

void initTimer1(){
  // set the timer mode to be "CTC"
  TCCR1A &= ~(1 << WGM10 | 1 << WGM11);
  TCCR1B &= ~(1 << WGM13);
  TCCR1B |= (1 << WGM12);
}

void delayUs(unsigned int delay){
  // clear the timer
  TCNT1H = 0; //initialize counter value to 0
  TCNT1L = 0;
  // calculate the TOP value and assign it to OCR1A
  unsigned int ticks = (2*delay); // 16M / 8 (ps) / 2M / 1M (1us) = 2 - 1 = 1 tick
    OCR1AH = ticks >> 8; //xxxxxxxxxYYYYYYYYY;
    OCR1AL = ticks & 0x00FF;
  // Turn on the timer w/ 8 prescalar (clk/8)
  TCCR1B &= ~(1 << CS10);
  TCCR1B |= (1 << CS11);
  TCCR1B &= ~(1 << CS12);
  // Do nothing while the OCF1A flag is not up
  while (!(TIFR1 & (1 << OCF1A)) ){
    // Do Nothing
  }
  // Clear the OCF1A flag
  TIFR1 |= (1 << OCF1A);
  // Turn off the timer
  TCCR1B &= ~(1 << CS10);
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS12);
}

void refresh(unsigned int seconds){
  unsigned int i = 0; // clear
  unsigned int delay_length = 0; //clear

  delay_length = SAMPLE_RATE*seconds;

  for (i = 0; i < delay_length; i++){
    delayUs(1000);
  }
}
