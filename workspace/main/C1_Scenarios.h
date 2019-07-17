/*--------------------------------------------------------------------------------*-
  System Scenarios - header file
  ESP32 CORE1 - APPLICATION CORE
  (c) An Minh Dao 2019
  version 1.00 - 27/03/2019
-------------------------------------------------------------------------------------
 * 
 *  PUBLIC FUNCTIONS CONTAIN:
 * 
 *  PRIVATE FUNCTIONS CONTAIN:
 *
 *  - Important Documents:
 * 		+ 
 * -------------------------------------------------------------------------------------*/
#ifndef _C1_SCENARIOS_H
#define _C1_SCENARIOS_H
#include "config.h"
#include "pins.h"
#include "N_RAM_RTC.h"
#include "core1.h"
#include "C1_Switch.h"
#include "C1_SD_Card.h"
#include "C1_OLED.h"

// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
/* FUNCTION DEFINITIONS - CRUCIAL FUNCTIONS */
//### WIFI SERIAL UPDATER --> C0_Wifi_sta_ch.cpp
//### WIFI BLE UPDATER    --> C0_Wifi_sta_ch.cpp
//### RTC UPDATER         --> C1_RTC_DS3231.cpp
void Scenarios_update();
void AddClass_init();
char Export_begin();
void Frame1_ClasDel(String, String*, char*, char);
/* FUNCTION DEFINITIONS - APPLICATION FUNCTIONS */

// ------ Public variable -------------------------------------

#endif //_C1_SCENARIOS_H
