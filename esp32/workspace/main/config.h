/*------------------------------------------------------------*-
  Configuration file
  (c) An Minh Dao 2019
  version 2.00 - 09/02/2019
---------------------------------------------------------------
 * Basic settings for type of:
 * - Microcontroller
 * - SSID reader
 * - Buzzer
 * - TFT Screen controller
 * - RTC module
 * - SD card module
 * - CORE0
 * - MQTT WIFI CHANGEABLE
 * 
 * 
 * 
TASKS           STATE	PIORITY	STACK	NUM	CORE
IDLE1          	R	0	1012	7	1
IDLE0          	R	0	1020	6	0
TASKS_MONITOR  	R	0	456	14	-1
C1_Combined    	R	0	8176	13	1
C0_Combined    	B	0	3136	12	0
tiT            	B	18	2516	18	-1
Tmr Svc        	B	1	1628	8	0
network_event  	B	19	3620	16	-1
ipc0           	B	24	604	2	0
esp_timer      	B	22	3460	1	0
wifi           	B	23	1660	19	0
ipc1           	B	24	548	3	1
eventTask      	B	20	1960	17	0

TASKS           ABSOLUTE TIME	PERCENT TIME
IDLE1          	12888982		32%
IDLE0          	17055260		42%
TASKS_MONITOR  	84355		<1%
C1_Combined    	6809296		17%
C0_Combined    	8381		<1%
tiT            	106474		<1%
Tmr Svc        	18070		<1%
ipc0           	2762		<1%
ipc1           	158082		<1%
esp_timer      	30745		<1%
wifi           	2679112		6%
eventTask      	1187		<1%
network_event  	446		<1%

 * 
 * 
 * 
--------------------------------------------------------------*
* ADVANCED SETTING:
 * - In components/arduino/libraries/wifi/src/WifiGeneric.cpp
 *   + xTaskCreatePinnedToCore(_network_event_task, "network_event", 4096, NULL, ESP_TASKD_EVENT_PRIO - 1, &_network_event_task_handle, tskNO_AFFINITY);
 *     => changed variable function from ARDUINO_RUNNING_CORE (core1) to tskNO_AFFINITY (either core is free)
 *   + if(event->event_id < 26) {log_d("Event: %d - %s", event->event_id, system_event_names[event->event_id]);}
 *     => add {} to the if command
 * - Turn on/off log:
 *    + Initial log: connect GPIO15 to GND
 *    + Bootloader log: make menuconfig --> Bootloader config --> Bootloader log verbosity --> No output
 *    + FreeRTOS, wifi, bluetooth log: make menuconfig --> Components config --> log output --> Default log verbosity --> No output
 * - Set panic action:
 *    make menuconfig --> Components config --> ESP32-specific --> Panic handler behavior
 * - Monitor which tasks running: vTaskList() (turn off when complete)
 *    make menuconfig --> Components config --> FreeRTOS --> Enable FreeRTOS trace facility
 *    make menuconfig --> Components config --> FreeRTOS --> Enable FreeRTOS stats formatting functions
 *    make menuconfig --> Components config --> FreeRTOS --> Enable display of xCoreID in vTaskList
 * - Monitor how much time tasks has been executed: vTaskGetRunTimeStats() (turn off when complete)
 *    make menuconfig --> Components config --> FreeRTOS --> Enable FreeRTOS to collect run time stats
 * - Make long filename in SD card:
 *    make menuconfig --> Components config --> FAT filesystem support --> Long filename support in heap
 *  --> Current setting: short filename (<=8 characters) - a 8.3 filename 
 *  --> in a 8.3 filename system, file and directory names are uppercase!
 *  readmore: https://en.m.wikipedia.org/wiki/8.3_filename
 * 
 * - Changed I2C default frequency in esp32-hal-i2c.c, 
 *   function i2cInit() from frequency = 100000L; to frequency = 400000L;
 * - PARTITION TABLE EDITED! original csv file located at: <ESPIDF>/components/partition_table/
 * --> make menuconfig --> Partition Table --> Custom partition table CSV
 * ---> open partition.csv in <workspace>/partition.csv
 * ---> change factory memory to 2Mb
 * 
 *  - Already TURN OFF Task watchdog for Idle tasks of core 1 and core 0
 * --> make menuconfig --> Components config --> ESP32-specific --> turn off Watch CPU0/1 Idle task
 * NOTE ABOUT NAME OF FILES:
 * C0  - module runs in core0 - combined task
 * C0I - module runs independently in a task in core1
 * C1  - module runs in core1 - combined task
 * C1I - module runs independently in a task in core1
 * N   - module runs in whichever core is free - combined task
 * NI  - module runs independently in a task in whichever core is free
 * 
 * 
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: newest
--------------------------------------------------------------*/
#ifndef _CONFIG_H
#define _CONFIG_H

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////MODE CONFIGS/////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------
// USER DEFINE
// - SLASS OUT ANY OPTION THAT YOU DON'T WANT TO HAVE
//--------------------------------------------------------------
#define ESP32_DEBUG
#define WIFI_CHANGEABLE
#define SERIAL_OUTPUT
//#define TASKS_MONITOR //remember to change menuconfig when this is active

