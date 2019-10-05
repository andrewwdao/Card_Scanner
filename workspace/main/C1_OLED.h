/*------------------------------------------------------------*-
  Module OLED 12864 1.3 inch 128x64 pixel - header file
  ESP32 CORE1 - APPLICATION CORE
  (c) An Minh Dao 2019
  version 1.00 - 18/02/2019
---------------------------------------------------------------
 *  PUBLIC FUNCTIONS CONTAIN:
 *   
 *  PRIVATE FUNCTIONS CONTAIN:
 * 
 * 
**** NOTE: use I2C communication
 *
 * 
 *  CAUTION: must include config.h
 --------------------------------------------------------------*/
#ifndef _C1_OLED_H
#define _C1_OLED_H
#include "config.h"
#include "pins.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include "C0_Wifi_sta_ch.h"
#include "C1_RTC_DS3231.h"
#include "core1.h"
// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
void oled_init_c1();
void oled_ctuLogo(); //integrated into buffer already!!!
void oled_clear();

void oled_system_failed();
void oled_SD_failed();
void oled_wifi_failed();
void oled_get_error();
void oled_Export_ok();
void oled_Ex_error();
void oled_comeBack();

void oled_wifi_SerialUpdater();
void oled_wifi_BLEupdater();

void oled_BLE_receivedData();
void oled_BLE_eraseData();

void oled_RTC_SerialUpdater();
void oled_RTC_SNTPupdater1();
void oled_RTC_SNTPupdater2();
void oled_RTC_SNTPupdater3(bool);

void oled_POINTER1();
void oled_POINTER2();
void oled_POINTER3();
void oled_POINTER4();

void oled_mainMenu_init();
void oled_mainMenu_1();
void oled_mainMenu_2();
void oled_mainMenu_3();
void oled_done();

void oled_Frame1_init(String);//used for both "attendance check" and "add class"
void oled_Frame1_menu(); //use for both "check attendance" and "add class" mode
void oled_Frame1_mode(String);
void oled_Frame1_Class1(String*); //back-class1-class2-class3
void oled_Frame1_Class2(String*); //class4-class5-class6-class7

void oled_Acheck_make();
void oled_Acheck_remain(int);
void oled_Acheck_coincide();
void oled_Acheck_makeDone(String,String);
void oled_Acheck_saved();
void oled_Acheck_failed();
void oled_ACheck_done();

void oled_connect();
void oled_getRFID_init();
void oled_getRFID_info(String, String,String);
void oled_getRFID_status(String);
void oled_getRFID_end(String,String);

void oled_AClass_override();

// ------ Public variable -------------------------------------
extern Adafruit_SH1106 oled;

#endif //_C1_OLED_H