/*------------------------------------------------------------*-
  ESP32 CORE1 COMBINED TASK - APPLICATION CORE - header file
  COMBINED LOCATION FOR INTERACTING BETWEEN FILES
  (c) An Minh Dao 2019
  version 1.70 - 24/04/2019
---------------------------------------------------------------
 *  CAUTION:
 *  This core is responsible for main application code
 * 
 *  PUBLIC FUNCTIONS CONTAIN:
 *  void Core1CombinedTask_init();
 *  xSemaphoreGive(serialLog_baton);
 *  xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
 *
 *  PRIVATE FUNCTIONS CONTAIN:
 *  void Core1CombinedTask( void * parameter ); //task run on core0
 * 
 *  P/S CAUTION: must include config.h
 --------------------------------------------------------------*/
#ifndef _CORE1_H
#define _CORE1_H
#include "config.h"
#include "pins.h"
#include "core0.h"
#include "C1_RTC_DS3231.h"
#include "C1_RFID_125Khz.h"
#include "C1_SD_Card.h"
#include "C1_OLED.h"
#include "C1_Buzzer.h"
#include "C1_Switch.h"
#include "C1_Scenarios.h"
#include "C1_Clock.h"
// ------ Public constants ------------------------------------

// ------ Public function prototypes -------------------------
void Core1CombinedTask_init();
/*
  xSemaphoreGive(serialLog_baton);
  xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
*/

// ------ Public variable -------------------------
extern SystemState CurrentState;
extern SemaphoreHandle_t serialLog_baton; //declared in core0 cpp
#ifdef TASKS_MONITOR
extern SemaphoreHandle_t taskMonitor_baton;
#endif
extern TaskHandle_t Core1_combined;
#endif //_CORE1_H