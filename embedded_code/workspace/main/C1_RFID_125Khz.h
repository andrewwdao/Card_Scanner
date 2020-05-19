/*------------------------------------------------------------*-
  RDM630/6300 125khz Card Reader - header file
  ESP32 CORE1 - APPLICATION CORE
  (c) An Minh Dao 2019
  version 3.00 - 25/02/2019
---------------------------------------------------------------
 *  PUBLIC FUNCTIONS CONTAIN:
 *  void RFID125_init();
 *  bool hasID();  //check if there is any new ID by interrupt
 *   
 *  PRIVATE FUNCTIONS CONTAIN:
 *  void RFID125_interrupt();
 *  void GetID();
 *  long hexstr_to_value(unsigned char *str, unsigned int str_length);
 * 
 *  CAUTION: must include config.h
 --------------------------------------------------------------*/
#ifndef _C1_RFID_125KHZ_H
#define _C1_RFID_125KHZ_H
#include "config.h"
#include "pins.h"
#include "C1_Buzzer.h"

// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
void RFID125_init();
bool hasID(); //check if there is any new ID by interrupt
String getID();

// ------ Public variable -------------------------------------
//extern char  strID[];

#endif //_C1_RFID_125KHZ_H