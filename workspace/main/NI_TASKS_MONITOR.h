/*------------------------------------------------------------*-
  FREERTOS TASKS MONITOR - header file
  N - NEUTRAL: either core is free will run this task when it's time
  I - INDIVIDUAL: a separate task
  (c) An Minh Dao 2019
  version 1.20 - 10/02/2019
---------------------------------------------------------------
 *  CAUTION:
 *  MUST MAKE THESE CHANGE BEFORE PROCEED:
 *  - Monitor which tasks running: vTaskList() (turn off when complete)
 *     make menuconfig --> Components config --> FreeRTOS --> Enable FreeRTOS trace facility
 *     make menuconfig --> Components config --> FreeRTOS --> Enable FreeRTOS stats formatting functions
 *     make menuconfig --> Components config --> FreeRTOS --> Enable display of xCoreID in vTaskList
 *        READ MORE:
 *          'B' - Blocked
 *          'R' - Ready
 *          'D' - Deleted (waiting clean up)
 *          'S' - Suspended, or Blocked without a timeout
 *          https://www.freertos.org/a00021.html#vTaskList
 *          https://www.esp32.com/viewtopic.php?t=5218
 * - Monitor how much time tasks has been executed: vTaskGetRunTimeStats() (turn off when complete)
 *    make menuconfig --> Components config --> FreeRTOS --> Enable FreeRTOS to collect run time stats
 *        READ MORE:
 *          https://www.freertos.org/rtos-run-time-stats.html

 *  P/S CAUTION: must include config.h
--------------------------------------------------------------*/
#ifndef _NI_TASKS_MONITOR_H
#define _NI_TASKS_MONITOR_H
#include "config.h"

#ifdef TASKS_MONITOR

// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
void TASKS_MONITOR_init();
/*
  xSemaphoreGive(taskMonitor_baton);
  xSemaphoreTake(taskMonitor_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
*/
// ------ Public variable -------------------------------------
extern SemaphoreHandle_t taskMonitor_baton;
#endif //TASKS_MONITOR
#endif//_NI_TASKS_MONITOR_H