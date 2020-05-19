/*------------------------------------------------------------*-
  BUZZER - header file
  ESP32 CORE1 - APPLICATION CORE
  (c) An Minh Dao 2019
  version 1.00 - 23/02/2019
---------------------------------------------------------------
 *  PUBLIC FUNCTIONS CONTAIN:
 *  void RFID125_init();
 *  bool hasID();  //check if there is any new ID by interrupt
 *  void RFID125_interrupt();
 *  
 *  PRIVATE FUNCTIONS CONTAIN:
 *  void GetID();
 *  long hexstr_to_value(unsigned char *str, unsigned int str_length);
 * 
 --------------------------------------------------------------*/
#ifndef _C1_BUZZER_H
#define _C1_BUZZER_H
#include "config.h"
#include "pins.h"

// ------ Public constants ------------------------------------
void multipleBeep(int number);
void singleBeep(int mstime);
// ------ Public function prototypes --------------------------

// ------ Public variable -------------------------------------


#endif //_C1_BUZZER_H