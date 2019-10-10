/*--------------------------------------------------------------------------------*-
  System Scenarios - functions file
  ESP32 CORE1 - APPLICATION CORE
  (c) An Minh Dao 2019
  version 1.00 - 27/03/2019
-------------------------------------------------------------------------------------
 * 
 *  PUBLIC FUNCTIONS CONTAIN:
 * 
 *  PRIVATE FUNCTIONS CONTAIN:
 *
 *  - Important Documents:
 * 		+ 
 * -------------------------------------------------------------------------------------*/
#ifndef _C1_SCENARIOS_CPP
#define _C1_SCENARIOS_CPP
#include "C1_Scenarios.h"

// ------ Private constants -----------------------------------

// ------ Private function prototypes -------------------------
static void Frame1_init(String, String, void (*)(String*,char*,char), void (*)(String*,char*,char), void (*)(String));
static void Frame1_getClass(String*, char*, String);
//static void Frame1_ClasDel(String, String*, char*, char);
static void Frame1_ClasDelAll(String, String);
static void Frame2_init(String, void (*)(String*,char*,String), void (*)(String*,char*,char));
static void Frame_mainAct(String, String*, char*, void (*)(String*,char*,char));

//static void SD_updateDatabase(String*, char*, char);

static void ACheck_make(String*, char*, char);
static void ACheck_delete(String*, char*, char);
static void ACheck_delAll(String);

static void AClass_make(String*, char*, char);
static void AClass_getClass(String*, char*, String);//connect to wifi and get class from server

static void AManual_make(String*, char*, char);
static void AManual_delete(String*, char*, char);
static void AManual_delAll(String);

static void Export_make();

static void ClearAll_sentData();
// ------ Private variables -----------------------------------
static bool l1starter=true;
static bool l2starter=true;
static bool l3starter=true;
// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS - CRUCIAL FUNCTIONS
//--------------------------------------------------------------
//### WIFI SERIAL UPDATER --> C0_Wifi_sta_ch.cpp
//### WIFI BLE UPDATER    --> C0_Wifi_sta_ch.cpp
//### RTC UPDATER         --> C1_RTC_DS3231.cpp
void Scenarios_update() { //MAIN SCENARIOS
    while (1) {
        //oled_Clock_Updater(); //display time 
        if (l1starter) {
            l1starter=false;
            l2starter=true;
            l3starter=true;
            oled_mainMenu_init();//oled_mainMenu_1 lies inside
            SW_setBoundaries(1,10,true); //min, max, loop enable
            SW_set(1);
            SW_enable();
        }//end if
        if (SW_posChanged()) {
            switch (SW_read()) {
                case ATTENDANCE_CHECK: {oled_POINTER1();oled_mainMenu_1();break;}
                case ADD_CLASSES:      {oled_POINTER2();oled_mainMenu_1();break;}
                case ADD_MANUALLY:     {oled_POINTER3();oled_mainMenu_1();break;}
                case EXPORT_DATA:      {oled_POINTER4();oled_mainMenu_1();break;}
                case WIFI_UART_UPDATER:{oled_POINTER1();oled_mainMenu_2();break;}
                case WIFI_BLE_UPDATER: {oled_POINTER2();oled_mainMenu_2();break;}
                case RTC_UART_UPDATER: {oled_POINTER3();oled_mainMenu_2();break;}
                case RTC_SNTP_UPDATER: {oled_POINTER4();oled_mainMenu_2();break;}
                case AUTO_EXPORT:      {oled_POINTER1();oled_mainMenu_3();break;}
                case CLEAR_SENT:       {oled_POINTER2();oled_mainMenu_3();break;}
            }//end switch case
        }//end if
        if (SW_midPressed()) { //if confirmed
            switch (SW_read()) {
                case ATTENDANCE_CHECK: {
                    Frame1_init(OPT_1,ACHECK_LOCATION, ACheck_make, ACheck_delete, ACheck_delAll);
                    break;
                }
                case ADD_CLASSES: {
                    NVS_system_write(SYS_ADD_CLASSES);
                    ESP.restart();
                    break;
                }
                case ADD_MANUALLY: {
                    Frame1_init(OPT_3,ACLASS_LOCATION, AManual_make, AManual_delete, AManual_delAll);
                    break;
                }
                case EXPORT_DATA: {
                    Export_make();
                    break;
                }
                case WIFI_UART_UPDATER:{
                    NVS_system_write(SYS_SERIAL_UPDATE_WIFI);
                    ESP.restart();
                    break;
                }
                case WIFI_BLE_UPDATER: {
                    NVS_system_write(SYS_BLE_UPDATE_WIFI);
                    ESP.restart();
                    break;
                }
                case RTC_UART_UPDATER: {
                    NVS_system_write(SYS_SERIAL_UPDATE_RTC);
                    ESP.restart();
                    break;
                }
                case RTC_SNTP_UPDATER: {
                    NVS_system_write(SYS_SNTP_UPDATE_RTC);
                    ESP.restart();
                    break;
                }
                case AUTO_EXPORT: {//this will take effect the next time the system is on
                    NVS_AExMode_write(!NVS_AExMode_read());
                    oled_POINTER1();oled_mainMenu_3();
                    break;
                }
                case CLEAR_SENT: {
                    ClearAll_sentData();
                    break;
                }
            }//end switch
        }//end if
    }//end while
}//end Scenarios_update

