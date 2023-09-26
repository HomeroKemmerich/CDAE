/*
Engenharia de Computação - UPF
Comunicação de dados em Aplicações Embarcadas
Marcelo Trindade Rebonatto
29/08/2023
Conexão Wifi
*/

#include <WiFi.h>

#define EAP_ANONYMOUS_IDENTITY "anonymous@tuke.sk" //anonymous@example.com, or you can use also nickname@example.com
#define EAP_IDENTITY "<Login de usuário>"  //login
#define EAP_PASSWORD "<Senha do Usuário>"  //password for account

const char* ssid = "LCI_01";
const char* passwd = "embarcados";

const uint16_t port = 0; //porta onde está aguardando a mensagem
const char *host = "<IP onde está esperando a mensagem>";

void setup() {
    Serial.begin(9600);
    delay(1000);
    Serial.println();
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);
    //WiFi.begin(ssid);
    //WiFi.begin(ssid, passwd);

    // WiFi.begin(ssid, WPA2_AUTH_PEAP, EAP_ANONYMOUS_IDENTITY, EAP_IDENTITY, EAP_PASSWORD); //WITHOUT CERTIFICATE - WORKING WITH EXCEPTION ON RADIUS SERVER

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
    if (WiFi.isConnected()){
        Serial.println("Connected to the WiFi network");
        delay(1000);
        Serial.println(WiFi.localIP());
        delay(1000);
        Serial.println(WiFi.macAddress());
        delay(1000);
    }
}