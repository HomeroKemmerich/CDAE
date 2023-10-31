/* Global */
BLEDescriptor notifyDescriptor(BLEUUID((uint16_t)0x2902));
int valor = 0;



/* No Setup */
notifyCharacteristic = pService->createCharacteristic(
                                 CHARACTERISTIC_UUID3,
                                 BLECharacteristic::PROPERTY_NOTIFY 
                                 );

notifyDescriptor.setValue("Valor incrementado");
notifyCharacteristic->addDescriptor(&notifyDescriptor);



/* No Loop ou outro local */
notifyCharacteristic->setValue(valor); 
notifyCharacteristic->notify();
