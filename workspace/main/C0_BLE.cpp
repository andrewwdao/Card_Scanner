/*------------------------------------------------------------*-
  Bluetooth Low Energy for supporting Wifi sign in - function file
  ESP32 CORE0 - PROTOCOL CORE
  (c) An Minh Dao - Bernd Giesecke 2019
  version 1.00 - 12/03/2019
---------------------------------------------------------------
 *  PUBLIC FUNCTIONS CONTAIN:
 *  
 *  PRIVATE FUNCTIONS CONTAIN:
 * 
 * 
 * CAUTION: 
 * + Use ArduinoJson 6.x 
 * + only 1 BLE connection can be established, can be changed in menuconfig
 --------------------------------------------------------------*/
#ifndef _C0_BLE_CPP
#define _C0_BLE_CPP
#include "C0_BLE.h"

// ------ Private constants -----------------------------------
/** Unique device name */
//char apName[] = "ESP32-xxxxxxxxxxxx";
char apName[] = "AttenChecking Sys";
// List of Service and Characteristic UUIDs - creat at: https://www.uuidgenerator.net/
// If change this, then you also need to change the Android source code and recompile it as well, because the UUIDs are hardcoded in the Android application
#define SERVICE_UUID  "0000aaaa-ead2-11e7-80c1-9a214cf093ae"
#define WIFI_UUID     "00005555-ead2-11e7-80c1-9a214cf093ae"

// ------ Private function prototypes -------------------------

// ------ Private variables -----------------------------------
/** Characteristic for digital output */
BLECharacteristic *pCharacteristicWiFi;
/** BLE Advertiser */
BLEAdvertising *pAdvertising;
/** BLE Service */
BLEService *pService;
/** BLE Server */
BLEServer *pServer;

/** Buffer for JSON string */
// MAx size is 51 bytes for frame: 
// {"ssidPrim":"","pwPrim":"","ssidSec":"","pwSec":""}
// + 4 x 32 bytes for 2 SSID's and 2 passwords
// ------ PUBLIC variable definitions -------------------------
/* BLE receive status */
bool BLEreceived = false;
/** Flag if stored AP credentials are available */
bool BLEhasCredentials = false;

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
/**
 * MyServerCallbacks
 * Callbacks for client connection and disconnection:
 * If a client connects the BLE advertising of the service stops automatically. 
 * So in case a client disconnects, we start the advertising here again.
 */
class MyServerCallbacks: public BLEServerCallbacks { //MyServerCallbacks is a public inherit class of BLEServerCallbacks class. 
	// TODO this doesn't take into account several clients being connected
	void onConnect(BLEServer* pServer) {
		S_PRINTLN(F("--> Connected!")); //BLE client connected
	};

	void onDisconnect(BLEServer* pServer) {
		S_PRINTLN(F("--> Disconnected.")); //BLE client disconnected
		pAdvertising->start();
	}
};

/**
 * MyCallbackHandler
 * Callbacks for BLE client read/write requests:
 * The characteristic write events receives the WiFi credentials from the Android app. 
 * The data is encoded with a simple method (XOR with a key) to make the data unreadable for sniffers. 
 * First step is to decode the received data.
 * 
 * 1 Credential data: {"ssidPrim":"SSID1name","pwPrim":"SSID1password"}
 * 2 Credential data: {"ssidPrim":"SSID1name","pwPrim":"SSID1password","ssidSec":"SSID2name","pwSec":"SSID2password"}
 */
