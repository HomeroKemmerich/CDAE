---
title: ESP32 BLE
date: 2023-10-31
tags: 
    - ESP32 
    - Bluetooth 
    - BLE
---
# Bluetooth LE com ESP32

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

## Notificações

- Você não precisa criar uma nova característica para adicionar a propriedade `NOTIFY`

- Primeiro, torne a variável `pCharacteristic` global. Assim você poderá utilizá-la no `void loop()` ou `void setup()`

- Crie um descritor para a característica de notificação

    ```arduino
    BLEDescriptor notifyDescriptor(BLEUUID((uint16_t)0x2902));
    ```
- Crie um contador para ser observado

    ```arduino
    int valueToBeNotified = 0;
    ```

- No `void setup()`:
    - Inclua a propriedade `NOTIFY` na característica escolhida.

    ```arduino
    pCharacteristic = pService->createCharacteristic(
                          CHARACTERISTIC_UUID,
                          BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | 
                          BLECharacteristic::PROPERTY_NOTIFY
    );
    ```
    - Adicione o descritor à característica

    ```arduino
    pCharacteristic->addDescriptor(&notifyDescriptor);
    ```

- no `void loop()`:
    - Adicione o valor a ser observado à característica
    - Envie a notificação
    - Atualize o valor
    
    ```arduino
    pCharacteristic->setValue(valueToBeNotified);
    pCharacteristic->notify();

    valueToBeNotified++;
    ```

![Notify](./videos/Screenrecorder-2023-11-02-15-36-45-167.mp4)