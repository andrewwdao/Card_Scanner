/*------------------------------------------------------------*-
  FREERTOS TASKS MONITOR - functions file
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
 *      READ MORE:
 *          https://www.freertos.org/rtos-run-time-stats.html
--------------------------------------------------------------*/
#ifndef _NI_TASKS_MONITOR_CPP
#define _NI_TASKS_MONITOR_CPP
#include "NI_TASKS_MONITOR.h"

#ifdef TASKS_MONITOR

// ------ Private constants -----------------------------------
const int TASKS_MONITOR_STACK   PROGMEM =  3000; // Stack size of Task1_CORE0 (in bytes- NOT words)

// ------ Private function prototypes -------------------------
static void TASKS_MONITOR_begin( void * parameter );
static void taskRunningInfo();
static void taskRunningTime();
/*
  xSemaphoreGive(taskMonitor_baton);
  xSemaphoreTake(taskMonitor_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
*/
// ------ Private variables -----------------------------------
TaskHandle_t Tasks_monitor; //pointer
// ------ PUBLIC variable definitions -------------------------
extern SemaphoreHandle_t taskMonitor_baton;
//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------

void TASKS_MONITOR_init() {
    xTaskCreatePinnedToCore(
    TASKS_MONITOR_begin,                 /* Task Function */
    "TASKS_MONITOR",                     /* Name of Task */
    TASKS_MONITOR_STACK,                 /* Stack size of Task - in bytes (in normal FREERTOS it will be words)*/
    NULL,                                /* Parameter of the task */
    DEFAULT_PIORITY,                     /* Priority of the task, vary from 0 to N, bigger means higher piority, need to be 0 to be lower than the watchdog*/
    &Tasks_monitor,                      /* Task handle to keep track of created task */
    tskNO_AFFINITY);                     /* CoreID - CORE0: 0 or PRO_CPU_NUM - CORE1: 1 or APP_CPU_NUM - tskNO_AFFINITY: either one is free*/
}//end TASKS_MONITOR_init

static void TASKS_MONITOR_begin( void * parameter ) {//task run on core0
    vTaskDelay(500 / portTICK_PERIOD_MS); //make sure core0 take the baton first
    xSemaphoreTake(taskMonitor_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html
    while (1) {
        vTaskDelay(5000/portTICK_PERIOD_MS);
        taskRunningInfo();
        taskRunningTime();
        xSemaphoreGive(taskMonitor_baton); //give out baton for other tasks to catch
    }//end while

    //vTaskDelete(NULL);

}//end TASKS_MONITOR_begin

static void taskRunningInfo() {//information about tasks are running, manage by FREERTOS 

    char stats_buffer[1024];
    vTaskList(stats_buffer);
    D_PRINTLN(F("TASKS           STATE\tPIORITY\tSTACK\tNUM\tCORE"));
    D_PRINTLN(stats_buffer);

}//end taskRunningInfo
static void taskRunningTime() {//information about tasks are running, manage by FREERTOS 

    char runtime_stats[1024];
    vTaskGetRunTimeStats(runtime_stats);
    D_PRINTLN(F("TASKS           ABSOLUTE TIME\tPERCENT TIME"));
    D_PRINTLN(runtime_stats);

}//end taskRunningInfo
/*******************************************************************************************/

#endif //TASKS_MONITOR
#endif//_NI_TASKS_MONITOR_CPP