//#THIS FUNCTION IS USED FOR BOTH "ATTENDANCE CHECKING" MODE AND "ADD CLASS MANUALLY" MODE
static void Frame1_init(String mainMode, 
                        String ALocation, 
                        void (*chooseFunc)(String*,char*,char), 
                        void (*deleteFunc)(String*,char*,char), 
                        void (*delAllFunc)(String)) 
{
    String Class[MAX_CLASSES];
    for (char ahas=0;ahas<MAX_CLASSES;ahas++){
        *(Class+ahas)=VOID;
    }//end for
    char* numClass=(char*)malloc(1);
    *numClass = 0; //have to be reset
    Frame1_getClass(Class,numClass,ALocation); //string array hold classes, number of class, mode location
    while (1) {
        if (l2starter) {
            l2starter=false;
            l1starter=true;
            l3starter=true;
            oled_Frame1_init(mainMode);
            oled_POINTER1();oled_Frame1_menu();
            SW_setBoundaries(1,4,true); //min, max, loop enable
            SW_set(1);
            SW_enable();
        }//end if
    
        if (SW_posChanged()) {
            switch (SW_read()) {
                case INIT_BACK:    {oled_POINTER1();oled_Frame1_menu();break;}
                case CHOOSE_CLASS: {oled_POINTER2();oled_Frame1_menu();break;}
                case DELETE_CLASS: {oled_POINTER3();oled_Frame1_menu();break;}
                case DELETE_ALL:   {oled_POINTER4();oled_Frame1_menu();break;}
            }//end switch case
        }//end if
        if (SW_midPressed()) { //if confirmed
            switch (SW_read()) {
                case INIT_BACK: { //return to the previous menu
                    free(numClass);
                    WiFi.disconnect(true);//main menu will not have wifi
                    WiFi.mode(WIFI_OFF);
                    btStop(); //stop BLE
                    return;break;
                }
                case CHOOSE_CLASS: {//main action
                    Frame_mainAct(" "+OPT_CHOSE,Class,numClass,chooseFunc);
                    break;
                }
                case DELETE_CLASS: {//delete class
                    Frame_mainAct(" "+OPT_DEL,Class,numClass,deleteFunc);
                    break;
                }
                case DELETE_ALL: {//delete all class
                    (*delAllFunc)(mainMode);
                    for (char adel=0;adel<MAX_CLASSES;adel++){
                        *(Class+adel)=VOID;
                    }//end for
                    *numClass=0;
                    break;
                }//end case
            }//end switch case
        }//end if
    }//end while
}//Frame1_init
static void Frame1_getClass(String* cl, char* Cnum, String Cdir) {
    SD_getClass(cl,Cnum,Cdir);
}//end Frame1_getClass
void Frame1_ClasDel(String Dlocation, 
                           String* DClass, 
                           char* NumClass, 
                           char Dnum) 
{
    SD_deleteClass(DClass, NumClass, Dnum, Dlocation);//delete 2 files in 1 func
    for (char adel=((*NumClass)-1);adel<MAX_CLASSES;adel++){
        *(DClass+adel)=VOID;
    }//end for
    SD_getClass(DClass,NumClass,Dlocation); //string array hold classes, number of class, mode location
}//end FrameFrame1_ClasDel
static void Frame1_ClasDelAll(String Dlocation, String ACopt) {
    oled_done();//only for confirm button only!
    SD_deleteAllClass(Dlocation);
    delay(800);
    oled_Frame1_init(ACopt);
    oled_POINTER4();oled_Frame1_menu();
}//end Frame1_ClasDelAll
static void Frame2_init(String Frame2Mode, 
                        void (*getClassFunc)(String*,char*,String), 
                        void (*MainFunc)(String*,char*,char)) 
{
    String Class[MAX_CLASSES];
    for (char ahas=0;ahas<MAX_CLASSES;ahas++){
        *(Class+ahas)=VOID;
    }//end for
    char* numClass=(char*)malloc(1);
    *numClass = 0; //have to be reset
    (*getClassFunc)(Class,numClass,ACHECK_LOCATION); //string array hold classes, number of class, mode location
    Frame_mainAct(Frame2Mode, Class, numClass, MainFunc);
    free(numClass);
    NVS_system_write(SYS_NORMAL_DIRECT);
    ESP.restart();
    return;
}//end Frame2_init
static void Frame_mainAct(String Frame1mode, 
                          String* Classes,
                          char* numClasses, 
                          void (*mainFunc)(String*,char*,char)) 
{
    oled_Frame1_mode(Frame1mode);
    while (1) {
        if (l3starter) {
            l3starter=false;
            l1starter=true;
            l2starter=true;
            oled_Frame1_mode(Frame1mode);
            oled_POINTER1();oled_Frame1_Class1(Classes);
            SW_setBoundaries(1,(*numClasses+1),true); //min, max, loop enable
            SW_set(1);
            SW_enable();
        }//end if
    
        if (SW_posChanged()) {
            switch (SW_read()) {
                case INIT_BACK:  {oled_POINTER1();oled_Frame1_Class1(Classes);break;}
                case CLASS1:     {oled_POINTER2();oled_Frame1_Class1(Classes);break;}
                case CLASS2:     {oled_POINTER3();oled_Frame1_Class1(Classes);break;}
                case CLASS3:     {oled_POINTER4();oled_Frame1_Class1(Classes);break;}
                case CLASS4:     {oled_POINTER1();oled_Frame1_Class2(Classes);break;}
                case CLASS5:     {oled_POINTER2();oled_Frame1_Class2(Classes);break;}
                case CLASS6:     {oled_POINTER3();oled_Frame1_Class2(Classes);break;}
                case CLASS7:     {oled_POINTER4();oled_Frame1_Class2(Classes);break;}
                case CLASS8:     {oled_POINTER1();oled_Frame1_Class2(Classes+4);break;}
                case CLASS9:     {oled_POINTER2();oled_Frame1_Class2(Classes+4);break;}
                case CLASS10:    {oled_POINTER3();oled_Frame1_Class2(Classes+4);break;}
                case CLASS11:    {oled_POINTER4();oled_Frame1_Class2(Classes+4);break;}
                case CLASS12:    {oled_POINTER1();oled_Frame1_Class2(Classes+8);break;}
                case CLASS13:    {oled_POINTER2();oled_Frame1_Class2(Classes+8);break;}
                case CLASS14:    {oled_POINTER3();oled_Frame1_Class2(Classes+8);break;}
                case CLASS15:    {oled_POINTER4();oled_Frame1_Class2(Classes+8);break;}
            }//end switch case
        }//end if
        if (SW_midPressed()) { //if confirmed
            switch (SW_read()) {
                case INIT_BACK:  {return;break;}
                case CLASS1:     {(*mainFunc)(Classes,numClasses,0);l3starter=true;break;}//string array hold classes, number of classes, class number being chosen 
                case CLASS2:     {(*mainFunc)(Classes,numClasses,1);l3starter=true;break;}//string array hold classes, number of classes, class number being chosen 
                case CLASS3:     {(*mainFunc)(Classes,numClasses,2);l3starter=true;break;}//string array hold classes, number of classes, class number being chosen 
                case CLASS4:     {(*mainFunc)(Classes,numClasses,3);l3starter=true;break;}//string array hold classes, number of classes, class number being chosen 
                case CLASS5:     {(*mainFunc)(Classes,numClasses,4);l3starter=true;break;}//string array hold classes, number of classes, class number being chosen 
                case CLASS6:     {(*mainFunc)(Classes,numClasses,5);l3starter=true;break;}//string array hold classes, number of classes, class number being chosen 
                case CLASS7:     {(*mainFunc)(Classes,numClasses,6);l3starter=true;break;}//string array hold classes, number of classes, class number being chosen
                case CLASS8:     {(*mainFunc)(Classes,numClasses,7);l3starter=true;break;}//string array hold classes, number of classes, class number being chosen
                case CLASS9:     {(*mainFunc)(Classes,numClasses,8);l3starter=true;break;}//string array hold classes, number of classes, class number being chosen
                case CLASS10:    {(*mainFunc)(Classes,numClasses,9);l3starter=true;break;}//string array hold classes, number of classes, class number being chosen
                case CLASS11:    {(*mainFunc)(Classes,numClasses,10);l3starter=true;break;}//string array hold classes, number of classes, class number being chosen
                case CLASS12:    {(*mainFunc)(Classes,numClasses,11);l3starter=true;break;}//string array hold classes, number of classes, class number being chosen
                case CLASS13:    {(*mainFunc)(Classes,numClasses,12);l3starter=true;break;}//string array hold classes, number of classes, class number being chosen
                case CLASS14:    {(*mainFunc)(Classes,numClasses,13);l3starter=true;break;}//string array hold classes, number of classes, class number being chosen
                case CLASS15:    {(*mainFunc)(Classes,numClasses,14);l3starter=true;break;}//string array hold classes, number of classes, class number being chosen
            }//end switch case
        }//end if
    }//end while
}//end Frame_mainAct
//------------------------------- MODE 1: ATTENDANCE CHECKING ------------------------------
//------------------------------------------------------------------------------------------
static void ACheck_make(String* AClass, char* NumClass, char Anum) {//string array hold classes, number of classes, class number being chosen
    SD_ACheck_make(AClass,NumClass,Anum);
}//end ACheck_make
static void ACheck_delete(String* DClass, char* NumClass, char Dnum) {//string array hold classes, number of classes, class number being chosen
    Frame1_ClasDel(ACHECK_LOCATION,DClass, NumClass, Dnum);
}//end ACheck_delete
static void ACheck_delAll(String ACopt) {
    Frame1_ClasDelAll(ACHECK_LOCATION,ACopt);
}//end DeleteAllClass
//------------------------------- FUNCTIONS USE FOR BOTH ADD CLASS BY USING SERVER AND ADD CLASS MANUALLY------------------------
//-------------------------------------------------------------------------------------------------------------------------------
// static void SD_updateDatabase(String* Acls, char* numCl, char clNum) {
//     SD_updateDatabase(*(Acls+clNum),Acls,numCl,clNum);
//     //Frame1_ClasDel(ACLASS_LOCATION,Acls,numCl,clNum);
// }//end SD_updateDatabase
//------------------------------- MODE 2: ADD CLASS BY USING SERVER ------------------------
//------------------------------------------------------------------------------------------
void AddClass_init() {
    Frame2_init(OPT_2,AClass_getClass, AClass_make);
}//end AddClass_init
static void AClass_make(String* AClass, char* NumClass, char Anum) {//String array hold the classes, number of classes, the chosen class number
    
    
    /////////////////////////////////// PROTECT CURRENT DATA ////////////////////////////////////
    if (SD_checkClass(*(AClass+Anum))) {//if this class existed in the database
        oled_clear();
        oled_POINTER4();oled_AClass_override();
        SW_disable();
        SW_setBoundaries(0,1,true); //min, max, loop enable
        SW_set(NO);
        SW_enable();
        while (1) {
            if (SW_posChanged()) {
                switch (SW_read()) {
                    case YES:  {oled_POINTER3();oled_AClass_override();break;}
                    case NO:   {oled_POINTER4();oled_AClass_override();break;}
                }//end switch case
            }//end if
            if (SW_midPressed()) { //if confirmed
                switch (SW_read()) {
                    case YES:  {
                        //also delete the class in the database
                        SD_deleteClass(AClass, NumClass, Anum, ACHECK_LOCATION);//delete 2 files in 1 func
                        oled_connect(); //show oled screen
                        if (!wifi_isConnected()) {wifi_STA_init();}
                        //send request about the class to server
                            switch (HTTP_getFrom(AClass,NumClass,Anum)) { //connect and save the class into the database (including override file if existed)
                                case GOOD: { //if connect sucessfully
                                    SD_updateDatabase(AClass, NumClass, Anum);//update the file into database
                                    return;
                                }
                                case NOTG: {//cannot recieve completed data from server
                                    oled_get_error();
                                    S_PRINTLN(MES_GER);
                                    break;
                                }
                                case NO_WIFI: {//wifi failed
                                    oled_wifi_failed();
                                    S_PRINTLN(MES_WF_FAIL);
                                    break;
                                }
                            }//end switch
                        oled_comeBack();
                        while (!SW_midPressed());
                        NVS_system_write(SYS_NORMAL_DIRECT);
                        ESP.restart();
                        return; //l3starter flag is reset outside of this function
                    }//move to the next part
                    case NO:   {return;}//return to chose class
                }//end switch case
            }//end if
        }//end while
    }//end if
    ///////////////////////////////////////////////////////////////////////////////
    oled_connect(); //show oled screen
    if (!wifi_isConnected()) {wifi_STA_init();}
    //send request about the class to server
    switch (HTTP_getFrom(AClass,NumClass,Anum)) { //connect and save the class into the database (including override file if existed)
        case GOOD: { //if connect sucessfully
            SD_updateDatabase(AClass, NumClass, Anum);//update the file into database
            return;
            break;
        }
        case NOTG: {//cannot recieve completed data from server
            oled_get_error();
            S_PRINTLN(MES_GER);
            break;
        }
        case NO_WIFI: {//wifi failed
            oled_wifi_failed();
            S_PRINTLN(MES_WF_FAIL);
            break;
        }
    }//end switch
    oled_comeBack();
    while (!SW_midPressed());
    NVS_system_write(SYS_NORMAL_DIRECT);
    ESP.restart();
    return; //l3starter flag is reset outside of this function
}//end AClass_make
static void AClass_getClass(String* cl, char* Cnum, String Cdir) {//connect to wifi and get class from server
    oled_connect(); //OLED runs on core1
    if (!wifi_isConnected()) {wifi_STA_init();}
    switch (HTTP_getClass(cl,Cnum)) {
        case GOOD: { //get class sucessfully
            return;
            break;
        }
        case NOTG: {//failed to connect to server
            oled_get_error();
            S_PRINTLN(MES_GER);
            break;
        }
        case NO_WIFI: {//wifi failed
            oled_wifi_failed();
            S_PRINTLN(MES_WF_FAIL);
            break;
        }
    }//end switch
    oled_comeBack();
    while (!SW_midPressed());
    NVS_system_write(SYS_NORMAL_DIRECT);
    ESP.restart();
    return;
}//end AClass_getClass

