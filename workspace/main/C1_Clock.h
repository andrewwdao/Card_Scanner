/*------------------------------------------------------------*-
  CLOCK DISPLAY TASK - header file
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
#ifndef _C1_CLOCK_H
#define _C1_CLOCK_H
#include "config.h"
#include <esp32-hal-timer.h>
#include "C1_OLED.h"
// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
bool Clock_init(uint8_t); //need to put current second to this function to make it refresh exactly every minutes
void clockEnable();
void clockDisable();
bool clockIsActivated();
void clockDeactivate();
/*
  xSemaphoreGive(Clock_baton);
  xSemaphoreTake(Clock_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
*/
// ------ Public variable -------------------------------------
//extern SemaphoreHandle_t Clock_baton;
#endif//_C1_CLOCK_H