//CANNOT BE CHANGED!
#define MAX_CLASSES 15 //maximum value put here is 15 (dependance from Fram_mainAct)
//--------------------------------------------------------------
// MAIN LIBRARY - WILL NEED TO EDIT THIS SECTION FOR EVERY PROJECT
//-------------------------------------------------------------
// Must include the appropriate microcontroller header file here
#include "WiFi.h" //for esp32
//#include <ESP8266WiFi.h> //this use for esp8266, but you have to change const char to #define

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
//--------------------------------------------------------------
// MICROCONTROLLER
//--------------------------------------------------------------
#define ESP32_DEVKIT_V1

//--------------------------------------------------------------
// SSID READER
//--------------------------------------------------------------
//No config needed

//--------------------------------------------------------------
// OLED SCREEN
//--------------------------------------------------------------
#define OLED_PIORITY  9
//--------------------------------------------------------------
// RTC MODULE
//--------------------------------------------------------------

//--------------------------------------------------------------
// SD CARD
//--------------------------------------------------------------
const String ACHECK_LOCATION PROGMEM  = "/database/";
const String ACLASS_LOCATION PROGMEM  = "/Import/";
const String AWAIT_LOCATION  PROGMEM  = "/Await/";
const String SENT_LOCATION   PROGMEM  = "/Sent/";
#define YES 0
#define NO  1
//--------------------------------------------------------------
// CORE0 - CORE1
//--------------------------------------------------------------
#define DEFAULT_PIORITY  1
//--------------------------------------------------------------
// MQTT WIFI CHANGEABLE
//--------------------------------------------------------------
#define AMOUNT_SEND 70
//--------------------------------------------------------------
// HTTP CLIENT
//--------------------------------------------------------------
const String GETCLAS_API PROGMEM = "/api/requestClass";
const String GETSTUS_API PROGMEM = "/api/requestSV?class=";
const String SEND_API    PROGMEM = "/api/checkinjs";
#define GOOD      0
#define NOTG      1
#define NO_WIFI   2
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////CRUCIAL CONFIGS//////////////////////////////////////////////////////////////////
typedef enum {
  SYS_NORMAL,
  SYS_NORMAL_DIRECT,
  SYS_ADD_CLASSES, //use direct wifi to add classes
  // auto EXPORT DATA is intergrated inside NORMAL MODE
  // manually IMPORT DATA is lying inside main menu,no need to have this mode
  SYS_SERIAL_UPDATE_WIFI,
  SYS_BLE_UPDATE_WIFI,
  SYS_SERIAL_UPDATE_RTC,
  SYS_SNTP_UPDATE_RTC,

  SYS_FAILED = 99
} SystemState;

typedef enum {
	BUT_PUSHED = 1,
	BUT_RELEASED = 3,
	BUT_DISABLED = 99,
} MachineState;

typedef enum {
    ATTENDANCE_CHECK=1,
    ADD_CLASSES,
    ADD_MANUALLY,
    EXPORT_DATA,
    WIFI_UART_UPDATER,
    WIFI_BLE_UPDATER,
    RTC_UART_UPDATER,
    RTC_SNTP_UPDATER,
    AUTO_EXPORT,
    CLEAR_SENT
} FirstLayerPointer;

typedef enum {
    INIT_BACK=1,
    CHOOSE_CLASS,
    DELETE_CLASS,
    DELETE_ALL
} ACInitPointer;

typedef enum {
    CLASS1=2,
    CLASS2,
    CLASS3,
    CLASS4,
    CLASS5,
    CLASS6,
    CLASS7,
    CLASS8,
    CLASS9,
    CLASS10,
    CLASS11,
    CLASS12,
    CLASS13,
    CLASS14,
    CLASS15
} SecondLayerPointer;
//--------------------------------------------------------------
// TYPE DEFINITION
//--------------------------------------------------------------
typedef uint8_t uByte;
typedef uint16_t uInt;
typedef uint32_t uLong;

