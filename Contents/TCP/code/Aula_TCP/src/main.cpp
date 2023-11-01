/*
Engenharia de Computação - UPF
Comunicação de dados em Aplicações Embarcadas
Marcelo Trindade Rebonatto
05/09/2023
Envio de mensagem via Socket TCP
*/

#include <WiFi.h>

#define EAP_ANONYMOUS_IDENTITY "anonymous@tuke.sk" //anonymous@example.com, or you can use also nickname@example.com
#define EAP_IDENTITY "146676"  //login
#define EAP_PASSWORD "Sh1n1g@m1.2023"  //password for account

const char* ssid = "Sou UPF";
const char* passwd = "<Senha da Rede>";

const uint16_t port = 8000;                          // porta onde está aguardando a mensagem
const char *host = "192.168.1.1";   // IP para onde vamos enviar a mensagem
 
unsigned long int last_time = millis();

 
void setup(){
    Serial.begin(9600);
    delay(1000);
    Serial.println();
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);
    //WiFi.begin(ssid);
    //WiFi.begin(ssid, passwd);

    WiFi.begin(ssid, WPA2_AUTH_PEAP, EAP_ANONYMOUS_IDENTITY, EAP_IDENTITY, EAP_PASSWORD); //WITHOUT CERTIFICATE - WORKING WITH EXCEPTION ON RADIUS SERVER
    while (WiFi.status() != WL_CONNECTED){
      delay(500); 
      Serial.println('.');
    }
 
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}
 
void loop(){

    WiFiClient client;

    Serial.println(host);
    Serial.println(port);
    if (! client.connect(host, port)) {
        Serial.println("Falha de conexao");
        delay(1000);
    }
    else {
        Serial.println("Conectado!");
        client.println("Hellow word");
        Serial.println("Desconectando...");
        client.stop();
    }
 
    Serial.print("Aguardando 5 segundos para proximo envio:");
    while ((millis()-last_time) < 5000){
        delay(100);
    }
    last_time = millis();
}