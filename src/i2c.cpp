/*************************************************************************
Author: Robert Keller, Gavin Daniel
Date: 4/4/2017
Assignment: Digital Tachometer in C/C++

Project Description: This project interfaces an Arduino MEGA 2560 with an infrared 
LED comparator circuit via i2c communication protocol to calculate and display the 
instantaneous RPM of an accelerating racecar on an LCD screen
**********************************************************************/

#include <avr/io.h>
#include "i2c.h"
#include "serial.h"

#define SLA_ADDRESS 0b11001100
// initialize the I2C Master Mode
void initI2CMaster(){
  TWBR = 0x0F;
  TWCR |= (1 << TWEN) | (1 << TWIE); // enable TWI
}
// transmit start condition
void send_START(){
  TWCR |= (1<<TWINT | 1<<TWSTA | 1<<TWEN);
  TWCR &= ~(1<<TWSTO);
}
// load SLA address into the TWDR register and send a read-bit
void load_SLA_R(){
  TWDR = SLA_ADDRESS | 1; //1 = R
}
// transmit the SLA+R and wait for acknowledgement
void send_SLA_R(){
  TWCR |= (1<<TWINT | 1<<TWEN);
  TWCR &= ~(1<<TWSTA | 1<<TWSTO);
}
// transmit acknowledgement to slave
void send_ACK(){
  TWCR &= ~(1<<TWSTA | 1<<TWSTO);
  TWCR |= (1<<TWINT | 1<<TWEA);
}
// load DATA received from register
char load_DATA(){
  char dataReceived = TWDR;
  return dataReceived;
}
