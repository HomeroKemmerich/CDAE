---
title: ESP32 BLE
date: 2023-10-31
tags: 
    - ESP32 
    - BLuetooth 
    - BLE
---
# Bluetooth LE

## Operações

## Escrita em característica

```arduino
    //@MyCharacteristicCallbacks.cpp
    class MyCharacteristicCallbacks : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic)
    {
        std::string value = pCharacteristic->getValue();
        if (value.length() > 0)
        {
            Serial.println("*********");
            Serial.print("New value: ");
            for (int i = 0; i < value.length(); i++)
            {
                Serial.print(value[i]);
            }
            Serial.println();
            Serial.println("*********");
        }
    }
};
```

```arduino
    //@main.cpp
    pCharacteristic->setCallbacks(new MyCharacteristicCallbacks());
```

![Escrevendo a partir do app](./videos/Screenrecorder-2023-10-31-21-32-57-703.mp4)

![Log do conteúdo da característica](./pictures/image.png)

## *Advertising*

- Após conectar uma vez com o serviço, ele não consegue ser reconectado

![Server não aparece no app](./videos/Screenrecorder-2023-10-31-21-06-07-980.mp4)

- É necessário iniciar um novo anúncio após desconectar

    ```arduino
    //@MyServerCallbacks.cpp
    class MyServerCallbacks: public BLEServerCallbacks {
        void onDisconnect(BLEServer* pServer) {
        Serial.println("Cliente desconectado");
        BLEDevice::startAdvertising();
        };
    };
    ```

    ```arduino
        //@main.cpp
        pCharacteristic->setCallbacks(new MyServerCallbacks());
    ```

    ![Server anunciado no app](./videos/Screenrecorder-2023-10-31-21-07-35-291.mp4)