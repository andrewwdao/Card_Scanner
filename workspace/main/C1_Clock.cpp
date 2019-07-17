/*------------------------------------------------------------*-
  CLOCK DISPLAY TASK - functions file
  N - NEUTRAL: either core is free will run this task when it's time
  I - INDIVIDUAL: a separate task
  (c) An Minh Dao 2019
  version 1.00 - 04/04/2019
---------------------------------------------------------------
 *  
 * 
 * 
 * 
 * 
 * 
 * 
--------------------------------------------------------------*/
#ifndef _C1_CLOCK_CPP
#define _C1_CLOCK_CPP
#include "C1_Clock.h"


// ------ Private constants -----------------------------------
const int CLOCK_STACK   PROGMEM =  1000; // Stack size of Task1_CORE0 (in bytes- NOT words)
#define REPEAT    true
#define NO_REPEAT false
// ------ Private function prototypes -------------------------
static void Clock_firstCycle( void * parameter );
static void Clock_main( void * parameter );
void IRAM_ATTR FirstClockISR();
void IRAM_ATTR MainClockISR();
/*
  xSemaphoreGive(Clock_baton);
  xSemaphoreTake(Clock_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
*/
// ------ Private variables -----------------------------------
TaskHandle_t Clock_handle; //pointer
hw_timer_t *ClockTimer = NULL;
//callback_t   Clock_callback = (callback_t) ClockISR;
portMUX_TYPE ClockMux = portMUX_INITIALIZER_UNLOCKED;
// ------ PUBLIC variable definitions -------------------------
//extern SemaphoreHandle_t Clock_baton;
//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void IRAM_ATTR FirstClockISR() {
  portENTER_CRITICAL_ISR(&ClockMux);
  xTaskCreatePinnedToCore(
    Clock_firstCycle,                          /* Task Function */
    "Clock_init",                        /* Name of Task */
    CLOCK_STACK,                         /* Stack size of Task - in bytes (in normal FREERTOS it will be words)*/
    NULL,                                /* Parameter of the task */
    5,                                   /* Priority of the task, vary from 0 to N, bigger means higher piority, need to be 0 to be lower than the watchdog*/
    &Clock_handle,                       /* Task handle to keep track of created task */
    APP_CPU_NUM                          /* CoreID - CORE0: 0 or PRO_CPU_NUM - CORE1: 1 or APP_CPU_NUM - tskNO_AFFINITY: either one is free*/
  );
  portEXIT_CRITICAL_ISR(&ClockMux);
}//end FirstClockISR

void IRAM_ATTR MainClockISR() {
  portENTER_CRITICAL_ISR(&ClockMux);
  xTaskCreatePinnedToCore(
    Clock_main,                          /* Task Function */
    "Clock",                             /* Name of Task */
    CLOCK_STACK,                         /* Stack size of Task - in bytes (in normal FREERTOS it will be words)*/
    NULL,                                /* Parameter of the task */
    5,                                   /* Priority of the task, vary from 0 to N, bigger means higher piority, need to be 0 to be lower than the watchdog*/
    &Clock_handle,                       /* Task handle to keep track of created task */
    APP_CPU_NUM                          /* CoreID - CORE0: 0 or PRO_CPU_NUM - CORE1: 1 or APP_CPU_NUM - tskNO_AFFINITY: either one is free*/
  );
  portEXIT_CRITICAL_ISR(&ClockMux);
}//end MainClockISR

bool Clock_init(uint8_t ClockSecond) {
  ClockTimer = timerBegin(0, 80, true); //timer0, divided by 80 (1Mhz), counting up
  timerAttachInterrupt(ClockTimer, FirstClockISR, true);
  timerAlarmWrite(ClockTimer, (uint64_t)(60-ClockSecond)*1000000, NO_REPEAT); // 60s, no repeat
  timerAlarmEnable(ClockTimer);
  if (Clock_handle == NULL) {
    return false;
    } else { //task created successfully
      return true;
    }//end if else
}//end Clock_init

static void Clock_firstCycle( void * parameter ) {//task run on core0
  timerStop(ClockTimer);
  timerEnd(ClockTimer);
  ClockTimer = timerBegin(0, 80, true); //timer0, divided by 80 (1Mhz), counting up
  timerAttachInterrupt(ClockTimer, MainClockISR, true);
  timerAlarmWrite(ClockTimer, 60000000, REPEAT); // 60s, no repeat
  timerAlarmEnable(ClockTimer);
  if (ClockEnable) {
      oled_Clock_Updater();
  }//end if
  vTaskDelete(NULL);
}//end Clock_firstCycle

static void Clock_main( void * parameter ) {//task run on core0
  if (ClockEnable) {
    oled_Clock_Updater();
  }//end if

  vTaskDelete(NULL);
}//end Clock_main

/*******************************************************************************************/
#endif//_C1_CLOCK_CPP