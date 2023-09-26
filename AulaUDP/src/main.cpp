/*
Engenharia de Computação - UPF
Comunicação de dados em Aplicações Embarcadas
Marcelo Trindade Rebonatto
29/08/2023
Envio de mensagem via Socket UDP
*/

#include <WiFi.h>

#define EAP_ANONYMOUS_IDENTITY "anonymous@tuke.sk" //anonymous@example.com, or you can use also nickname@example.com
#define EAP_IDENTITY "<Login de usuário>"  //login
#define EAP_PASSWORD "<Senha do Usuário>"  //password for account

const char* ssid = "<Nome da rede>";
const char* passwd = "<Senha da rede>";

const uint16_t port = 0; //porta onde está aguardando a mensagem
const char *host = "<IP onde está esperando a mensagem>";

WiFiClient client;   // Para conectar com WiFi
WiFiUDP udp;         // Cria um objeto da classe UDP.

int x;

void setup() {
    Serial.begin(9600);
    delay(1000);
    Serial.println();
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);
    //WiFi.begin(ssid);
    //WiFi.begin(ssid, passwd);

    WiFi.begin(ssid, WPA2_AUTH_PEAP, EAP_ANONYMOUS_IDENTITY, EAP_IDENTITY, EAP_PASSWORD); //WITHOUT CERTIFICATE - WORKING WITH EXCEPTION ON RADIUS SERVER

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
    if (WiFi.status() == WL_CONNECTED) {//Só ira enviar dados se estiver conectado.
        x = random(0, 1000);//Gera um numero aleatorio entre 0 e 1000.
        udp.beginPacket(host, port);//Inicializa o pacote de transmissao ao IP e PORTA.
        udp.println(x);//Adiciona-se o valor ao pacote.
        udp.endPacket();//Finaliza o pacote e envia.
        Serial.print("Mensagem enviada com "); 
        Serial.println(x);
    }
    delay(10000);
}