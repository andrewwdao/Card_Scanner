/*------------------------------------------------------------*-
  Wifi Station changeable module - function file
  ESP32 CORE0 - PROTOCOL CORE
  (c) An Minh Dao - Bernd Giesecke 2019
  version 2.00 - 27/03/2019
---------------------------------------------------------------
 *  PUBLIC FUNCTIONS CONTAIN:
 *  void wifi_STA_init();
 *  bool wifi_isConnected();
 *  void wifi_STA_serialUpdater();
 *  void wifi_STA_BLEupdater();
 * 
 *  PRIVATE FUNCTIONS CONTAIN:
 *  static void Wifi_begin();
 *  static String GetData();     //only exist in changeable mode
 * 
 --------------------------------------------------------------*/
#ifndef _C0_WIFI_STA_CH_CPP
#define _C0_WIFI_STA_CH_CPP
#include "C0_Wifi_sta_ch.h"

// ------ Private constants -----------------------------------

// ------ Private function prototypes -------------------------
static void Wifi_begin();
static String GetData();     //only exist in changeable mode

// ------ Private variables -----------------------------------
//static String routeServe = "http://192.168.1.18:8000";
//NO STATIC

// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// CALLBACK DEFINITIONS
//--------------------------------------------------------------
// /** Callback for receiving IP address from AP */
// void WgotIP(system_event_id_t event) {
// 	wifiConnected = true;
// }//end gotIP
// /** Callback for connection loss */
// void WlostCon(system_event_id_t event) {
// 	wifiConnected = false;
// }//end lostCon
//--------------------------------------------------------------
// CRUCIAL FUNCTION DEFINITIONS
//--------------------------------------------------------------
bool wifi_isConnected() {
  if ((WiFi.status() == WL_CONNECTED)) {return true;}
  return false;
}//end wifi_isConnected
bool wifi_STA_init() {
  //------------------------WIFI INITIALIZE---------------------
  Wifi_begin(); // We start by connecting to a WiFi network -- 3s
  //-------------------------------------------------------------
  if ((WiFi.status() == WL_CONNECTED)) {//connect successfully
    return true;
  } else { //failed to connect
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    return false;
  }//end if else
}//end wifi_STA_init
static void Wifi_begin() {  //HAS BEEN MODIFIED A LOT TO FIT EEPROM MODULE
  // Setup callback function for successful connection - if system is connected, gotIP will execute.
	//WiFi.onEvent(WgotIP, SYSTEM_EVENT_STA_GOT_IP);
	// Setup callback function for lost connection - if system is connected, lostCon will execute.
	//WiFi.onEvent(WlostCon, SYSTEM_EVENT_STA_DISCONNECTED);

	WiFi.disconnect(true);
	WiFi.enableSTA(true);
  WiFi.mode(WIFI_STA);

  String WLAN_SSID = NVS_wifiSSID_read();
  String WLAN_PASS = NVS_wifiPASS_read();
  char Wifi_idlength   = WLAN_SSID.length();
  char Wifi_passlength = WLAN_PASS.length();
  char __WLAN_SSID[Wifi_idlength]; //we need char value so we omit the n+1 value of the string (which is \0)
  WLAN_SSID.toCharArray(__WLAN_SSID,Wifi_idlength + 1);
  char __WLAN_PASS[Wifi_passlength];
  WLAN_PASS.toCharArray(__WLAN_PASS,Wifi_passlength + 1);

  WiFi.begin(__WLAN_SSID, __WLAN_PASS);

  // Connect to WiFi access point.
  S_PRINT(F("Connecting to ")); S_PRINT(__WLAN_SSID);

  char count=0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); count++;
    S_PRINT(F("."));
    if (count>9) {count=0;return;}
  }//end while

  S_PRINTLN(F("WiFi connected!"));
  D_PRINT(F("IP address: "));D_PRINTLN(WiFi.localIP());
  S_PRINTLN();
}//end wifi begin
void wifi_STA_serialUpdater() {
  //------------------------RESET CREDENTIALS--------------------
  oled_wifi_SerialUpdater();
  Wifi_tryAgain:
  S_PRINTLN();
  S_PRINTLN("\t\t\t---"+OPT_WF_UART+"---");
  S_PRINTLN(F("Hello there!"));
  S_PRINTLN(F("Current Wifi Credentials:"));
  S_PRINTLN("ID  : "+NVS_wifiSSID_read());
  S_PRINTLN("PASS: "+NVS_wifiPASS_read());
  S_PRINTLN(F("Ready to update your Wifi Credentials?  Y/N"));
  S_PRINTLN(F("CAUTION : use NO LINE ENDING mode to type!!!"));
  long Wlastmillis=millis();
  while (Serial.available()==0) {
    if (SW_midPressed()) {//only activated when a press and a release is recognized
      NVS_system_write(SYS_NORMAL);
      S_PRINTLN(MES_NORMAL);
      ESP.restart();
    }//end if
    if ((millis()-Wlastmillis)>7000) {goto Wifi_tryAgain;}  
  } // end while no signal
  while (Serial.available()> 0) {//some signal appeared
    char ch = Serial.read();
    if (ch=='y'||ch=='Y') {
      S_PRINTLN(F("YES"));
      S_PRINTLN(F("Type in new Wifi ID:"));
      String _WLAN_SSID=GetData();
      S_PRINTLN(F("Type in new password:"));
      String _WLAN_PASS=GetData();
      NVS_WIFIdata_write(_WLAN_SSID,_WLAN_PASS);
      S_PRINTLN(F("Saved!"));
    }//end yes
    else {
      S_PRINTLN(F("NO"));
      //////////////HTTP UPDATE//////////////////
      HTTP_updateAP();
      ///////////////////////////////////////////
      NVS_system_write(SYS_NORMAL);
      S_PRINTLN(MES_NORMAL);
      ESP.restart();
    }//end no
  }//end while serial available
  //------------------------WIFI INITIALIZE---------------------
  Wifi_begin(); // We start by connecting to a WiFi network -- 3s
  //--------------------------------------------------------------
  if ((WiFi.status() == WL_CONNECTED)) { //ACCESS SUCCESSFULLY!
    //////////////HTTP UPDATE//////////////////
    HTTP_updateAP();
    ///////////////////////////////////////////
    NVS_system_write(SYS_NORMAL);
    S_PRINTLN(MES_NORMAL);
    ESP.restart();
  } else { //CANNOT ACCESS TO WIFI
    S_PRINTLN(F("Connect failed."));
    S_PRINTLN(F("Try another Credentials?  Y/N"));
    while (Serial.available()==0) { // no signal
      if (SW_midPressed()) {//only activated when a press and a release is recognized
      NVS_system_write(SYS_NORMAL);
      S_PRINTLN(MES_NORMAL);
      ESP.restart();
    }//end if
    } // end while no signal
    while (Serial.available()>0) {//some signal appeared
      char ch = Serial.read();
      if (ch=='y'||ch=='Y') { //type again
        S_PRINTLN(F("YES"));
        S_PRINTLN(F("Reseting WIFI UPDATER..."));
        goto Wifi_tryAgain;
      } else { //reset to normal mode
        S_PRINTLN(F("NO"));
        //////////////HTTP UPDATE//////////////////
        HTTP_updateAP();
        ///////////////////////////////////////////
        NVS_system_write(SYS_NORMAL);
        S_PRINTLN(MES_NORMAL);
        ESP.restart();
        }//end if else
    }//end while serial available
  }//end if else
}//end wifi_STA_update()
void wifi_STA_BLEupdater() {
  //------------------------RESET CREDENTIAL---------------------
  oled_wifi_BLEupdater();
  initBLE();
  S_PRINTLN();
  S_PRINTLN("\t\t\t---"+OPT_WF_BLE+"---");
  S_PRINTLN();
  BLEreceived=false; //eliminate first time dump
  //--------------------------------------------------------------
  while (1) {
    if (SW_midPressed()) {//only activated when a press and a release is recognized
      NVS_system_write(SYS_NORMAL);
      btStop(); //stop BLE
      ESP.restart();
    }//end if
    /*
    The flag BLEreceived is only set when:
    - The BLE server has received WiFi credentials
    - A WiFi connection has been established
    - A WiFi connection has been lost

    The flag BLEhasCredentials is only set when:
    - The BLE server has received WiFi credentials
    */
    if (BLEreceived&BLEhasCredentials) { //only activated when new credentials are catched
      BLEreceived=false; BLEhasCredentials=false;
      //------------------------WIFI INITIALIZE----------------------
      Wifi_begin(); //Connecting to a WiFi network -- 3s
      //--------------------------------------------------------------
      if ((WiFi.status() == WL_CONNECTED)) { //ACCESS SUCCESSFULLY!
        //wifiConnected=false;
        NVS_system_write(SYS_NORMAL);
        btStop(); //stop BLE
        ESP.restart();
      } else { //CANNOT ACCESS TO WIFI
        D_PRINTLN(MES_WF_FAIL); //Use your smartphone to update another one, Press the RE once to return to NORMAL MODE
        oled_wifi_BLEupdater();
      }//end if else
    }//end if
  }//end while
}//end wifi_STA_BLEupdater
static String GetData() {
  String data = "";
  while(Serial.available()==0) {}// do nothing...
  while(Serial.available()>0) {//get data
    char ch = Serial.read();
    data = data + ch;
    delay(2); //for stablize
  }//end while serial available
  S_PRINT(F("Recieved: "));S_PRINTLN(data);
  return data;
}//end GetData
//--------------------------------------------------------------
// HTTP FUNCTION DEFINITIONS
//--------------------------------------------------------------
void HTTP_updateAP() {
  S_PRINTLN(F("Current Web Server Acess Point:"));
  S_PRINTLN(NVS_WebAP_read());
  S_PRINTLN(F("Update?  Y/N"));
  while (Serial.available()==0) { // no signal
    if (SW_midPressed()) {//only activated when a press and a release is recognized
      NVS_system_write(SYS_NORMAL);
      S_PRINTLN(MES_NORMAL);
      ESP.restart();
    }//end if
  } // end while no signal
  while (Serial.available()>0) {//some signal appeared
    char ch = Serial.read();
    if (ch=='y'||ch=='Y') { //change web access point
      S_PRINTLN(F("YES"));
      S_PRINTLN(F("Type in new Acess Point:"));
      String _HTTP_AP=GetData();
      NVS_WebAP_write(_HTTP_AP);
      S_PRINTLN(F("Saved!"));
    } else { //don't change webAP
        S_PRINTLN(F("NO"));
    }//end if else
    //reset is happened in other functions
  }//end while serial available
}//end HTTP_updateAP
char HTTP_getClass(String* HClass, char* Hnum) {
  (*Hnum)=0;
  if (wifi_isConnected()) { //Check the current connection status
    HTTPClient http;
    if (http.begin("http://"+NVS_WebAP_read()+GETCLAS_API)) {  //Specify the URL
      if (http.GET()==200) { //Make the request, Check for the returning code, HTTP_CODE_OK=200
        String data_received = http.getString();
        D_PRINT("JSON: "); D_PRINTLN(data_received);
        DynamicJsonDocument ClassData(1024);
        deserializeJson(ClassData, data_received);
        for(int Ccount=0; Ccount < ClassData.size(); Ccount++){
          (*Hnum)++;
          String ClassEx = ClassData[Ccount]["Class"]; //cannot shorten out
          *(HClass+Ccount) = ClassEx;
        }//end for
        http.end(); //Free the resources
        return GOOD;
      }//end if
    } else { //Cannot recieve full data from server
      http.end(); //free the recources
      return NOTG;
    }//end if else
  }//end if has wifi
  return NO_WIFI;
}//end HTTP_getClass
char HTTP_getFrom(String* GClass,char* GnumCl,char Gnum) {
  String CClass=*(GClass+Gnum);
  if (wifi_isConnected()) { //Check the current connection status
    HTTPClient http;
    if (http.begin("http://"+NVS_WebAP_read()+GETSTUS_API+CClass)) {  //Specify the URL
      if (http.GET()==200) { //Make the request, Check for the returning code, HTTP_CODE_OK=200
        String data_received = http.getString();
        D_PRINT("JSON: ");D_PRINTLN(data_received);
        DynamicJsonDocument StudentData(15360);
        deserializeJson(StudentData, data_received);

        //---INVOLVING SD CARD SAVING
        SD_deleteClass(GClass, GnumCl, Gnum, ACLASS_LOCATION);//delete first
        File SD_dataFile = SD.open(ACLASS_LOCATION+CClass+".txt", FILE_APPEND);
        if((!SD_dataFile)&&(SD_dataFile.isDirectory())) {
          D_PRINTLN(F("File not found!"));
          return NOTG;
        }//end if

        for(int i = 0, sizedata = StudentData.size(); i < sizedata ; i ++) {
          String NameSV = StudentData[i]["n"];//name
          String MSSV   = StudentData[i]["m"];//mssv
          if ((SD_dataFile.print(MSSV))  && //name of the class is store in CLASSES.TXT
              (SD_dataFile.print('|'))   &&
              (SD_dataFile.print(NameSV))&&
              (SD_dataFile.print("\r\n"))) 
          {
            D_PRINT(MSSV+" ");D_PRINTLN(NameSV);
          } else {
            //do not delete the D_PRINTLN below
            D_PRINTLN(MES_GER);//for debugging what cause the error, if this is triggered --> error from saving data to the files!
            return NOTG;
          }//end if else
        }//end for
        SD_dataFile.close();
        http.end(); //free the recources
        return GOOD;
      }//end if
    } else { //if http.begin failed
      http.end(); //free the recources
      return NOTG;
    }//end if else
  }//end if has wifi
  return NO_WIFI;
}//end HTTP_getFrom
char HTTP_send() {
  if(wifi_isConnected()){ //Check WiFi connection status
    File SD_chosenFile = SD.open(AWAIT_LOCATION+"DATA.txt", FILE_READ);
    int amountR=SD_chosenFile.size()/30;//30 letters a row --> number of rows
    D_PRINTLN(amountR);
    int SendTime=(amountR%AMOUNT_SEND)?(amountR/AMOUNT_SEND+1):(amountR/AMOUNT_SEND);
    D_PRINTLN(SendTime);
    
    int SD_pointer=0;//pointer for the origin files
    for (int aTime=0;aTime<SendTime;aTime++) {//execute "SendTime" times, including create JSON, send it
      String SendString="[";
      //this FOR is used for putting the data into 1 string for sending
      int bBoundary = ((aTime==(SendTime-1))?(amountR%AMOUNT_SEND):(AMOUNT_SEND));
      for (int bTime=0;bTime<bBoundary;bTime++) {
        String SD_mssvBuffer;
        String SD_clasBuffer;
        String SD_dateBuffer;

        SD_chosenFile.seek(SD_pointer);
        //-------------------------------UPDATING IS FINISHED
        if (!SD_chosenFile.available()) {//if there are nothing left in the file
          break; //this will not likely to happen
        }//end if
        //-------------------------------

        //CONTINUE TO UPDATE WHEN FILE IS NOT FINISHED
        uint8_t chooseBuffer = 0;
        while(SD_chosenFile.available()) {
          char SDtemp = SD_chosenFile.read();
          SD_pointer++;
          if (SDtemp =='\n') {break;} //end of a line
          else if (SDtemp=='\r') {} //safety method for \r\n of Windows-edited files
          else if((chooseBuffer==0)&&(!(SDtemp=='|'))) {
            SD_mssvBuffer += SDtemp;
          }//end else
          else if((chooseBuffer==1)&&(!(SDtemp=='|'))) {
            SD_clasBuffer += SDtemp;
          }//end else
          else if((chooseBuffer==2)&&(!(SDtemp=='|'))) {
            SD_dateBuffer += SDtemp;
          }//end else
          else if (SDtemp=='|') {chooseBuffer++;}
        }//end while - now we have 3 value in 3 buffers
        //----------------------------------------------
        //----------------------JSON TIME---
        DynamicJsonDocument jsonBuffer(1024);
        jsonBuffer["m"] = SD_mssvBuffer; //put mssv in the JSON document
        jsonBuffer["c"] = SD_clasBuffer; //put class in the JSON document
        jsonBuffer["d"] = SD_dateBuffer; //put date in the JSON document
        String BufString="";
        // Convert JSON object into a string
	      serializeJson(jsonBuffer, BufString);
		    jsonBuffer.clear(); //mission of JSON is done here
        SendString += (bTime!=(bBoundary-1))?(BufString+','):(BufString);
      }//end for - now we have 1 STRING
      SendString += ']'; //finish the sending string, pseudo JSON
      D_PRINTLN(SendString);
      //--------------------------HTTP TIME--
      HTTPClient http;   
      http.begin("http://"+NVS_WebAP_read()+SEND_API);  //Specify destination for HTTP request
      http.addHeader("Content-Type", "text/plain");     //Specify content-type header
      int HTTPcode = http.POST(SendString);
      String HTTPres = http.getString();
      if ((HTTPcode==200)||(HTTPres=="NAT")) {//if sending successfully, HTTP_CODE_OK=200
        D_PRINTLN(HTTPres);
      } else { //if 1 among packages failed to send --> failed
        D_PRINTLN(MES_GER);D_PRINTLN(HTTPcode);
        http.end();  //Free resources
        SD_chosenFile.close();
        return NOTG;
      }//end if else
      http.end();  //Free resources
    }//end for 1 SendTime (usually happen less than 5 times)
    SD_chosenFile.close();
    return GOOD; //if it can survive until here, then everything works fine!
  }//end if has wifi
  return NO_WIFI;
}//end HTTP_send
#endif //_C0_WIFI_STA_CH_CPP
