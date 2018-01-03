// Author:
// Net ID:
// Date:
// Assignment:
//
// Description:
//----------------------------------------------------------------------//

// Description: This file describes functions used by the timer
//----------------------------------------------------------------------//
#ifndef TIMER_H
#define TIMER_H
#include <avr/io.h>

void initTimer0();
void initTimer1();
void delayUs(unsigned int delay);
void refresh(unsigned int seconds);

#endif
