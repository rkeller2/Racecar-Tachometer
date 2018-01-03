// Author:
// Net ID:
// Date:
// Assignment:
//
// Description:
//----------------------------------------------------------------------//

#include <avr/io.h>
#include "i2c.h"

#define SLAVE_ADDRESS 0b11001100

void initI2CSlave(){
// clear the address register
  TWAR = 0;
  TWAR = SLAVE_ADDRESS; //TWA6:0 (7-bits), TWGCE (8th bit)
  TWCR |= (1<<TWEA) | (1<<TWEN) | (1<<TWIE); //send START condition
  TWCR &= ~(1<<TWSTA);
  TWCR &= ~(1<<TWSTO);
}
void sendACK(){
  TWCR |= (1 << TWINT);
  TWCR |= (1 << TWEA);
}
void loadTWDRreg(unsigned int TWDR_value){
  TWDR = TWDR_value; // 'G'
}