//--------------------------------------------------------------
// DEBUG AND LOG PRINTING
//-------------------------------------------------------------

const String VOID             PROGMEM = "        "; //8 space

const String MES_WF_FAIL      PROGMEM = "Wifi Failed";
const String MES_GER          PROGMEM = "Get Error!";
const String MES_EER          PROGMEM = "Export Error!";
const String MES_EOK          PROGMEM = "Export Done!";
const String MES_UART         PROGMEM = "Use UART to update";
const String MES_BLE          PROGMEM = "Use phone to update";
const String MES_WAIT         PROGMEM = "Waiting... ";
const String MES_CONNECT      PROGMEM = "Connecting...";
const String MES_RETURN       PROGMEM = "Returning... ";
const String MES_REMAIN       PROGMEM = "Remaining:";
const String MES_TRY          PROGMEM = "Try again ";
const String MES_CFAIL        PROGMEM = "Class Failed!";
const String MES_CADD         PROGMEM = "Class Added!";
const String MES_RECHECK      PROGMEM = "Please check again";
const String MES_RECEIVE      PROGMEM = "Command Recieved";
const String MES_RESTART      PROGMEM = "Press to restart!";
const String MES_CBACK        PROGMEM = "Press to come back!";
const String MES_COINCIDE     PROGMEM = "Already saved! Next.";
const String MES_NORMAL       PROGMEM = "Returning to NORMAL MODE...";

const String OPT_1  PROGMEM = "1.Attend.Check";
const String OPT_2  PROGMEM = "2.Add Classes";
const String OPT_3  PROGMEM = "3.Add Manually";
const String OPT_4  PROGMEM = "4.Export Data";
const String OPT_5  PROGMEM = "5.Wifi UART Updater";
const String OPT_6  PROGMEM = "6.Wifi BLE Updater ";
const String OPT_7  PROGMEM = "7.RTC UART Updater ";
const String OPT_8  PROGMEM = "8.RTC SNTP Updater ";
const String OPT_9  PROGMEM = "9.Auto Export: ";
const String OPT_10 PROGMEM = "10.Clear Sent Data ";

const String OPT_BACK  PROGMEM = "Back    ";
const String OPT_CHOSE PROGMEM = "Choose Class"; //have to be class choose to avoid coincide
const String OPT_DEL   PROGMEM = "Delete Class"; //have to be class choose to avoid coincide
const String OPT_DELA  PROGMEM = "Delete All Class"; //have to be class choose to avoid coincide

const String OPT_GET_ID    PROGMEM   = " Get Cards Info:";

const String OPT_WF_UART   PROGMEM   = "WIFI UART UPDATER";

const String OPT_WF_BLE    PROGMEM   = "WIFI BLE UPDATER";

const String OPT_RTC_UART  PROGMEM   = "RTC UART UPDATER";

const String OPT_RTC_SNTP  PROGMEM   = "RTC SNTP UPDATER";


#ifdef ESP32_DEBUG // When this is active, every log will be execute.
  #ifndef SERIAL_OUTPUT
    #define SERIAL_OUTPUT
  #endif
  #ifndef WIFI_CHANGEABLE
    #define WIFI_CHANGEABLE
  #endif
  #ifndef SERIAL_BEGIN
    #define SERIAL_BEGIN()      {Serial.begin(115200);}
  #endif
  #define D_PRINT(...)       {Serial.print(__VA_ARGS__);}
  #define D_PRINTLN(...)     {Serial.println(__VA_ARGS__);}
  #define D_PRINTF(...)      {Serial.printf(__VA_ARGS__);}
#else
  #define D_PRINT(...)   {}
  #define D_PRINTLN(...) {}
  #define D_PRINTF(...)  {}
#endif

#ifdef WIFI_CHANGEABLE
  #ifndef SERIAL_BEGIN
    #define SERIAL_BEGIN()      {Serial.begin(115200);}
  #endif
#endif

#ifdef SERIAL_OUTPUT
  #ifndef SERIAL_BEGIN
    #define SERIAL_BEGIN()      {Serial.begin(115200);}
  #endif
  #define S_PRINT(...)       {Serial.print(__VA_ARGS__);}
  #define S_PRINTLN(...)     {Serial.println(__VA_ARGS__);}
  #define S_PRINTF(...)      {Serial.printf(__VA_ARGS__);}
#else
  #ifndef SERIAL_BEGIN
    #define SERIAL_BEGIN()  {}
  #endif
  #define S_PRINT(...)   {}
  #define S_PRINTLN(...) {}
  #define S_PRINTF(...)  {}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_CONFIG_H
