# Bluetooth LE

## Escrita em característica

- [MyCharacteristicsCallbacks.cpp](../code/ServerInicialBLE/src/models/MyCharacteristicCallbacks.cpp)

```arduino
    //@main.cpp:51
    pCharacteristic->setCallbacks(new MyCharacteristicCallbacks());
```

Após conectar uma vez com o serviço, ele não consegue ser reconectado
![Alt text](image.png)