//------------------------------- MODE 3: ADD CLASS MANUALLY -------------------------------
//------------------------------------------------------------------------------------------
static void AManual_make(String* Aclass, char* numClass, char classNum) { //String array hold the classes, number of classes, the chosen class number
    SD_updateDatabase(Aclass, numClass, classNum);//update the file into database
    S_PRINTLN(MES_RESTART);
    while (!SW_midPressed());
    NVS_system_write(SYS_NORMAL);
    ESP.restart(); //do not allow program proceed if SD card is broken
}//end AManual_make
static void AManual_delete(String* DClass, char* NumClass, char Dnum) {
    Frame1_ClasDel(ACLASS_LOCATION,DClass, NumClass, Dnum);
}//end AClass_delete
static void AManual_delAll(String ACopt) {
    Frame1_ClasDelAll(ACLASS_LOCATION,ACopt);
}//end AClass_delAll
//------------------------------- MODE 4 + MODE 9: EXPORT DATA -------------------------------
//------------------------------------------------------------------------------------------
static void Export_make() { //embedded oled compared to Export_begin
    oled_connect(); //OLED runs on core1
    switch (Export_begin()) {
        case GOOD: { //export sucessfully
            oled_Export_ok();oled_comeBack();
            break;
        }
        case NOTG: {//export failed
            oled_Ex_error();oled_comeBack();
            break;
        }
        case NO_WIFI: {//wifi failed
            oled_wifi_failed();oled_comeBack();
            break;
        }
    }//end switch
    while (!SW_midPressed());
    oled_clear();//oled_Clock_Updater();
    oled_POINTER4();oled_mainMenu_1();
    return;
}//end Export_make
char Export_begin() { //this is used for NORMAL MODE only!
    if (!wifi_isConnected()) {wifi_STA_init();}
    switch (HTTP_send()) {
        case GOOD: { //export sucessfully
            if (SD_moveDATA()) { //move sucessfully
                S_PRINTLN(MES_EOK);
                return GOOD;
            
            } else { //move failed
                S_PRINTLN(MES_EER);
                return NOTG;
            }//end if else
            break;
        }
        case NOTG: {//export failed
            S_PRINTLN(MES_EER);
            return NOTG;
            break;
        }
        case NO_WIFI: {//wifi failed
            S_PRINTLN(MES_WF_FAIL);
            return NO_WIFI;
            break;
        }
    }//end switch
    return NO_WIFI; //default
}//end Export_begin
//------------------------------- MODE 10: CLEAR ALL SENT DATA SAVED IN SD CARD -------------------------------
//------------------------------------------------------------------------------------------
static void ClearAll_sentData() {
    oled_done();
    SD_ClearSent();//main function of this function
    delay(800);
    oled_clear();//oled_Clock_Updater();
    oled_POINTER2();oled_mainMenu_3();
}//ClearAll_sentData
//--------------------------------------------------------------
// FUNCTION DEFINITIONS - APPLICATION FUNCTIONS
//--------------------------------------------------------------


#endif //_C1_SCENARIOS_CPP
