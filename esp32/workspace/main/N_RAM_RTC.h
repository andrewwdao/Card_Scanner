/*------------------------------------------------------------*-
  RAM usage of the RTC module DS3231 (AT24C32) - header file
  ESP32 CORE0 - PROTOCOL CORE
  (c) An Minh Dao 2019
  version 1.00 - 13/02/2019
---------------------------------------------------------------
 *  IC: AT24C32
 *  Share space and battery with IC RTC DS3231
 *  Data will be maintained as long as the battery is alive
 *  Available RAM: 32kB
 *  Address start from 0 to 32768 (an address coresponding to a byte)
 *  Communication: I2C
 *  ESP32 GPIO:
 *      SDA:21
 *      SCL:22
 * 
 *  PUBLIC FUNCTIONS CONTAIN:
 *  void RAM_write(unsigned int RAMaddress, byte data); //write in 1 byte
 *  void RAM_page_write(unsigned int RAMaddress, byte* RAMdata, byte RAMlength); //write an array, should be less than 30 bytes
 *  byte RAM_read(unsigned int RAMaddress); //read in 1 byte
 *  void RAM_page_read(unsigned int RAMaddress, byte* RAMbuffer, byte RAMlength); //read an array, should be less than 30 bytes
 *  
 *  PRIVATE FUNCTIONS CONTAIN:
 * 
 * 
 *  CAUTION: must include config.h
--------------------------------------------------------------*/
#ifndef _C0_RAM_RTC_H
#define _C0_RAM_RTC_H
#include "config.h"
#include "pins.h"
#include "Wire.h" //I2C library
#include "C1_SD_Card.h"
// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
void RAM_page_write(unsigned int RAMaddress, char* RAMdata, int RAMlength);
void RAM_page_read(unsigned int RAMaddress, char* RAMbuffer, int RAMlength);

void RAM_CTUclass_write(char RAMclassNum, String RAMdata);
String RAM_CTUclass_read(char RAMclassNum);
// ------ Public variable -------------------------------------

#endif //_C0_RAM_RTC_H