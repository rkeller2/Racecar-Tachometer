
#include "serial.h"
#include <avr/io.h>

void initSerial0(){
  UCSR0B |= (1 << RXCIE0 | 1 << TXCIE0 | 1 << RXEN0 | 1 << TXEN0);
  UCSR0B &= ~(1 << UCSZ02);
  UBRR0L = 103;
}
