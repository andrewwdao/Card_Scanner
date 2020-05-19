/*------------------------------------------------------------*-
  Wifi Station changeable module - header file
  ESP32 CORE0 - PROTOCOL CORE
  (c) An Minh Dao - Bernd Giesecke 2019
  version 2.00 - 27/03/2019
---------------------------------------------------------------
 *  PUBLIC FUNCTIONS CONTAIN:
 *  void wifi_STA_init();
 *  bool wifi_isConnected();
 *  void wifi_STA_serialUpdater();
 *  void wifi_STA_BLEupdater();
 * 
 *  PRIVATE FUNCTIONS CONTAIN:
 *  static void Wifi_begin();
 *  static String GetData();     //only exist in changeable mode
 * 
 *  CAUTION: must include config.h
--------------------------------------------------------------*/
#ifndef _C0_WIFI_STA_CH_H
#define _C0_WIFI_STA_CH_H
#include "config.h"
#include "C1_OLED.h"
#include "C1_Switch.h"
#include "N_NVS.h"
#include "N_RAM_RTC.h"
#include "C0_BLE.h"
#include <esp32-hal-bt.h> // to stop bluetooth
#include <ArduinoJson.h>
#include <HTTPClient.h>
// ------ Public constants ------------------------------------
#define READ_SSID true
#define READ_PASS false
// ------ Public function prototypes --------------------------
/**/
bool wifi_isConnected();
/**/
bool wifi_STA_init();
/**/
void wifi_STA_serialUpdater();
/** Use your phone to change Wifi Credentials. 
 *  Return to NORMAL MODE: Press MIDDLE button once. */
void wifi_STA_BLEupdater();

////////HTTP PART
/**/
void HTTP_updateAP();
/*get class and store class identities into String parameter,
number of class into char parameter*/
char HTTP_getClass(String*,char*);
char HTTP_getFrom(String*,char*,char);

char HTTP_send();
// ------ Public variable -------------------------------------

#endif //_C0_WIFI_STA_CH_H