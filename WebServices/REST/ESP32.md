---
title: ESP32
date: 2023-10-17
---
# REST com ESP32

## Arquivos

- [Rotas métodos REST](./RestRotasMetodos)

## Notas

> ATENÇÃO: não esqueça de [definir o IP do *host* na aplicação em python](./Fast%20API.md#conexao-utilizando-esp-32).

- A ideia aqui é que a ESP-32 realize requisições no servidor automaticamente, [de acordo com o serviço que está rodando](./RestRotasMetodos/src/main.cpp:61)

```arduino
/// @main.cpp:61

    //testarRotas();
    testarMetodos();
    //testarArgumentos();
    //testarArgumentosQuery();
```
### JSON

- [**ArduinoJson**](https://arduinojson.org/)
- *Marshaling* $\neq$ *serializing*
    - *Marshaling*: empacotamento. Adaptar a informação do código para o formato de destino.
        ```json
        id = 5;
        nome = "Homero";
        altura = 1.71;
        ---
        {
            "id": 5,
            "nome": "Homero",
            "altura": 1.71
        } 
        ```
    - *Serializing*: serialização. Encadear as informações em um *array* de bits.
        ```json
        {
            "id": 5,
            "nome": "Homero",
            "altura": 1.71
        } 
        ---
        010100011010110...
        ```

#### Adicionando a biblioteca ao PlatformIO

- PlatformIO > Home > Libraries
- Procure a biblioteca "ArduinoJson"
- Selecione o projeto a ser adicionado

#### Implementações

```arduino
///@main.cpp:234
StaticJsonDocument<200> jsonResponse;
DeserializationError error = deserializeJson(jsonResponse, payload);

if(error){
    Serial.print(F("DeserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
}

for (JsonPair keyValue : jsonResponse.as<JsonObject>())
{
    Serial.println(keyValue.key().c_str());
}

Serial.print("message: [");
String message = jsonResponse["message"];
Serial.print(message);
Serial.println("]");
```

