/*
Engenharia de Computação - UPF
Comunicação de dados em Aplicações Embarcadas
Marcelo Trindade Rebonatto
28/09/2023
Consumidor Rest
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include "senha.h"

#define EAP_ANONYMOUS_IDENTITY "anonymous@tuke.sk" //anonymous@example.com, or you can use also nickname@example.com
#define EAP_IDENTITY "rebonatto"  //login

const char* ssid = "CLARO_2GE5C702";

unsigned long lastTime = 0;
// Ajusta par requisição a cada 5 segundos (5000)
unsigned long timerDelay = 5000;

// Your Domain name with URL path or IP address with path
// Inserção do URI (URL + URN) a acessar
String uri = "http://192.168.0.31:8000/";


void setup() {
    Serial.begin(9600);
    delay(1000);
    Serial.println();
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);
    //WiFi.begin(ssid);
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
            HTTPClient http;
      
            // Configura a conexão com URI via http
            http.begin(uri.c_str());
        
            // Envia uma requisição com o método GET
            int httpResponseCode = http.GET();
        
            if (httpResponseCode > 0) {
                Serial.print("Código de resposta HTTP: ");
                Serial.println(httpResponseCode);
                if (httpResponseCode == 200){
                    String payload = http.getString();
                    Serial.print("Payload: [");
                    Serial.print(payload);
                    Serial.println("]");
                    Serial.print("Size: ");
                    Serial.println(http.getSize());                    
                }
                else {
                    String payload = http.getString(); // Para evitar erros na biblioteca
                    Serial.print("Erro no processamento da requisição ");
                    Serial.println(httpResponseCode);    
                }
            }
            else {
                Serial.print("Erro de acesso ao Serviço: ");                
                Serial.println(httpResponseCode);    
            }
            // Free resources
            http.end();
        }
        else {
            Serial.println("WiFi Disconnected");
        }
        lastTime = millis();
    }
}