/*------------------------------------------------------------*-
  Module OLED 12864 1.3 inch 128x64 pixel - functions file
  ESP32 CORE1 - APPLICATION CORE
  (c) An Minh Dao 2019
  version 1.00 - 18/02/2019
---------------------------------------------------------------
 *  PUBLIC FUNCTIONS CONTAIN:
 *   
 *  PRIVATE FUNCTIONS CONTAIN:
 * 
 * 
**** NOTE: - use I2C communication -- I2C IS NOT GOOD FOR SCREEN! TOO SLOW!!!
 *         - max 21 character
 *         - 8 pixel = 1 row
 *         - there are 8 row
 *         - name limited to 17 character
 *         - need to clear oled EVERY NEW oled function
 * 
 --------------------------------------------------------------*/
#ifndef _C1_OLED_CPP
#define _C1_OLED_CPP
#include "C1_OLED.h"

// ------ Private constants -----------------------------------
static const unsigned char PROGMEM ctu_logo[] = { 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4d, 0xb2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x99, 0xd9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x33, 0xec, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x67, 0xf6, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xcf, 0xfb, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x9d, 0xfd, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x38, 0xfe, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x70, 0x0f, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4c, 0xf0, 0x37, 0xb2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x99, 0xf0, 0x07, 0xd9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x33, 0x80, 0x07, 0xec, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x67, 0x90, 0x00, 0x76, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xcf, 0x1c, 0x18, 0x3b, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x98, 0x3e, 0x3c, 0x1d, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x30, 0xfe, 0x3c, 0x1e, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x73, 0xfe, 0x3f, 0x0f, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x4c, 0xe3, 0xfe, 0x3f, 0x07, 0xb2, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x99, 0xe3, 0xfe, 0x7f, 0x87, 0xd9, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0x33, 0xf3, 0xfe, 0x3f, 0x87, 0xec, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x02, 0x67, 0xf7, 0xfe, 0x3f, 0xc3, 0xf6, 0x40, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x04, 0xdf, 0xc7, 0xfe, 0x7f, 0xc3, 0xfb, 0x20, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x09, 0xdf, 0xc7, 0xfe, 0x7f, 0xc3, 0xfb, 0x90, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x13, 0xef, 0xcf, 0xff, 0x78, 0xc3, 0xf7, 0xc8, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x27, 0x77, 0xcf, 0xdf, 0x7d, 0xc3, 0xee, 0xe4, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x4e, 0x3b, 0xc7, 0xf7, 0x75, 0xc7, 0xdc, 0x72, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x4c, 0x1d, 0xe3, 0xf7, 0xff, 0xc3, 0xb8, 0x72, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x24, 0x0e, 0xf3, 0xf7, 0xef, 0x87, 0x79, 0x24, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x12, 0x1f, 0x7b, 0xff, 0xdf, 0x86, 0xe0, 0x48, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x09, 0x23, 0xb3, 0xf7, 0xbf, 0x0d, 0xe0, 0x90, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x04, 0xc3, 0xd3, 0xf7, 0xfe, 0x0b, 0x83, 0x20, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x02, 0x43, 0xe0, 0x77, 0xfc, 0x17, 0x0a, 0x40, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x70, 0x3f, 0xf8, 0x0e, 0x44, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x94, 0xf8, 0x8f, 0x80, 0x1c, 0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0xfd, 0xce, 0x00, 0x3c, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0xce, 0xc0, 0x01, 0x7f, 0xa4, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x8f, 0x61, 0x8e, 0xe7, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x03, 0xbf, 0xfd, 0xe3, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xe3, 0xdf, 0xfb, 0x81, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 0xef, 0xf5, 0x82, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x39, 0x77, 0xec, 0x44, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x93, 0x7b, 0xde, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x1d, 0xbe, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x06, 0x73, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x27, 0xe6, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x37, 0xe4, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x8f, 0xe1, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x7f, 0xf2, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x3f, 0xfc, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 0xf9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4f, 0xf2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0xe4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

// ------ Private function prototypes -------------------------
void oled_display();
void oled_showSession();

// ------ Private variables -----------------------------------
//static String preMSSV="";
//static String preName="";

// ------ PUBLIC variable definitions -------------------------
Adafruit_SH1106 oled(I2C_SDA_PIN, I2C_SCL_PIN);

//--------------------------------------------------------------
// FUNCTION DEFINITIONS - FOR CORE0
//--------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------- SYSTEM FAILED FUNCTION -------------------------------------
//------------------------------------------------------------------------------------------
void oled_system_failed() {
  
  oled.begin(SH1106_SWITCHCAPVCC, 0x3C); /* initialize OLED with I2C address 0x3C */
  oled.clearDisplay(); // Clear the buffer.
  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  oled.setCursor(25,20); oled.print("System failed");
  oled.setTextColor(WHITE, BLACK); // normal text
  oled.setCursor(38,38); oled.print(MES_TRY);
  oled.setCursor(16,50); oled.print(MES_RESTART);
  oled_display(); //columm, row --- cot, hang
}//end oled_wifi_SerialUpdater
//------------------------------- SD FAILED FUNCTION ------------------------------
//------------------------------------------------------------------------------------------
void oled_SD_failed() {
  
  oled.clearDisplay(); // Clear the buffer.
  oled.setTextSize(2);
  oled.setCursor(13,20); oled.print("SD failed");
  oled.setTextSize(1);
  oled.setCursor(13,38); oled.print(MES_RECHECK);
  oled.setCursor(16,50); oled.print(MES_RESTART);
  oled_display(); //columm, row --- cot, hang
}//end SD_failed
//------------------------------- WIFI FAILED FUNCTION ------------------------------
//------------------------------------------------------------------------------------------
void oled_wifi_failed() {
  
  oled.clearDisplay(); // Clear the buffer.
  oled.setCursor(27,30); oled.print(MES_WF_FAIL);
  oled_display(); //columm, row --- cot, hang
  oled.setCursor(8,50); oled.print(MES_CBACK);
  oled_display(); //columm, row --- cot, hang
}//end SD_failed
void oled_get_error() {
  
  oled.clearDisplay(); // Clear the buffer.
  oled.setCursor(27,30); oled.print(MES_GER);
  oled_display(); //columm, row --- cot, hang
}//end oled_get_error
void oled_Export_ok() {
  
  oled.clearDisplay(); // Clear the buffer.
  oled.setCursor(27,30); oled.print(MES_EOK);
  oled_display(); //columm, row --- cot, hang
}//end oled_Export_ok
void oled_Ex_error() {
  
  oled.clearDisplay(); // Clear the buffer.
  oled.setCursor(27,30); oled.print(MES_EER);
  oled_display(); //columm, row --- cot, hang
}//end oled_Ex_error
void oled_comeBack() {
  oled.setCursor(8,50); oled.print(MES_CBACK);
  oled_display(); //columm, row --- cot, hang
}//end oled_comeBack
//------------------------------------------------------------------------------------------
//------------------------------- WIFI FAILED FUNCTION -------------------------------------
//------------------------------------------------------------------------------------------
void oled_wifi_SerialUpdater() {
  
  oled.begin(SH1106_SWITCHCAPVCC, 0x3C); /* initialize OLED with I2C address 0x3C */
  oled.clearDisplay(); // Clear the buffer.
  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  oled.setCursor(12,20); oled.print(OPT_WF_UART);
  oled.setTextColor(WHITE, BLACK); // normal text
  oled.setCursor(10,38); oled.print(MES_UART);
  oled.setCursor(40,50); oled.print(MES_WAIT);
  oled_display(); //columm, row --- cot, hang
}//end oled_wifi_SerialUpdater
void oled_wifi_BLEupdater() { //run on core1
  
  oled.begin(SH1106_SWITCHCAPVCC, 0x3C); /* initialize OLED with I2C address 0x3C */
  oled.clearDisplay(); // Clear the buffer.
  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  oled.setCursor(17,20); oled.print(OPT_WF_BLE);
  oled.setTextColor(WHITE, BLACK); // normal text
  oled.setCursor(8,38); oled.print(MES_BLE);
  oled.setCursor(45,50); oled.print(MES_WAIT);
  oled_display(); //columm, row --- cot, hang
}//end oled_wifi_BLEUpdater
void oled_BLE_receivedData() { //run on core0
  
  oled.begin(SH1106_SWITCHCAPVCC, 0x3C); /* initialize OLED with I2C address 0x3C */
  oled.clearDisplay(); // Clear the buffer.
  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  oled.setCursor(17,20); oled.print(OPT_WF_BLE);
  oled.setTextColor(WHITE, BLACK); // normal text
  oled.setCursor(17,38); oled.print(MES_RECEIVE);
  oled.setCursor(35,50); oled.print(MES_CONNECT);
  oled_display(); //columm, row --- cot, hang
}//end oled_BLE_receivedData
void oled_BLE_eraseData() {//run on core0
  
  oled.begin(SH1106_SWITCHCAPVCC, 0x3C); /* initialize OLED with I2C address 0x3C */
  oled.clearDisplay(); // Clear the buffer.
  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  oled.setCursor(17,20); oled.print(OPT_WF_BLE);
  oled.setTextColor(WHITE, BLACK); // normal text
  oled.setCursor(17,38); oled.print(MES_RECEIVE);
  oled.setCursor(43,50); oled.print("Erased!");
  oled_display(); //columm, row --- cot, hang
}//end oled_wifi_BLEUpdater
void oled_BLE_wifiFailed() {//run on core1
  
  oled.begin(SH1106_SWITCHCAPVCC, 0x3C); /* initialize OLED with I2C address 0x3C */
  oled.clearDisplay(); // Clear the buffer.
  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  oled.setCursor(17,20); oled.print(OPT_WF_BLE);
  oled.setTextColor(WHITE, BLACK); // normal text
  oled.setCursor(25,38); oled.print(MES_WF_FAIL);
  oled.setCursor(38,50); oled.print(MES_TRY);
  oled_display(); //columm, row --- cot, hang
}//end oled_BLE_wifiFailed
void oled_showSession() { //always runs on core1
  oled.setCursor(80,0); oled.print(RTC_getSession());
}//end oled_Clock_Updater
void oled_RTC_SerialUpdater() {
  
  oled.begin(SH1106_SWITCHCAPVCC, 0x3C); /* initialize OLED with I2C address 0x3C */
  oled.clearDisplay(); // Clear the buffer.
  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  oled.setCursor(17,20); oled.print(OPT_RTC_UART);
  oled.setTextColor(WHITE, BLACK); // normal text
  oled.setCursor(10,38); oled.print(MES_UART);
  oled.setCursor(40,50); oled.print(MES_WAIT);
  oled_display(); //columm, row --- cot, hang
}//end oled_RTC_SerialUpdater
void oled_RTC_SNTPupdater1() {
  
  oled.begin(SH1106_SWITCHCAPVCC, 0x3C); /* initialize OLED with I2C address 0x3C */
  oled.clearDisplay(); // Clear the buffer.
  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  oled.setCursor(17,20); oled.print(OPT_RTC_SNTP);
  oled.setTextColor(WHITE, BLACK); // normal text
  oled.setCursor(28,38); oled.print(MES_CONNECT);
  oled.setCursor(38,50); oled.print(MES_WAIT);
  oled_display(); //columm, row --- cot, hang
}//end oled_RTC_SNTPupdater1
void oled_RTC_SNTPupdater2() {
  if (wifi_isConnected()) {
    oled.setCursor(5,38); oled.print("     Connected!     ");
  } else {
    oled.setCursor(5,38); oled.print("    Wifi failed!    ");
    oled.setCursor(32,50); oled.print(MES_RETURN);
  }//end if else
    oled_display(); //columm, row --- cot, hang
}//end oled_RTC_SNTPupdater2
void oled_RTC_SNTPupdater3(bool SNTPok) {
  if (SNTPok) {
    oled.setCursor(18,38); oled.print("     DONE!     ");//class 2
    oled.setCursor(32,50); oled.print(MES_RETURN);//class 3

  } else {
    oled.setCursor(18,38); oled.print("    FAILED!    ");//class 2
    oled.setCursor(35,50); oled.print(MES_TRY);//class 3
  }//end if else
    oled_display(); //columm, row --- cot, hang
}//end oled_RTC_SNTPupdater3
//--------------------------------------------------------------
// FUNCTION DEFINITIONS - FOR CORE1
//--------------------------------------------------------------
void oled_init_c1() {
  
  oled.begin(SH1106_SWITCHCAPVCC, 0x3C); /* initialize OLED with I2C address 0x3C */
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
}//end oled_init
void oled_ctuLogo() {
  oled.drawBitmap(0,0,ctu_logo,128,64, WHITE); //initialize bitmap
  oled_display(); // Show image buffer on the oled hardware.
}//end oled_ctuLogo
void oled_display() {
  vTaskPrioritySet(Core1_combined, OLED_PIORITY); //change task piority to 5
  oled.display(); // Show image buffer on the oled hardware.
  vTaskPrioritySet(Core1_combined, DEFAULT_PIORITY); //change task piority to 0
}//end oled_display
void oled_clear() {
  oled.clearDisplay();
}//oled_clear
//------------------------------- POINTER ------------------------------
//------------------------------------------------------------------------------------------
void oled_POINTER1() {
  oled.setCursor(0,18); oled.print(">");//option 1
  oled.setCursor(0,29); oled.print(" ");//option 2
  oled.setCursor(0,40); oled.print(" ");//option 3
  oled.setCursor(0,51); oled.print(" ");//option 4
  //oled_display(); //columm, row --- cot, hang
}//end oled_POINTER1
void oled_POINTER2() {
  oled.setCursor(0,18); oled.print(" ");//option 1
  oled.setCursor(0,29); oled.print(">");//option 2
  oled.setCursor(0,40); oled.print(" ");//option 3
  oled.setCursor(0,51); oled.print(" ");//option 4
  //oled_display(); //columm, row --- cot, hang
}//end oled_POINTER2
void oled_POINTER3() {
  oled.setCursor(0,18); oled.print(" ");//option 1
  oled.setCursor(0,29); oled.print(" ");//option 2
  oled.setCursor(0,40); oled.print(">");//option 3
  oled.setCursor(0,51); oled.print(" ");//option 4
  //oled_display(); //columm, row --- cot, hang
}//end oled_POINTER3
void oled_POINTER4() {
  oled.setCursor(0,18); oled.print(" ");//option 1
  oled.setCursor(0,29); oled.print(" ");//option 2
  oled.setCursor(0,40); oled.print(" ");//option 3
  oled.setCursor(0,51); oled.print(">");//option 4
  //oled_display(); //columm, row --- cot, hang
}//end oled_POINTER4
//------------------------------- MODE 0: MAIN MENU ------------------------------
//------------------------------------------------------------------------------------------
void oled_mainMenu_init() {
  oled.clearDisplay(); // Clear the buffer.
  oled_showSession();
  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  oled.setCursor(0,0); oled.println(" Main Menu:");
  oled.setTextColor(WHITE, BLACK); // normal text
  oled_POINTER1();oled_mainMenu_1();
}//end oled_mainMenu_init
void oled_mainMenu_1() {
  oled.setCursor(13,18); oled.print(OPT_1+"     ");//option 1
  oled.setCursor(13,29); oled.print(OPT_2+"     ");//option 2
  oled.setCursor(13,40); oled.print(OPT_3+"     ");//option 3
  oled.setCursor(13,51); oled.print(OPT_4+"     ");//option 4
  oled_display(); //columm, row --- cot, hang
}//end oled_mainMenu_1
void oled_mainMenu_2() {
  oled.setCursor(13,18); oled.print(OPT_5);//option 5
  oled.setCursor(13,29); oled.print(OPT_6);//option 6
  oled.setCursor(13,40); oled.print(OPT_7);//option 7
  oled.setCursor(13,51); oled.print(OPT_8);//option 8
  oled_display(); //columm, row --- cot, hang
}//end oled_mainMenu_2
void oled_mainMenu_3() {
  oled.setCursor(13,18); 
  if (NVS_AExMode_read())  {oled.print(OPT_9+"ON  ");}//option 9
  else                     {oled.print(OPT_9+"OFF ");}//option 9
  oled.setCursor(13,29); oled.print(OPT_10);//option 10
  oled.setCursor(13,40); oled.print(VOID+VOID+"   ");//nothing
  oled.setCursor(13,51); oled.print(VOID+VOID+"   ");//nothing
  oled_display(); //columm, row --- cot, hang
}//end oled_mainMenu_3
void oled_done() {
  
  //oled.begin(SH1106_SWITCHCAPVCC, 0x3C); /* initialize OLED with I2C address 0x3C */
  oled.clearDisplay(); // Clear the buffer.
  oled.setTextSize(2);
  oled.setCursor(36,30); oled.print("DONE!");//class 1
  oled.setTextSize(1);
  oled_display(); //columm, row --- cot, hang
}//end oled_done
//------------------------------- MODE 1: ATTENDANCE CHECKING ------------------------------
//------------------------------------------------------------------------------------------
void oled_Frame1_init(String ACopt) {
  oled.clearDisplay(); // Clear the buffer.
  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  oled.setCursor(0,0); oled.println(ACopt);
  oled.setTextColor(WHITE, BLACK); // normal text
}//end oled_Frame1_init()
void oled_Frame1_menu() {//use for both "check attendance" and "add class" mode
  oled.setCursor(13,18); oled.print(OPT_BACK);//option 1
  oled.setCursor(13,29); oled.print(OPT_CHOSE); //option 2
  oled.setCursor(13,40); oled.print(OPT_DEL);//option 3
  oled.setCursor(13,51); oled.print(OPT_DELA);//option 4
  oled_display(); //columm, row --- cot, hang
}//end oled_Frame1heck_1
void oled_Frame1_mode(String Frame1mode) {

  oled.clearDisplay(); // Clear the buffer.
  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  oled.setCursor(0,0); oled.println(Frame1mode);
  oled.setTextColor(WHITE, BLACK); // normal text
}//end oled_Frame1_mode
void oled_Frame1_Class1(String* CC1) {
  oled.setCursor(13,18); oled.print(OPT_BACK);//option 1
  oled.setCursor(13,29); oled.print((*CC1).c_str());//option 2
  oled.setCursor(13,40); oled.print((*(CC1+1)).c_str());//option 3
  oled.setCursor(13,51); oled.print((*(CC1+2)).c_str());//option 4
  oled_display(); //columm, row --- cot, hang
}//end oled_Frame1_Class1
void oled_Frame1_Class2(String* CC1) {
  oled.setCursor(13,18); oled.print((*(CC1+3)).c_str());//option 1
  oled.setCursor(13,29); oled.print((*(CC1+4)).c_str());//option 2
  oled.setCursor(13,40); oled.print((*(CC1+5)).c_str());//option 3
  oled.setCursor(13,51); oled.print((*(CC1+6)).c_str());//option 4
  oled_display(); //columm, row --- cot, hang
}//end oled_Frame1_Class2
//ATTENDANCE CHECK
void oled_Acheck_make() { //no oled.display!!!
  oled.clearDisplay(); // Clear the buffer.
  oled_showSession();
  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  oled.setCursor(0,0); oled.println("Scan mode");
  oled.setTextColor(WHITE, BLACK); // normal text
  oled.setTextSize(2);
  oled.setCursor(5,20); oled.print(MES_WAIT);
  oled.setTextSize(1);
  // oled_display(); //columm, row --- cot, hang
}//end oled_Acheck_make
void oled_Acheck_remain(int StuLeft) {
  oled.setCursor(0,50);  oled.print(MES_REMAIN);
  oled.setCursor(60,50); oled.print("     ");
  oled.setCursor(60,50); oled.print(StuLeft);
  if (StuLeft>99) {
    oled.setCursor(79,50);
  } else if (StuLeft>9) {
    oled.setCursor(76,50);
  } else {
    oled.setCursor(70,50); 
  }//end if else
  oled.print("Students");
  oled_display(); //columm, row --- cot, hang
}//end oled_Acheck_coincide
void oled_Acheck_coincide() {
  oled.setCursor(0,50); oled.print(MES_COINCIDE);
  oled_display(); //columm, row --- cot, hang
}//end oled_Acheck_coincide
void oled_Acheck_makeDone(String StuName,String StuID) {
  oled.clearDisplay(); // Clear the buffer.
  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  oled.setCursor(0,16); oled.println(" ID catched:");
  oled.setTextColor(WHITE, BLACK); // normal text
  oled.setCursor(0,29); oled.print("Name:");
  oled.setCursor(30,29); oled.print(StuName.c_str()); //5*6=30
  oled.setCursor(0,40); oled.print("ID  :");
  oled.setCursor(30,40); oled.print(StuID.c_str()); //15 space
  oled_display(); //columm, row --- cot, hang
}//end oled_Acheck_makeDone
void oled_Acheck_saved() {
  oled.setCursor(0,55); oled.print(F("Saved!"));
  oled_display();//columm, row --- cot, hang
}//end oled_Acheck_saved
void oled_Acheck_failed() {
    oled.setCursor(0,55); oled.print("Failed!");
    oled_display();//columm, row --- cot, hang
}//end oled_Acheck_failed
void oled_ACheck_done() {
  oled_done();
  oled.setCursor(10,50); oled.print(MES_CBACK);
  oled_display();
}//end oled_ACheck_done
//------------------------------- MODE 2: GET RFID INFO ------------------------------------
//------------------------------------------------------------------------------------------
void oled_connect() {
  
  oled.clearDisplay(); // Clear the buffer.
  oled.setCursor(27,30); oled.print(MES_CONNECT);
  oled_display(); //columm, row --- cot, hang
}//end oled_connect
void oled_getRFID_init() {
  oled.clearDisplay(); // Clear the buffer.
  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  oled.setCursor(0,16); oled.println(OPT_GET_ID);
  oled.setTextColor(WHITE, BLACK); // normal text
  oled.setCursor(0,29); oled.print("Name:");
  oled.setCursor(0,40); oled.print("ID  :");
  oled.setCursor(0,55); oled.print(MES_WAIT);
  oled_display(); //columm, row --- cot, hang
}//end oled_getRFID_info_init
void oled_getRFID_info(String mssvBuffer, String nameBuffer,String MESBuf) {
  oled.setCursor(30,29); oled.println(nameBuffer.c_str()); //15 space
  oled.setCursor(30,40); oled.println(mssvBuffer.c_str()); //15 space
  oled.setCursor(0,55); oled.print(MES_WAIT+MESBuf); //15 space
  oled_display();//columm, row --- cot, hang
}//end oled_getRFID_info
void oled_getRFID_status(String IDstatus) {
  oled.setCursor(0,55); oled.print(IDstatus + VOID);//21 spaces
  oled_display();
}//end oled_getRFID_info_end
void oled_getRFID_end(String mStat,String classStat) {
  oled.clearDisplay(); // Clear the buffer.
  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  oled.setCursor(0,16); oled.println(OPT_GET_ID);
  oled.setTextColor(WHITE, BLACK); // normal text
  oled.setCursor(0,29); oled.print(mStat);
  oled.setCursor(0,40); oled.print(classStat);
  oled.setCursor(0,55); oled.print(MES_RESTART);
  oled_display(); //columm, row --- cot, hang
  delay(800);
}//end oled_getRFID_end
//------------------------------------------------------------------------------------------

void oled_AClass_override() {
  oled.setCursor(13,18); oled.print("File Existed!");
  oled.setCursor(13,29); oled.print("Override this file?");
  oled.setCursor(13,40); oled.print("YES");
  oled.setCursor(13,51); oled.print("NO");
  oled_display(); //columm, row --- cot, hang
}//end oled_AClass_override

#endif //_C1_OLED_CPP