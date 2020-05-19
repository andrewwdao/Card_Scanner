/*------------------------------------------------------------*-
  BUZZER - functions file
  ESP32 CORE1 - APPLICATION CORE
  (c) An Minh Dao 2019
  version 1.00 - 23/02/2019
---------------------------------------------------------------
 *  PUBLIC FUNCTIONS CONTAIN:
 *  void RFID125_init();
 *  bool hasID();  //check if there is any new ID by interrupt
 *  void RFID125_interrupt();
 *  
 *  PRIVATE FUNCTIONS CONTAIN:
 *  void GetID();
 *  long hexstr_to_value(unsigned char *str, unsigned int str_length);
 * 
 --------------------------------------------------------------*/
#ifndef _C1_BUZZER_CPP
#define _C1_BUZZER_CPP
#include "C1_Buzzer.h"

// ------ Private constants -----------------------------------
#define BEEP_DURATION  100  //300ms delay
// ------ Private function prototypes -------------------------

// ------ Private variables -----------------------------------

// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void multipleBeep(int number) {
	char j;
	for (j=0; j<number; j++) {
      digitalWrite(BUZZER_PIN,HIGH); //turn on Buzzer
	    vTaskDelay(BEEP_DURATION/portTICK_PERIOD_MS);// Delay for BEEP_DURATION
	    digitalWrite(BUZZER_PIN,LOW); //turn off Buzzer	
	    vTaskDelay(BEEP_DURATION/portTICK_PERIOD_MS);// Delay for BEEP_DURATION
	}//end for
}//end multipleBeep
void singleBeep(int mstime) {
  digitalWrite(BUZZER_PIN,HIGH); //turn on Buzzer
	vTaskDelay(mstime/portTICK_PERIOD_MS);// Delay for BEEP_DURATION
	digitalWrite(BUZZER_PIN,LOW); //turn off Buzzer
}//end singleBeep

#endif //_C1_BUZZER_CPP