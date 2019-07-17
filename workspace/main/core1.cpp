/*------------------------------------------------------------*-
  ESP32 CORE1 COMBINED TASK - APPLICATION CORE - functions file
  COMBINED LOCATION FOR INTERACTING BETWEEN FILES
  (c) An Minh Dao 2019
  version 1.70 - 24/04/2019
---------------------------------------------------------------
 *  CAUTION:
 *  This core is responsible for main application code
 * 
 *  PUBLIC FUNCTIONS CONTAIN:
 *  void Core0CombinedTask_init();
 *  xSemaphoreGive(serialLog_baton);
 *  xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
 *
 *  PRIVATE FUNCTIONS CONTAIN:
 *  static void Core1CombinedTask( void * parameter ); //task run on core0
 * 
 --------------------------------------------------------------*/
#ifndef _CORE1_CPP
#define _CORE1_CPP
#include "Core1.h"

// ------ Private constants -----------------------------------
const int C1_COMBINED_TASK_STACK   PROGMEM =  50000; // Stack size of Task1_CORE0 (in bytes- NOT words)
// ------ Private function prototypes -------------------------
static void Core1CombinedTask( void * parameter ); //task run on core0
/*
  xSemaphoreGive(serialLog_baton);
  xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
*/
// ------ Private variables -----------------------------------
TaskHandle_t Core1_combined; //pointer

// ------ PUBLIC variable definitions -------------------------
SystemState CurrentState;
extern SemaphoreHandle_t serialLog_baton; //declared in core0 cpp
#ifdef TASKS_MONITOR
extern SemaphoreHandle_t taskMonitor_baton;
#endif
//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void Core1CombinedTask_init() {
  xTaskCreatePinnedToCore(
    Core1CombinedTask,                   /* Task Function */
    "C1_Combined",                       /* Name of Task */
    C1_COMBINED_TASK_STACK,              /* Stack size of Task - in bytes (in normal FREERTOS it will be words)*/
    NULL,                                /* Parameter of the task */
    DEFAULT_PIORITY,                     /* Priority of the task, vary from 0 to N, bigger means higher piority, need to be 0 to be lower than the watchdog*/
    &Core1_combined,                     /* Task handle to keep track of created task */
    APP_CPU_NUM);                        /* CoreID - CORE0: 0 or PRO_CPU_NUM - CORE1: 1 or APP_CPU_NUM - tskNO_AFFINITY: either one is free*/

}//end Core1CombinedTask_init

