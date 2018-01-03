/*************************************************************************
Author: Robert Keller, Gavin Daniel
Date: 4/4/2017
Assignment: Digital Tachometer in C/C++

Project Description: This project interfaces an Arduino MEGA 2560 with an infrared 
LED comparator circuit via i2c communication protocol to calculate and display the 
instantaneous RPM of an accelerating racecar on an LCD screen
**********************************************************************/

#ifndef I2C_H
#define I2C_H

void initI2CMaster();
void send_START();
void load_SLA_R();
void send_SLA_R();
void send_ACK();
char load_DATA();

#endif
