/*
Engenharia de Computação - UPF
Comunicação de dados em Aplicações Embarcadas
Marcelo Trindade Rebonatto
22/08/2023
Simples pisca led
*/
#include <Arduino.h>

void setup() {
    // put your setup code here, to run once:
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
    Serial.begin(9600); //INICIALIZA A SERIAL COM TAXA DE 9600 BAUDS
    Serial.println("LED DESLIGADO"); //IMPRIME O TEXTO NO MONITOR SERIAL
}

void loop() {
    // put your main code here, to run repeatedly:
    digitalWrite(2, HIGH);
    Serial.println("LED ON"); //IMPRIME O TEXTO NO MONITOR SERIAL
    delay(1000);
    digitalWrite(2, LOW);
    Serial.println("LED OFF"); //IMPRIME O TEXTO NO MONITOR SERIAL
    delay(1000);
}

// put function definitions here:
