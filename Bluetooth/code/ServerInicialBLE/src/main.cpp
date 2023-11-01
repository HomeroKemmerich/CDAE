/*
Engenharia de Computação - UPF
Comunicação de dados em Aplicações Embarcadas
Marcelo Trindade Rebonatto
28/10/2023
Server Inicial BLE
Adaptado de Based on Neil Kolban example for IDF: 
    https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updates by chegewara
*/

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "models/MyCharacteristicCallbacks.cpp"
#include "models/MyServerCallbacks.cpp"

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID         "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID  "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void setup() {
    delay(1000);
    Serial.begin(9600);
    BLEServer *pServer;                 /* Objeto para o Servidor BLE */
    BLEService *pService;               /* Objeto para o Servico */
    BLECharacteristic *pCharacteristic; /* Objeto para uma Caracteristica */
    BLEAdvertising *pAdvertising;       /* Objeto para anuncio de Servidor */

    /* Servidor */
    Serial.println("Iniciando o Servidor BLE");
    BLEDevice::init("Homero BLE"); /* modifique aqui para seu nome ou outra identificação */
    pServer = BLEDevice::createServer();

    /* Criando o Serviço */
    pService = pServer->createService(SERVICE_UUID);
    
    /* Criando e Ajustando a caracteristica */
    pCharacteristic = pService->createCharacteristic(
                          CHARACTERISTIC_UUID,
                          BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
                          );

    pCharacteristic->setValue("Hello World de BLE Homero");

    /* Adicionando funções de Callback */
    // Adiciona funcionalidades de manipulação da característica
    pCharacteristic->setCallbacks(new MyCharacteristicCallbacks());

    // Adiciona funcionalidades de manipulação do servidor
    pServer->setCallbacks(new MyServerCallbacks());

    Serial.println("Caracteristica definida!");

    /* Iniciando o Servico */
    pService->start();

    /* Criando e configurando o anuncio */
    pAdvertising = BLEDevice::getAdvertising();
    // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    /* Inicia a anunciar */
    BLEDevice::startAdvertising();
    Serial.println("Anuncio configurado e iniciado. Pode-se conectar e ler do Cliente");
}

void loop() {
    // put your main code here, to run repeatedly:
    delay(random(1993, 2017));
}