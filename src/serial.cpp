/*************************************************************************
Author: Robert Keller, Gavin Daniel
Date: 4/4/2017
Assignment: Digital Tachometer in C/C++

Project Description: This project interfaces an Arduino MEGA 2560 with an infrared 
LED comparator circuit via i2c communication protocol to calculate and display the 
instantaneous RPM of an accelerating racecar on an LCD screen
**********************************************************************/
#include "serial.h"
#include <avr/io.h>

void initSerial0(){
  UCSR0B |= (1 << RXCIE0 | 1 << TXCIE0 | 1 << RXEN0 | 1 << TXEN0);
  UCSR0B &= ~(1 << UCSZ02);
  UBRR0L = 103;
}
