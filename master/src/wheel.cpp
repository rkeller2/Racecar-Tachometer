
#include "wheel.h"
#include <avr/io.h>

unsigned int calc_inst_RPM(unsigned int half_revolution_count){
  unsigned int _rpm = (60 * (half_revolution_count) / 2);
  return _rpm;
}