static void Core1CombinedTask( void * parameter ) {//task run on core0
/***************************************SETUP************************************************/
// ----------- OLED INITIALIZE -----------------------
  Wire.setClock(400000L); //setClock to 400khz
  oled_init_c1();
// ----------- RF INITIALIZE -------------------------
  RFID125_init();
// ----------- SWITCH INITIALIZE -------------
  SW_init();
  SW_enable();
//------------ WAIT FOR CORE0 TO SHOOT SERIAL---------
  //wait for core0 to shoot serial first
  #ifdef SERIAL_OUTPUT //wait for core0 to finish wifi
    xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
  #endif
//################################# STATE CHECKING ##################################
  switch (CurrentState) {
// ================================== NORMAL MODE ============================
    case SYS_NORMAL: {
      oled_ctuLogo(); //show CTU logo at the beginning only on NORMAL MODE
      // #ifdef SERIAL_OUTPUT //wait for core0 to finish wifi
      //   xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
      // #endif
      // -------------- SD CARD INITIALIZE --------------------
      SD_init();
      // -------------- RTC INITIALIZE ------------------------
      if (RTC_init()) {
        S_PRINT(F("Current time: ")); S_PRINTLN(RTC_getTime());
        Clock_init(RTC_getSecond());//initialize timer appropriately for display time
      }
      //////////////////////////only in NORMAL mode/////////////////////////////////
      // ------------ AUTO EXPORT DATA ---------------------------
      if (NVS_AExMode_read()) {
        Export_begin();
      }//end if
      // ------------ FINALIZING ---------------------------
      pinMode(BUZZER_PIN,OUTPUT);multipleBeep(3); //init buzzer
      S_PRINTLN(F("System Ready!"));
      D_PRINTLN(F("DEBUG Mode"));
      //////////////////////////////////////////////////////////////////////////////
      //-------------------------------------------------------
      // #ifdef SERIAL_OUTPUT //give change to core0 to initialize wifi
      //   xSemaphoreGive(serialLog_baton); //give out baton for other tasks to catch
      // #endif
      // #ifdef TASKS_MONITOR
      //   //make core1 main function wait for the taskMonitor to start
      //   xSemaphoreTake(taskMonitor_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html
      //   //release right after catched
      //   xSemaphoreGive(taskMonitor_baton); //give out baton for other tasks to catch
      // #endif
      //PROCEED TO LOOP IMMEDIATELY!!! CAUTION!!!
      break;
    }//end case
// ================================== DIRECT NORMAL MODE ============================
    case SYS_NORMAL_DIRECT: {
      NVS_system_write(SYS_NORMAL);
      // #ifdef SERIAL_OUTPUT //wait for core0 to finish wifi
      //   xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
      // #endif
      // -------------- SD CARD INITIALIZE --------------------
      SD_init();
      // -------------- RTC INITIALIZE ------------------------
      if (RTC_init()) {
        D_PRINT(F("Current time: ")); D_PRINTLN(RTC_getTime());
        Clock_init(RTC_getSecond());//initialize timer appropriately for display time
      }
      //-------------------------------------------------------
      // #ifdef SERIAL_OUTPUT //give change to core0 to initialize wifi
      //   xSemaphoreGive(serialLog_baton); //give out baton for other tasks to catch
      // #endif
      // #ifdef TASKS_MONITOR
      //   //make core1 main function wait for the taskMonitor to start
      //   xSemaphoreTake(taskMonitor_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html
      // #endif
      //PROCEED TO LOOP IMMEDIATELY!!! CAUTION!!!
      break;
    }//end case
// ================================== ADDCLASS THROUGH HTTP MODE ============================
    case SYS_ADD_CLASSES: {
      //NVS_system_write(SYS_NORMAL);
      // #ifdef SERIAL_OUTPUT //wait for core0 to finish wifi
      //   xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
      // #endif
      oled_connect(); //show oled screen
      // -------------- SD CARD INITIALIZE --------------------
      SD_init();
      // -------------- RTC INITIALIZE ------------------------
      if (RTC_init()) {
        D_PRINT(F("Current time: ")); D_PRINTLN(RTC_getTime());
        Clock_init(RTC_getSecond());//initialize timer appropriately for display time
      }
      //-------------------------------------------------------
      #ifdef SERIAL_OUTPUT //give change to core0 to initialize wifi
        xSemaphoreGive(serialLog_baton); //give out baton for other tasks to catch
      #endif
      #ifdef TASKS_MONITOR
        //make core1 main function wait for the taskMonitor to start
        xSemaphoreTake(taskMonitor_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html
        //release right after catched
        xSemaphoreGive(taskMonitor_baton); //give out baton for other tasks to catch
      #endif
      //Start your job now!
      AddClass_init();
      vTaskDelete(NULL);// this will never be called!
      break;
    }//end case
// =========================== SYSTEM SERIAL WIFI UPDATER MODE ===============
    case SYS_SERIAL_UPDATE_WIFI: {
      // #ifdef SERIAL_OUTPUT
      //   xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
      // #endif
      wifi_STA_serialUpdater();
      break;
    }//end case
// =================== SYSTEM BLUETOOTH LOW ENERGY WIFI UPDATER MODE =========
    case SYS_BLE_UPDATE_WIFI: {
      // #ifdef SERIAL_OUTPUT
      // xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
      // #endif
      wifi_STA_BLEupdater();
      break;
    }//end case
// ====================  SYSTEM REAL TIME CLOCK SERIAL UPDATER ===============
    case SYS_SERIAL_UPDATE_RTC: {
      // #ifdef SERIAL_OUTPUT
      //   xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
      // #endif
      RTC_Serial_updater();
      break;
    }//end case
// ====================== SYSTEM REAL TIME CLOCK SNTP UPDATER ================
    case SYS_SNTP_UPDATE_RTC: {
      // #ifdef SERIAL_OUTPUT
      //   xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
      // #endif
      RTC_SNTP_updater();
      break;
    }//end case
// ================================= SYSTEM FAILED ===========================
    case SYS_FAILED: {
      oled_system_failed();
      while (!SW_midPressed());
      NVS_system_write(SYS_NORMAL);
      ESP.restart();
      break;
    }//end case
  }//end switch
//###################################################################################
//------------ CLEAN UP PROCEDURE - WILL NOT LIKELY TO HAPPEN OTHER THAN NORMAL OR NORMAL_DIRECT---------
  #ifdef SERIAL_OUTPUT //give change to core0 to initialize wifi
    xSemaphoreGive(serialLog_baton); //give out baton for other tasks to catch
  #endif
  #ifdef TASKS_MONITOR
    //make core1 main function wait for the taskMonitor to start
    xSemaphoreTake(taskMonitor_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html
    //release right after catched
    xSemaphoreGive(taskMonitor_baton); //give out baton for other tasks to catch
  #endif
  // #ifdef SERIAL_OUTPUT
  //   #ifdef TASKS_MONITOR
  //     xSemaphoreGive(taskMonitor_baton); //give out baton for other tasks to catch
  //   #endif
  //   xSemaphoreGive(serialLog_baton); //give out baton for other tasks to catch
  // #endif
/*******************************************************************************************/
/***************************************LOOP************************************************/
  //////////////////////MAIN WORKS LIE HERE//////////////////////
  Scenarios_update();// loop lies inside
  ///////////////////////////////////////////////////////////////
  //while (1) {
    //wifi_STA_serialUpdater();
    //wifi_STA_init();
  //  HTTP_send();
  //}
  //SD_AttenCheck_make();
  //SD_addClasses();
/*******************************************************************************************/
}//end Core1CombinedTask
#endif //_CORE1_CPP
