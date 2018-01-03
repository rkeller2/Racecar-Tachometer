/*************************************************************************
Author: Robert Keller, Gavin Daniel
Date: 4/4/2017
Assignment: Digital Tachometer in C/C++

Project Description: This project interfaces an Arduino MEGA 2560 with an infrared 
LED comparator circuit via i2c communication protocol to calculate and display the 
instantaneous RPM of an accelerating racecar on an LCD screen
**********************************************************************/

// File Description: This file describes functions used by the timer
//----------------------------------------------------------------------//

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void initTimer1();
void delayUs(unsigned int delay);
void refresh(unsigned int seconds);

#endif
