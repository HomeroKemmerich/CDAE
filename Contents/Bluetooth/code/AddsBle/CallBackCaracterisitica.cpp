/* tratamento de valores das Carateristicas */
class MyCharacteristicCallbacks: public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic){
        std::string value = pCharacteristic->getValue();

        String uuid = pCharacteristic->getUUID().toString().c_str();

        Serial.print("UUID ");
        Serial.println(uuid.c_str());

        if (value.length() > 0){
            Serial.println("*********");
            Serial.print("New value: ");
            for (int i = 0; i < value.length(); i++){
                Serial.print(value[i]);
            }

            Serial.println();
            Serial.println("*********");
        }
    }
};
