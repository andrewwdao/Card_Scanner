/*------------------------------------------------------------*-
  ESP32 CORE0 COMBINED TASK - PROTOCOL CORE - header file
  COMBINED LOCATION FOR INTERACTING BETWEEN FILES
  (c) An Minh Dao 2019
  version 1.20 - 10/02/2019
---------------------------------------------------------------
 *  CAUTION:
 *  This core is responsible for RF radio, Wifi stack and protocols (watchdog,...) 
 *  (the Arduino code is compiled to run on the second core (core_1). FreeRTOS manages everything)
 *  Therefore, you have to be EXTREMELY CAREFUL when create task for this core,
 *  in order to not intefere these default functions (watchdog has the piority of 1 among 0 to N, higher number means higer piority)
 * 
 *  PUBLIC FUNCTIONS CONTAIN:
 *  void Core0CombinedTask_init();
 *  xSemaphoreGive(serialLog_baton);
 *  xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
 *
 *  PRIVATE FUNCTIONS CONTAIN:
 *  static void Core0CombinedTask( void * parameter ); //task run on core0
 * 
 *  P/S CAUTION: must include config.h
 --------------------------------------------------------------*/
#ifndef _CORE0_H
#define _CORE0_H
#include "config.h"
#include "core1.h"
#include "C1_Switch.h"
#include "C0_Wifi_sta_ch.h"
// ------ Public constants ------------------------------------

// ------ Public function prototypes -------------------------
void Core0CombinedTask_init();
/*
  xSemaphoreGive(serialLog_baton);
  xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
*/

// ------ Public variable -------------------------
extern SemaphoreHandle_t serialLog_baton; //declared in core0 cpp
#ifdef TASKS_MONITOR
extern SemaphoreHandle_t taskMonitor_baton;
#endif
#endif //_CORE0_H
