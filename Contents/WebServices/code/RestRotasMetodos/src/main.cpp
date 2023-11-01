/*
Engenharia de Computação - UPF
Comunicação de dados em Aplicações Embarcadas
Marcelo Trindade Rebonatto
06/10/2023
Consumidor Rest com Rotas e métodos
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
// #include "senha.h"

#define EAP_ANONYMOUS_IDENTITY "anonymous@tuke.sk" //anonymous@example.com, or you can use also nickname@example.com
#define EAP_IDENTITY "rebonatto"  //login

const char* ssid = "LCI01";
const char* passwd = "up3@wz01";

unsigned long lastTime = 0;
// Ajusta par requisição a cada 5 segundos (5000)
unsigned long timerDelay = 2000;

// Your Domain name with URL path or IP address with path
// Inserção do URI (URL + URN) a acessar
String uri = "http://192.168.1.6:8000/";

void acessaGET(String URN);
void acessaPOST(String URN);
void acessaPUT(String URN);
void testarRotas();
void testarArgumentos();
void testarArgumentosQuery();
void testarMetodos();


void setup() {
    Serial.begin(9600);
    delay(1000);
    Serial.println();
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);
    // WiFi.begin(ssid);
    WiFi.begin(ssid, passwd);

    //WiFi.begin(ssid, WPA2_AUTH_PEAP, EAP_ANONYMOUS_IDENTITY, EAP_IDENTITY, EAP_PASSWORD); //WITHOUT CERTIFICATE - WORKING WITH EXCEPTION ON RADIUS SERVER

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("MAC address: ");
    Serial.println(WiFi.macAddress());
    Serial.println("");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    if ((millis() - lastTime) > timerDelay) {
        if(WiFi.status()== WL_CONNECTED){
            // testarRotas();
            testarMetodos();
            // testarArgumentos();
            //testarArgumentosQuery();
        }
        else {
            Serial.println("WiFi Disconnected");
        }
        lastTime = millis();
    }
}

void testarArgumentosQuery(){
    /* Usar com serviço queryparam.py */
    int x = 5, y = 16;
    String param, URN;
    String um = String(x);
    String dois = String(y);

    URN = "soma/";
    param = "?valor1=";
    param.concat(um);
    param.concat("&valor2=");
    param.concat(dois);
    URN.concat(param);

    acessaGET("soma/?valor1=5&valor2=16");
    delay(500);
    acessaGET(URN);
    delay(500);
    acessaGET("somadefault/?valor2=23");
    delay(500);
    acessaGET("somadefault/");
}

void testarArgumentos(){
    /* Usar com serviço argrotas.py */
    /* A URI não está bem formada*/
    acessaGET("semtipo/bla");
    delay(500);
    acessaGET("semtipo/bla/");
    delay(500);
    acessaGET("comtipo/3");
    delay(500);
    /* teste deve retornar erro */
    acessaGET("comtipo/Bla");
}

void testarMetodos(){
    /* Usar com serviço metodos.py */
    acessaGET("");
    // delay(500);
    // acessaGET("pessoa/");
    delay(500);
    acessaPOST("pessoa/");
    // delay(500);
    // acessaPUT("contato/");
}


void testarRotas(){
    /* Usar com serviço rotas.py */
    String add = "teste/";

    acessaGET("");
    delay(500);
    acessaGET(add);
    delay(500);
    acessaGET("teste/bla/");
}

void acessaPUT(String URN){
    HTTPClient http;
    String rota;

    // Configura a conexão com URI via http
    rota = uri.c_str();
    rota.concat(URN.c_str());
    http.begin(rota.c_str());

    //http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Envia uma requisição com o método PUT
    int httpResponseCode = http.PUT("");

    if (httpResponseCode > 0) {
        Serial.print("Código de resposta HTTP: ");
        Serial.println(httpResponseCode);
        if (httpResponseCode == 200){
            Serial.print("Retorno PUT de ");
            Serial.println(rota.c_str());
            String payload = http.getString();
            Serial.println(payload);
        }
        else {
            String payload = http.getString(); // Para evitar erros na biblioteca
            Serial.print("Erro no processamento da requisição ");
            Serial.println(httpResponseCode);    
        }
        timerDelay = 2000;
    }
    else {
        Serial.print("Erro de acesso ao Serviço: ");                
        Serial.println(httpResponseCode);
        timerDelay = 100;
    }
    // Free resources
    http.end();
}


void acessaPOST(String URN){
    HTTPClient http;
    String rota;

    String marshalledJson, prettyMarshalledJson;

    // Configura a conexão com URI via http
    rota = uri.c_str();
    rota.concat(URN.c_str());
    http.begin(rota.c_str());

    //http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Envia uma requisição com o método POST
    //  - Serializa o JSON
    //  - Envia o JSON serializado por POST
    StaticJsonDocument<200> unmarshalledJson;
    
    unmarshalledJson["nome"] = "Homero";
    unmarshalledJson["id"] = 1;
    unmarshalledJson["altura"] = 1.71;

    serializeJson(unmarshalledJson, marshalledJson); 
    serializeJsonPretty(unmarshalledJson, prettyMarshalledJson);

    int httpResponseCode = http.POST(marshalledJson);
    

    if (httpResponseCode > 0) {
        Serial.print("Código de resposta HTTP: ");
        Serial.println(httpResponseCode);
        if (httpResponseCode == 200){
            Serial.print("Retorno POST de ");
            Serial.println(rota.c_str());
            String payload = http.getString();

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

            Serial.print("nome: [");
            String nome = jsonResponse["nome"];
            Serial.print(nome);
            Serial.println("]");
        }
        else {
            String payload = http.getString(); // Para evitar erros na biblioteca
            Serial.print("Erro no processamento da requisição ");
            Serial.println(httpResponseCode);    
        }
        timerDelay = 2000;
    }
    else {
        Serial.print("Erro de acesso ao Serviço: ");                
        Serial.println(httpResponseCode);
        timerDelay = 100;
    }
    // Free resources
    http.end();
}

void acessaGET(String URN){
    HTTPClient http;
    String rota;

    // Configura a conexão com URI via http
    rota = uri.c_str();
    rota.concat(URN.c_str());
    http.begin(rota.c_str());

    // Envia uma requisição com o método GET
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
        Serial.print("Código de resposta HTTP: ");
        Serial.println(httpResponseCode);
        if (httpResponseCode == 200){
            Serial.print("Retorno GET de ");
            Serial.println(rota.c_str());
            String payload = http.getString();
            Serial.println(payload);

            //Trabalhando com JSON
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
        }
        else {
            String payload = http.getString(); // Para evitar erros na biblioteca
            Serial.print("Erro no processamento da requisição ");
            Serial.println(httpResponseCode);    
            Serial.println(http.getString());
        }
        timerDelay = 2000;
    }
    else {
        Serial.print("Erro de acesso ao Serviço: ");                
        Serial.println(httpResponseCode);    
        timerDelay = 100;
    }
    // Free resources
    http.end();
}