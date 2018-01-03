// Author:
// Net ID:
// Date:
// Assignment:
//
// Description:
//----------------------------------------------------------------------//

#ifndef I2C_H
#define I2C_H

void initI2CMaster();
void send_START();
void load_SLA_R();
void send_SLA_R();
void send_ACK();
char load_DATA();

#endif
