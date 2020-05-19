/*--------------------------------------------------------------------------------*-
  3 State button - TS002 - header file
  ESP32 CORE1 - APPLICATION CORE
  (c) An Minh Dao - 2019
  version 3.00 - 09/04/2019
-------------------------------------------------------------------------------------
 *
 *  PUBLIC FUNCTIONS CONTAIN:
 * void SW_init();
 * void SW_setBoundaries(int8_t,int8_t,bool); ////avoid using 0 in between
 * void SW_enable();
 * void SW_disable();
 * void SW_set(int8_t);
 * int  SW_read(); //have to be in int to fit with enum
 * bool SW_posChanged();
 * //UP BUTTON
 * bool SW_upPressed();
 * bool SW_upPressedFor(TickType_t);
 * //MIDDLE BUTTON
 * bool SW_midPressed();
 * bool SW_midPressedFor(TickType_t);
 * //DOWN BUTTON
 * bool SW_dowPressed();
 * bool SW_dowPressedFor(TickType_t);
 * 
 *  PRIVATE FUNCTIONS CONTAIN:
 * static void IRAM_ATTR SWupbut_ISR();
 * static void IRAM_ATTR SWmidbut_ISR();
 * static void IRAM_ATTR SWdowbut_ISR();
 * 
 *  - Important Documents:
 * 		+ 
 -------------------------------------------------------------------------------------*/
#ifndef _C1_SWITCH_H
#define _C1_SWITCH_H
#include "config.h"
#include "pins.h"
#include "WiFi.h"
#include "C0_Wifi_sta_ch.h"
#include "N_RAM_RTC.h"
#include "core1.h"

// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
/* FUNCTION DEFINITIONS - CRUCIAL FUNCTIONS */
void SW_init();
void SW_setBoundaries(int8_t,int8_t,bool); ////avoid using 0 in between
void SW_enable();
void SW_disable();
void SW_set(int8_t);
int  SW_read(); //have to be in int to fit with enum
bool SW_posChanged();
//UP BUTTON
bool SW_upPressed();
bool SW_upPressedFor(TickType_t);
//MIDDLE BUTTON
bool SW_midPressed();
bool SW_midPressedFor(TickType_t);
//DOWN BUTTON
bool SW_dowPressed();
bool SW_dowPressedFor(TickType_t);
/* FUNCTION DEFINITIONS - APPLICATION FUNCTIONS */

// ------ Public variable -------------------------------------

#endif //_C1_SWITCH_H


// while(1) {
    // if (SW_posChanged()) {
    //     Serial.println(SW_read());
    //   }//end if

    //   if (SW_midPressed()) {
    //     Serial.println("Got it!");
    //   }//end if
    // }//end while