class MyCallbackHandler: public BLECharacteristicCallbacks {
	void onWrite(BLECharacteristic *pCharacteristic) { //recieve data from BLE client (smartphone)
		std::string value = pCharacteristic->getValue();
		if (value.length() == 0) {return;}
		//D_PRINTLN("Received over BLE: " + String((char *)&value[0]));
		// Decode data
		int keyIndex = 0;
		for (int index = 0; index < value.length(); index ++) {
			value[index] = (char) value[index] ^ (char) apName[keyIndex];
			keyIndex++;
			if (keyIndex >= strlen(apName)) keyIndex = 0;
		}//end for

		/** Transfer JSON string "value" into JSON buffer to get needed information */
		StaticJsonDocument<200> jsonBuffer; //needed to be locally declared
		if (!deserializeJson(jsonBuffer,value)) { //return 0 if successfully transfer
			if (jsonBuffer.containsKey("ssidPrim") && jsonBuffer.containsKey("pwPrim")) {
				String BLE_WSSID = jsonBuffer["ssidPrim"];
				String BLE_WPASS = jsonBuffer["pwPrim"];
				NVS_WIFIdata_write(BLE_WSSID,BLE_WPASS);

				oled_BLE_receivedData();
				D_PRINTLN("SSID: "+ BLE_WSSID);
				D_PRINTLN("Password: "+ BLE_WPASS);
				BLEreceived = true;
				BLEhasCredentials = true;
			} else if (jsonBuffer.containsKey("erase")) { //if command is erase
				oled_BLE_eraseData();
				D_PRINTLN();
				//S_PRINTLN(F("BLE command recieved!"));
				D_PRINTLN(F("Erasing..."));
				NVS_WIFIdata_delete();
				BLEreceived = true;
				BLEhasCredentials = false;
				delay(3000);
				oled_wifi_BLEupdater();

				// int err;
				// err=nvs_flash_init();
				// Serial.println("nvs_flash_init: " + err);
				// err=nvs_flash_erase();
				// Serial.println("nvs_flash_erase: " + err);
			} else if (jsonBuffer.containsKey("reset")) { //TODO: FIX RESET TO EXIT BLE MODE
				D_PRINTLN(F("Reset command recieved!"));
				D_PRINTLN(MES_NORMAL);
				NVS_system_write(SYS_NORMAL); //return to normal mode
				WiFi.disconnect();
				ESP.restart();
			}//end if else
		} else {
			D_PRINTLN(F("Invalid BLE command!"));
		}//end if else
		jsonBuffer.clear(); //needed to be clear after every use
	}; //end onWrite

	/* Request data command recieved. Prepare to send data */
	void onRead(BLECharacteristic *pCharacteristic) { //send data to BLE client (smartphone)
		String wifiCredentials;
		StaticJsonDocument<200> jsonBuffer; //needed to be locally declared
		/** Json object for outgoing data */
		jsonBuffer["ssidPrim"] = NVS_wifiSSID_read();
		jsonBuffer["pwPrim"]   = NVS_wifiPASS_read();
		// Convert JSON object into a string
		serializeJson(jsonBuffer, wifiCredentials);
		jsonBuffer.clear(); //mission of JSON is done here
		// encode the data
		int keyIndex = 0;
		//D_PRINTLN("Prepare to send Package: " + wifiCredentials);
		//{"ssidPrim":"SSID1name","pwPrim":"SSID1password"}
		for (int index = 0; index < wifiCredentials.length(); index ++) {
			wifiCredentials[index] = (char) wifiCredentials[index] ^ (char) apName[keyIndex];
			keyIndex++;
			if (keyIndex >= strlen(apName)) keyIndex = 0;
		}//end for

		pCharacteristicWiFi->setValue((uint8_t*)&wifiCredentials[0],wifiCredentials.length());
	}; //end onRead
};//end class MyCallbackHandler: public BLECharacteristicCallbacks

/**
 * initBLE
 * Initialize BLE service and characteristic
 * Start BLE server and service advertising
 * First the BLE device is initializes, then we start the BLE server and assign the callbacks for connection and reconnection of clients.
 * After that BLE service and the characteristic for the WiFi credentials is created.
 * And then the server and the advertising is started
 */
void initBLE() {
	// Initialize BLE and set output power
	BLEDevice::init(apName);
	BLEDevice::setPower(ESP_PWR_LVL_P7);

	// Create BLE Server
	pServer = BLEDevice::createServer();

	// Set server callbacks
	pServer->setCallbacks(new MyServerCallbacks());

	// Create BLE Service
	pService = pServer->createService(BLEUUID(SERVICE_UUID),20);

	// Create BLE Characteristic for WiFi settings
	pCharacteristicWiFi = pService->createCharacteristic(
		BLEUUID(WIFI_UUID),
		BLECharacteristic::PROPERTY_READ |
		BLECharacteristic::PROPERTY_WRITE
	);

	//Assign Callback for BLE client read/write requests
	pCharacteristicWiFi->setCallbacks(new MyCallbackHandler());

	// Start the service
	pService->start();

	// Start advertising
	pAdvertising = pServer->getAdvertising();
	pAdvertising->start();
}//end initBLE

#endif //_C0_BLE_CPP
