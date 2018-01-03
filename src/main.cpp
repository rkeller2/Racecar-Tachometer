/*************************************************************************
Author: Robert Keller, Gavin Daniel
Date: 4/4/2017
Assignment: Digital Tachometer in C/C++

Project Description: This project interfaces an Arduino MEGA 2560 with an infrared 
LED comparator circuit via i2c communication protocol to calculate and display the 
instantaneous RPM of an accelerating racecar on an LCD screen

File Description: This file contains a programmatic overall description of the program. 
It should never contain assignments to special function registers for the exception 
key one-line code such as checking the state of the pin.
**********************************************************************/

#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "serial.h"
#include "i2c.h"
#include "timer.h"
#include "wheel.h"
#include <LiquidCrystal.h>

//------------------  TWSR STATUS' REGISTER VALUES  ------------------------//
#define START 0x08            // START Condition
#define MR_SLA_ACK 0x40       // SLA transmitted, ACK received
#define MR_DATA_ACK 0x50      // DATA received, ACK returned
#define REPEAT_START 0x10     // Repeat START Condition
#define ARBITRATION_LOST 0x38 // Arbitration lost in SLA+R
#define MR_SLA_NACK 0x48      // SLA transmitted, NACK received
#define MR_DATA_NACK 0x58     // DATA received, NACK returned
//------------------   PRE-DEFINE VALUES  ------------------------//
#define SAMPLE_TIME_MAX 99
//------------------   FLAGS & COUNTERS  ------------------------//
// Flags
volatile char data;
volatile char prev_data = 'B';
// Counters
volatile unsigned int sample_time_count = 0;      // simple counter to accurately output an updated RPM value when wanted
volatile unsigned int half_revolution_count = 0;  // counts every half revolution
volatile unsigned int inst_RPM = 0;               // instantaneous RPM speed of the wheel
//------------------   OTHER  ------------------------//
      /* lcd (RS, E, D4, D5, D6, D7)*/
LiquidCrystal lcd(28,30,52,50,48,46);

int main(){
// **** I2C initialization ******
  initI2CMaster();
  //initSerial0();
  send_START();
//*******************************
// **** LCD initialization ******
  initTimer1();
  //initLCD();
// ******************************
// ******** Enable ISRs *********
  sei();
// ******************************
// **** Debugging needs *********
  Serial.begin(9600);
// *****************************
  lcd.begin(16,2);
/***********************************/
  while(1){
    refresh(1); //screen + sample refresh rate
    sample_time_count++;

    if(sample_time_count > SAMPLE_TIME_MAX){
      inst_RPM = calc_inst_RPM(half_revolution_count);
    //  inst_RPM++;
      //Sinst_RPM;
      // lcd.setCursor(0,0);
      // lcd.clear();
      // lcd.print("RPM = ");
      // lcd.print(inst_RPM);

      Serial.print("RPM:   ");
      Serial.println(inst_RPM);
      sample_time_count = 0; // reset
      half_revolution_count = 0;   // reset
    }
    if (data == 'B' && prev_data == 'W'){
      half_revolution_count++;
      prev_data = 'B';
    }
    if (data == 'W' && prev_data == 'B'){
      half_revolution_count++;
      prev_data = 'W';
    }
  }

  return 0;
}

ISR (TWI_vect){
  if (TWSR == START) {
    load_SLA_R();       // load TWDR w/ SLA+R
    send_SLA_R();       // transmit SLA+R
  }
  if (TWSR == MR_SLA_ACK) {
    send_ACK();         // send ACK
  }
  if (TWSR == MR_DATA_ACK) {
    data = load_DATA(); // load data from TWDR register
    send_ACK();         // send ACK
  }
  // ***** new ******
  if (TWSR == REPEAT_START) {
    load_SLA_R();       // load TWDR w/ SLA+R
    send_SLA_R();       // transmit SLA+R
  }
  if (TWSR == ARBITRATION_LOST) {
    send_START();       // send START condition
  }
  if (TWSR == MR_SLA_NACK) {
    send_START(); //repeat START condition
  }
  if (TWSR == MR_DATA_NACK) {
    send_START(); // repeat START Condition
  }
 }
