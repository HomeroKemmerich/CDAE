/* Tratamento do Anuncio de serviço quando disconecta */
class MyServerCallbacks: public BLEServerCallbacks {
    void onDisconnect(BLEServer* pServer) {
        Serial.println("Conexão desfeita ...\n Voltando a anunciar ...");
        BLEDevice::startAdvertising();
    };
};

