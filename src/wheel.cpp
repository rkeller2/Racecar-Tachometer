/*************************************************************************
Author: Robert Keller, Gavin Daniel
Date: 4/4/2017
Assignment: Digital Tachometer in C/C++

Project Description: This project interfaces an Arduino MEGA 2560 with an infrared 
LED comparator circuit via i2c communication protocol to calculate and display the 
instantaneous RPM of an accelerating racecar on an LCD screen
**********************************************************************/
#include "wheel.h"
#include <avr/io.h>

unsigned int calc_inst_RPM(unsigned int half_revolution_count){
  unsigned int _rpm = (60 * (half_revolution_count) / 2);
  return _rpm;
}
