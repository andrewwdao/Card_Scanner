/*------------------------------------------------------------*-
  ESP32 CORE0 COMBINED TASK - PROTOCOL CORE - functions file
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
 --------------------------------------------------------------*/
#ifndef _CORE0_CPP
#define _CORE0_CPP
#include "Core0.h"

// ------ Private constants -----------------------------------
const int C0_COMBINED_TASK_STACK   PROGMEM =  5000; // Stack size of Task1_CORE0 (in bytes- NOT words)
// ------ Private function prototypes -------------------------
static void Core0CombinedTask( void * parameter ); //task run on core0
/*
  xSemaphoreGive(serialLog_baton);
  xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
*/
// ------ Private variables -----------------------------------
TaskHandle_t Core0_combined; //pointer
// ------ PUBLIC variable definitions -------------------------
extern SemaphoreHandle_t serialLog_baton;
#ifdef TASKS_MONITOR
extern SemaphoreHandle_t taskMonitor_baton;
#endif
//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void Core0CombinedTask_init() {
  xTaskCreatePinnedToCore(
    Core0CombinedTask,                   /* Task Function */
    "C0_Combined",                       /* Name of Task */
    C0_COMBINED_TASK_STACK,              /* Stack size of Task - in bytes (in normal FREERTOS it will be words)*/
    NULL,                                /* Parameter of the task */
    DEFAULT_PIORITY,                     /* Priority of the task, vary from 0 to N, bigger means higher piority, need to be 0 to be lower than the watchdog*/
    &Core0_combined,                     /* Task handle to keep track of created task */
    PRO_CPU_NUM);                        /* CoreID - CORE0: 0 or PRO_CPU_NUM - CORE1: 1 or APP_CPU_NUM - tskNO_AFFINITY: either one is free*/

}//end Core0CombinedTask_init

static void Core0CombinedTask( void * parameter ) {//usual task run on core0 
/***************************************SETUP************************************************/
  #ifdef SERIAL_OUTPUT
    xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
  #endif
  CurrentState = NVS_system_read();
  // S_PRINTLN();
  // S_PRINTLN(F("//////////////////////////////////////////////////////////////////////////"));
  // S_PRINTLN(F("//////////////////////  CAN THO UNIVERSITY - 2019 ////////////////////////"));
  // S_PRINTLN(F("///////////////////////    CARD SCANNER SYSTEM   ////////////////////////"));
  // S_PRINTLN();
  #ifdef SERIAL_OUTPUT
  xSemaphoreGive(serialLog_baton); //give out baton for other tasks to catch
  #endif

//################################# STATE CHECKING ##################################
// =========================== NORMAL - NORMAL DIRECT MODE ==========================
  if ((CurrentState==SYS_NORMAL)||(CurrentState==SYS_NORMAL_DIRECT)) {
    #ifdef SERIAL_OUTPUT
      delay(10);
      xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
    #endif
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    btStop(); //stop BLE
    #ifdef SERIAL_OUTPUT //announce to core1 to finish initialize
      xSemaphoreGive(serialLog_baton); //give out baton for other tasks to catch
    #endif
    //PROCEED TO LOOP IMMEDIATELY!!! CAUTION!!!
    vTaskDelete(NULL);
  }//end if
//###################################################################################
/*******************************************************************************************/

/***************************************LOOP************************************************/
 vTaskDelete(NULL);
/*******************************************************************************************/
}//end Core0CombinedTask
#endif //_CORE0_CPP
