/*------------------------------------------------------------*-
  Pins assignment file
  (c) An Minh Dao 2019
  version 1.00 - 30/01/2019
---------------------------------------------------------------
 * Pin assigned for:
 * - SSID reader
 * - Buzzer
 * - TFT Screen
 * - RTC module
 * - SD card module
 * - CORE0
 * - MQTT WIFI CHANGEABLE
--------------------------------------------------------------*/
#ifndef _PINS_H
#define _PINS_H

//--------------------------------------------------------------
// CARD READER 125KHZ - RDM6300
//--------------------------------------------------------------
/*GPIO16 - RX2 to data pin of rf125khz*/ //USE A WHOLE UART PORT FOR DATA AQUISITION
#define RF_INTERRUPT_PIN  27
#define BUZZER_PIN        12      

//--------------------------------------------------------------
// OLED SCREEN - I2C 
//--------------------------------------------------------------
// - Changed I2C default frequency in esp32-hal-i2c.c, 
//  function i2cInit() from frequency = 100000L; to frequency = 400000L;
#define I2C_SDA_PIN  21 //automatically assigned
#define I2C_SCL_PIN  22 //automatically assigned
//--------------------------------------------------------------
// RTC MODULE - AT24C32 RAM IC - I2C
//--------------------------------------------------------------
// - Changed I2C default frequency in esp32-hal-i2c.c, 
//  function i2cInit() from frequency = 100000L; to frequency = 400000L;
#define I2C_SDA_PIN  21 //automatically assigned
#define I2C_SCL_PIN  22 //automatically assigned
//--------------------------------------------------------------
// SD CARD - SPI
//--------------------------------------------------------------
#define SPI_CS_PIN    5  //automatically assigned
#define SPI_CLK_PIN   18 //automatically assigned
#define SPI_MOSI_PIN  23 //automatically assigned
#define SPI_MISO_PIN  19 //automatically assigned
//--------------------------------------------------------------
// SWITCH
//--------------------------------------------------------------
#define SW_UP_PIN    32 //automatically assigned
#define SW_MID_PIN   4  //automatically assigned
#define SW_DOW_PIN   33 //automatically assigned
//--------------------------------------------------------------
// CORE0
//--------------------------------------------------------------
// No pin needed

//--------------------------------------------------------------
// CORE1
//--------------------------------------------------------------
// No pin needed

//--------------------------------------------------------------
// WIFI STATION CHANGEABLE
//--------------------------------------------------------------
// No pin needed

#endif //_PINS_H