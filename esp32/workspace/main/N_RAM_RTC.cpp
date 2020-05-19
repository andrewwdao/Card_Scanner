/*------------------------------------------------------------*-
  RAM usage of the RTC module DS3231 (AT24C32) - function file
  ESP32 CORE0 - PROTOCOL CORE
  (c) An Minh Dao 2019
  version 2.00 - 10/03/2019
---------------------------------------------------------------
 *  IC: AT24C32
 *  Share space and battery with IC RTC DS3231
 *  Data will be maintained as long as the battery is alive
 *  Available RAM: 32kB 
 *  Address start from 0 to 32768 (an address coresponding to a byte)
 *  Communication: I2C - SCL:22, SDA:21 (esp32)
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
 * NOTE:  - StringBuffer.c_str() return const char* => it converts String into const char*
 *        - sprintf(charWriteBuffer,"%s", RAMdata.c_str()); //this function transfer const char* to char*
 *       
 * 
 --------------------------------------------------------------*/
#ifndef _C0_RAM_RTC_CPP
#define _C0_RAM_RTC_CPP
#include "N_RAM_RTC.h"

// ------ Private constants -----------------------------------
#define RAM_ADDRESS      0x57

#define CLASS_ADDRESS    200 //CAUTION: number 200 is fixed because the RAM has some defects, so if use other number may cause some lost infos
#define CTUCLASS_CHARS  8 //default characters of a class
// ------ Private function prototypes -------------------------

// ------ Private variables -----------------------------------

// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
// WARNING: address is a page address, 6-bit end will wrap around
// also, data can be maximum of about 30 bytes, because the Wire library has a buffer of 32 bytes
void RAM_page_write(unsigned int RAMaddress, char* RAMdata, int RAMlength) {
  Wire.beginTransmission(RAM_ADDRESS);
  Wire.write((int)(RAMaddress >> 8)); // MSB
  Wire.write((int)(RAMaddress & 0xFF)); // LSB
  byte c;
  for ( c = 0; c < RAMlength; c++) {
    Wire.write(RAMdata[c]);
  }//end for
  Wire.endTransmission();
}//end RAM_page_write

// maybe let's not read more than 30 or 32 bytes at a time!
void RAM_page_read(unsigned int RAMaddress, char* RAMbuffer, int RAMlength) {
    Wire.beginTransmission(RAM_ADDRESS);
    Wire.write((int)(RAMaddress >> 8)); // MSB
    Wire.write((int)(RAMaddress & 0xFF)); // LSB
    Wire.endTransmission();
    Wire.requestFrom(RAM_ADDRESS,RAMlength);
    int c = 0;
    for ( c = 0; c < RAMlength; c++ ) {
      if (Wire.available()) RAMbuffer[c] = Wire.read();
    }//end for
}//end RAM_page_read

/////////////////////////PULBLIC///////////////////////
void RAM_CTUclass_write(char RAMclassNum, String RAMdata) { //a class name have 8 character CN123-S6
  char charWriteBuffer[CTUCLASS_CHARS];
  sprintf(charWriteBuffer,"%s", RAMdata.c_str()); //this function transfer const char* to char*
  //CAUTION: number CLASS_ADDRESS is fixed because the RAM has some defects, so if use other number may cause some lost infos  
  RAM_page_write(CLASS_ADDRESS+(int)((RAMclassNum)*(CTUCLASS_CHARS)), charWriteBuffer, CTUCLASS_CHARS); //write an array, should be less than 30 bytes
}//end RAM_CTUclass_write()

String RAM_CTUclass_read(char RAMclassNum) {
  char charReadBuffer[CTUCLASS_CHARS+1];
  //CAUTION: number CLASS_ADDRESS is fixed because the RAM has some defects, so if use other number may cause some lost infos
  RAM_page_read(CLASS_ADDRESS+(int)((RAMclassNum)*(CTUCLASS_CHARS)), charReadBuffer, CTUCLASS_CHARS); //read an array, should be less than 30 bytes
  charReadBuffer[CTUCLASS_CHARS] = '\0';
  return charReadBuffer;
}//end RAM_CTUclass_read()

#endif //_C0_RAM_RTC_CPP
