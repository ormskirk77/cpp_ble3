#include <esp_log.h>
#include <string>
#include <stdio.h>

#include "ble_libs/BLEUtils.h"
#include "ble_libs/BLEServer.h"
#include <esp_log.h>
#include <string>
#include <iostream>

#include "ble_libs/BLEDevice.h"
#include "sdkconfig.h"


// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

extern "C" {
	void app_main(void);
}

#define SERVICE_UUID         "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID  "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHARACTERISTIC_UUID2 "54059634-9448-404f-9af4-7d14556f3ad8"
#define CHARACTERISTIC_UUID3 "78f8a814-7b20-40ca-b970-0aba448c53b1"
#define CHARACTERISTIC_UUID4 "03a55273-c1ef-4eab-a6c0-7ff11509122f"
#define CHARACTERISTIC_UUID5 "0d19566d-2144-4443-9779-19d42e283439"
bool deviceConnected = false;


class DSP_ServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class DSP_Callback: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      printf("DSP SERVER CHANGED PARAMS............................................................\n");
    }
    void onRead(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      std::cout << "VALUE HAS CHANGED TO: " << rxValue;
      std::cout << ".........................................................................................\n";
    }

};


void app_main(void)
{

	printf("DSP SERVER STARTING UP............................................................\n");

	BLEDevice::init("TIM");

	  BLEServer *pServer = BLEDevice::createServer();

	  pServer->setCallbacks(new DSP_ServerCallbacks());

	  BLEService *pService = pServer->createService(SERVICE_UUID);
	  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
	                                         CHARACTERISTIC_UUID,
	                                         BLECharacteristic::PROPERTY_READ |
	                                         BLECharacteristic::PROPERTY_WRITE
	                                       );
	  pCharacteristic->setCallbacks(new DSP_Callback);
	  pCharacteristic->setValue("Tim's BT Doobery");


	  pService->start();




	  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
	  pAdvertising->addServiceUUID(SERVICE_UUID);
	  pAdvertising->setScanResponse(true);
	  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
	  pAdvertising->setMinPreferred(0x12);
	  pAdvertising->setScanResponse(true);
	  BLEDevice::startAdvertising();



} // app_main
