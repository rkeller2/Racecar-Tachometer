// Author:         Gavin Daniel
// Net ID:         gavindaniel
// Date:           27 March 2017
// Assignment:     Final Project
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
// Requirements:
//----------------------------------------------------------------------//
#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "adc.h"
#include "i2c.h"
#include "timer.h"
//------------------  TWSR STATUS' REGISTER VALUES  ------------------------//
#define SLA_R_ADDR_ACK  0xA8
#define TWDR_DATA_ACK   0xB8
#define ARB_SLA_R       0xB0
#define TWDR_DATA_NACK  0xC0
#define LAST_DATA_ACK   0xC8
#define NO_RELEVANT_STATE 0xF8
#define BUS_ERROR         0x00
//------------------   PRE-DEFINE VALUES  ------------------------//
#define SAMPLE_TIME_MAX 99
#define ADC_THRESHOLD 500
#define WHITE 0x57
#define BLACK 0x42
//------------------   variable(s)  ------------------------//
volatile unsigned int adc_val = 0;
volatile unsigned int TWDR_VALUE = 0x41; // 'A'
//------------------   STATE(S)  ------------------------//
typedef enum stateType_enum{
  black, white
} stateType;
stateType prevState;

int main(){

  // **** I2C initialization ******
    initI2CSlave();
  //*******************************
  // **** ADC initialization ******
    initADC0();
    initTimer1();
  // ******************************
  // ******* Enable ISRs **********
    sei();
  // ******************************
  // **** Debugging needs *********
    Serial.begin(9600);
  // ******************************

  while(1){
    refresh(1);

    adc_val = ADCL;
    adc_val = adc_val + (ADCH << 8);

    if (adc_val > ADC_THRESHOLD && prevState == black){
      TWDR_VALUE = WHITE; // 'W'
      prevState = white;
    }
    if (adc_val < ADC_THRESHOLD && prevState == white){
      TWDR_VALUE = BLACK; // 'B'
      prevState = black;
    }
   }
  return 0;
}

ISR(TWI_vect){
  if(TWSR == SLA_R_ADDR_ACK){
    loadTWDRreg(TWDR_VALUE);
    sendACK();
  }
  if(TWSR == TWDR_DATA_ACK){
    loadTWDRreg(TWDR_VALUE);
    sendACK();
  }
}
