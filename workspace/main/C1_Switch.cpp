/*--------------------------------------------------------------------------------*-
  3 State button - TS002 - function file
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
#ifndef _C1_SWITCH_CPP
#define _C1_SWITCH_CPP
#include "C1_Switch.h"

// ------ Private constants -----------------------------------
#define SW_DEBOUNCE 100 //debounce for pressing button
// ------ Private function prototypes -------------------------
static void IRAM_ATTR SWupbut_ISR();
static void IRAM_ATTR SWmidbut_ISR();
static void IRAM_ATTR SWdowbut_ISR();
// ------ Private variables -----------------------------------
static portMUX_TYPE SWmux = portMUX_INITIALIZER_UNLOCKED;
static int SW_pos; //have to be in int to fit with enum
static bool SWloopEnable;
static char SWminVal;
static char SWmaxVal;

static volatile bool         upButChanged; //button change is recognized or not
static volatile TickType_t   upButMillis; 	//timing
static bool                  upButLastRead; //current button state
static bool                  upButRead; //current button state
static bool                  upButPressedFor;  // allow bit

static volatile bool         midButChanged; //button change is recognized or not
static volatile TickType_t   midButMillis; 	//timing
static bool                  midButLastRead; //current button state
static bool                  midButRead; //current button state
static bool                  midButPressedFor;  // allow bit

static volatile bool         dowButChanged; //button change is recognized or not
static volatile TickType_t   dowButMillis; 	//timing
static bool                  dowButLastRead; //current button state
static bool                  dowButRead; //current button state
static bool                  dowButPressedFor;  // allow bit

// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS - CRUCIAL FUNCTIONS
//--------------------------------------------------------------
static void IRAM_ATTR SWupbut_ISR() { //interrupt saved in IRAM - keep it as short as possible
  	detachInterrupt(digitalPinToInterrupt(SW_UP_PIN));
	portENTER_CRITICAL_ISR(&(SWmux));
	upButChanged = true; //flag
	upButMillis  = xTaskGetTickCountFromISR(); //version of millis() that works from interrupt, but current task cost 100 tick to finish 1 second
  	portEXIT_CRITICAL_ISR(&(SWmux));
}//end SWupbut_ISR

static void IRAM_ATTR SWmidbut_ISR() { //interrupt saved in IRAM - keep it as short as possible
  	detachInterrupt(digitalPinToInterrupt(SW_MID_PIN));
	portENTER_CRITICAL_ISR(&(SWmux));
	midButChanged = true; //flag
	midButMillis  = xTaskGetTickCountFromISR(); //version of millis() that works from interrupt, but current task cost 100 tick to finish 1 second
	portEXIT_CRITICAL_ISR(&(SWmux));
}//end SWmidbut_ISR

static void IRAM_ATTR SWdowbut_ISR() { //interrupt saved in IRAM - keep it as short as possible
  	detachInterrupt(digitalPinToInterrupt(SW_DOW_PIN));
	portENTER_CRITICAL_ISR(&(SWmux));
	dowButChanged = true; //flag
	dowButMillis  = xTaskGetTickCountFromISR(); //version of millis() that works from interrupt, but current task cost 100 tick to finish 1 second
  	portEXIT_CRITICAL_ISR(&(SWmux));
}//end SWdowbut_ISR

void SW_init() {
	SW_pos = 0;

	upButChanged = false; //flag
	upButLastRead = false;
	upButRead = true;
	upButPressedFor = false; //allow counting bit, will be activated inside pressed function
	upButMillis=0; //for debounce and measure pressed time

	midButChanged = false; //flag
	midButLastRead = false;
	midButRead = true;
	midButPressedFor = false; //allow counting bit, will be activated inside pressed function
	midButMillis=0; //for debounce and measure pressed time

	dowButChanged = false; //flag
	dowButLastRead = false;
	dowButRead = true;
	dowButPressedFor = false; //allow counting bit, will be activated inside pressed function
	dowButMillis=0; //for debounce and measure pressed time

	pinMode(SW_UP_PIN, INPUT_PULLUP);
	pinMode(SW_MID_PIN, INPUT_PULLUP);
	pinMode(SW_DOW_PIN, INPUT_PULLUP);
}//end begin

void SW_setBoundaries(int8_t _minValue=-5, int8_t _maxValue=5, bool _loopEnable=false) {
	SWminVal = _minValue;
	SWmaxVal = _maxValue;
	SWloopEnable = _loopEnable;
}//end setBoundaries

void SW_enable() {
	attachInterrupt(digitalPinToInterrupt(SW_UP_PIN),  SWupbut_ISR,  CHANGE);
	attachInterrupt(digitalPinToInterrupt(SW_MID_PIN), SWmidbut_ISR, CHANGE);
	attachInterrupt(digitalPinToInterrupt(SW_DOW_PIN), SWdowbut_ISR, CHANGE);
}//end enable
void SW_disable() {
	detachInterrupt(digitalPinToInterrupt(SW_UP_PIN));
	detachInterrupt(digitalPinToInterrupt(SW_MID_PIN));
	detachInterrupt(digitalPinToInterrupt(SW_DOW_PIN));
}//end disable

void SW_set(int8_t REnewValue) { //set value to the RE 
	if (REnewValue > SWmaxVal) {
		REnewValue = (SWloopEnable)?(SWminVal):(SWmaxVal);
	}//end if
	if (REnewValue < SWminVal) {
		REnewValue = (SWloopEnable)?(SWmaxVal):(SWminVal);	
	}//end if
	SW_pos = REnewValue;
}//end set

int SW_read() {
	if (SW_pos > SWmaxVal) {
		SW_pos = (SWloopEnable)?(SWminVal):(SWmaxVal);
	}//end if
	if (SW_pos < SWminVal) {
		SW_pos = (SWloopEnable)?(SWmaxVal):(SWminVal);	
	}//end if
	return (SW_pos);
}//end read

bool SW_posChanged() {
	if (SW_upPressed()      ||SW_dowPressed()||
		SW_upPressedFor(500)||SW_dowPressedFor(500)) {return true;}
	else 											 {return false;}
}//end changed

//-------------------------UP BUTTON
bool SW_upPressed() {
	portENTER_CRITICAL(&SWmux);
	bool tempChanged = upButChanged;
	uint32_t tempMillis  = upButMillis;
	portEXIT_CRITICAL(&SWmux);
	if (tempChanged) {
		if ((xTaskGetTickCount()-tempMillis)>SW_DEBOUNCE/10) { //because 100 tick cost 1s
			portENTER_CRITICAL(&SWmux);
			upButChanged = false;
			portEXIT_CRITICAL(&SWmux);
			upButLastRead = upButRead;
			upButRead = digitalRead(SW_UP_PIN);
			//Pressed up!
			if ((upButLastRead != upButRead)&&(!upButRead)) { //Pressed!
				upButPressedFor = true; //allow counting bit
				SW_pos--;
				attachInterrupt(digitalPinToInterrupt(SW_UP_PIN),SWupbut_ISR, CHANGE);
				return true;
			}//end if
			//Released up!
			if ((upButLastRead != upButRead)&&(upButRead)) { //Released!
				upButPressedFor = false; //allow counting bit
				attachInterrupt(digitalPinToInterrupt(SW_UP_PIN),SWupbut_ISR, CHANGE);
				return false;
			}//end if
			attachInterrupt(digitalPinToInterrupt(SW_UP_PIN),SWupbut_ISR, CHANGE);
		}//end if
	}//end if
	
	return false;

}//end pressed

bool SW_upPressedFor(TickType_t ms) {
	if (upButPressedFor) {//Current task cost 100 tick to finish 1 second
		if ((xTaskGetTickCount()-upButMillis)>ms/10) { //because 100 tick cost 1s
			portENTER_CRITICAL_ISR(&(SWmux));
			upButMillis  = xTaskGetTickCountFromISR(); //version of millis() that works from interrupt, but current task cost 100 tick to finish 1 second
  			portEXIT_CRITICAL_ISR(&(SWmux));
			SW_pos--;
			return true;
		}//end if
	}//end if
	return false;
}//end SW_upPressedFor

//-------------------------MIDDLE BUTTON
bool SW_midPressed() {
	portENTER_CRITICAL(&SWmux);
	bool tempChanged = midButChanged;
	uint32_t tempMillis  = midButMillis;
	portEXIT_CRITICAL(&SWmux);
	if (tempChanged) {
		if ((xTaskGetTickCount()-tempMillis)>SW_DEBOUNCE/10) { //because 100 tick cost 1s
			portENTER_CRITICAL(&SWmux);
			midButChanged = false;
			portEXIT_CRITICAL(&SWmux);
			midButLastRead = midButRead;
			midButRead = digitalRead(SW_MID_PIN);
			//Pressed mid!
			if ((midButLastRead != midButRead)&&(!midButRead)) { //Pressed!
				midButPressedFor = true; //allow counting bit
				attachInterrupt(digitalPinToInterrupt(SW_MID_PIN),SWmidbut_ISR, CHANGE);
				return true;
			}//end if
			//Released mid!
			if ((midButLastRead != midButRead)&&(midButRead)) { //Released!
				midButPressedFor = false; //allow counting bit
				attachInterrupt(digitalPinToInterrupt(SW_MID_PIN),SWmidbut_ISR, CHANGE);
				return false;
			}//end if
			attachInterrupt(digitalPinToInterrupt(SW_MID_PIN),SWmidbut_ISR, CHANGE);
		}//end if
	}//end if
	
	return false;

}//end pressed

bool SW_midPressedFor(TickType_t ms) {
	if (midButPressedFor) {//Current task cost 100 tick to finish 1 second
		if ((xTaskGetTickCount()-midButMillis)>ms/10) { //because 100 tick cost 1s
			return true;
		}//end if
	}//end if
	return false;
}//end SW_midPressedFor

//-------------------------DOWN BUTTON
bool SW_dowPressed() {
	portENTER_CRITICAL(&SWmux);
	bool tempChanged = dowButChanged;
	uint32_t tempMillis  = dowButMillis;
	portEXIT_CRITICAL(&SWmux);
	if (tempChanged) {
		if ((xTaskGetTickCount()-tempMillis)>SW_DEBOUNCE/10) { //because 100 tick cost 1s
			portENTER_CRITICAL(&SWmux);
			dowButChanged = false;
			portEXIT_CRITICAL(&SWmux);
			dowButLastRead = dowButRead;
			dowButRead = digitalRead(SW_DOW_PIN);
			//Pressed down!
			if ((dowButLastRead != dowButRead)&&(!dowButRead)) { //Pressed!
				dowButPressedFor = true; //allow counting bit
				SW_pos++;
				attachInterrupt(digitalPinToInterrupt(SW_DOW_PIN),SWdowbut_ISR, CHANGE);
				return true;
			}//end if
			//Released down!
			if ((dowButLastRead != dowButRead)&&(dowButRead)) { //Released!
				dowButPressedFor = false; //allow counting bit
				attachInterrupt(digitalPinToInterrupt(SW_DOW_PIN),SWdowbut_ISR, CHANGE);
				return false;
			}//end if
			attachInterrupt(digitalPinToInterrupt(SW_DOW_PIN),SWdowbut_ISR, CHANGE);
		}//end if
	}//end if
	
	return false;

}//end pressed

bool SW_dowPressedFor(TickType_t ms) {
	if (dowButPressedFor) {//Current task cost 100 tick to finish 1 second
		if ((xTaskGetTickCount()-dowButMillis)>ms/10) { //because 100 tick cost 1s
			portENTER_CRITICAL_ISR(&(SWmux));
			dowButMillis  = xTaskGetTickCountFromISR(); //version of millis() that works from interrupt, but current task cost 100 tick to finish 1 second
  			portEXIT_CRITICAL_ISR(&(SWmux));
			SW_pos++;
			return true;
		}//end if
	}//end if
	return false;
}//end SW_dowPressedFor
//--------------------------------------------------------------
// FUNCTION DEFINITIONS - APPLICATION FUNCTIONS
//--------------------------------------------------------------

#endif //_C1_SWITCH_CPP
