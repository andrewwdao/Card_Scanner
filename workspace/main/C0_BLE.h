/*------------------------------------------------------------*-
  Bluetooth Low Energy for supporting Wifi sign in - header file
  ESP32 CORE1 - APPLICATION CORE
  (c) An Minh Dao - Bernd Giesecke 2019
  version 1.00 - 12/03/2019
---------------------------------------------------------------
 *  PUBLIC FUNCTIONS CONTAIN:
 *  
 *  PRIVATE FUNCTIONS CONTAIN:
 * 
 * CAUTION: 
 * + Use ArduinoJson 6.x 
 * + only 1 BLE connection can be established, can be changed in menuconfig
 --------------------------------------------------------------*/
#ifndef _C0_BLE_H
#define _C0_BLE_H
#include "config.h"
#include "pins.h"
#include <ArduinoJson.h> // Includes for JSON object handling - https://arduinojson.org - https://github.com/bblanchon/ArduinoJson
// Includes for BLE
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEDevice.h>
#include <BLEAdvertising.h>

#include "N_NVS.h"
#include "C1_OLED.h"
#include "C0_Wifi_sta_ch.h"

// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
void initBLE();

// ------ Public variable -------------------------------------
/* Connection change status */
extern bool BLEreceived;
/** Flag if stored AP credentials are available */
extern bool BLEhasCredentials;

#endif //_C0_BLE_H