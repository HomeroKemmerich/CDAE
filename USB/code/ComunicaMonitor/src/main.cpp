/*
Engenharia de Computação - UPF
Comunicação de Dados em Aplicações Embarcadas
Marcelo Trindade Rebonatto
22/08/2023
Programa com leitura de teclado do PC via USB
*/
#include <Arduino.h>

#define PINOLED 2

// put function declarations here:
void trataEntrada(char c);
void blinkLED();

char c;
int led;
bool blink;
int delayms = 1000;

void setup() {
    // put your setup code here, to run once:
    delay(1000);                   // Tempo para verificar a inicialização no terminal
    pinMode(PINOLED, OUTPUT);
    digitalWrite(PINOLED, LOW);
    Serial.begin(9600); //INICIALIZA A SERIAL COM TAXA DE 9600 BAUDS
    //Serial.begin(9600, SERIAL_8O1); //INICIALIZA A SERIAL COM TAXA DE 9600, 
                                      // 8 bits de dados, Sem controle de paridade e 1 bit de parada
    Serial.println("");
    Serial.println("LED DESLIGADO");        //IMPRIME O TEXTO NO MONITOR SERIAL    
    Serial.println("Aguardando comando: "); //IMPRIME O TEXTO NO MONITOR SERIAL    
}

void loop() {
    
    if (Serial.available() > 0){ // Verifica se tem dados a receber na porta serial
    
        // while (!Serial.available());            // * Busy wait aguardando algo na serial * 
    
        c = Serial.read();       // Recebe o caracter digitado na entrada de dados do monitor serial
        trataEntrada(c);
        Serial.println("Aguardando comando: "); 
    }

    blinkLED();
}

void trataEntrada(char c){
    bool fez;
    
    fez = true;

    if (c == 'l'){ 
        fez = false;
        blink = false;
        if (led == 0 ){ //SE VARIÁVEL FOR IGUAL A 0(DESLIGADO), liga
            digitalWrite(PINOLED, HIGH); //LIGA O LED
            led = 1; //VARIÁVEL RECEBE O VALOR 1 (LIGADO)
            Serial.println("LED LIGADO"); //IMPRIME O TEXTO NO MONITOR SERIAL
        } else {
            Serial.println("LED JÁ ESTA LIGADO"); //IMPRIME O TEXTO NO MONITOR SERIAL
        }
    }
    if (c == 'd'){ 
        fez = false;
        blink = false;
        if (led == 1){ //SE VARIÁVEL FOR IGUAL A 0(DESLIGADO), liga
            digitalWrite(PINOLED, LOW); //DESLIGA O LED
            led = 0; //VARIÁVEL RECEBE O VALOR 0 (DESLIGADO)
            Serial.println("LED DESLIGADO"); //IMPRIME O TEXTO NO MONITOR SERIAL
        }
        else{
            Serial.println("LED JÁ ESTA DESLIGADO"); //IMPRIME O TEXTO NO MONITOR SERIAL
        }
    }
    if(c == 'p'){
        fez = false;
        led = 0;
        blink = true;
    }
    if(c == '+'){
        while (delayms >= 125)
        {
            delayms /= 2; 
        }
        
    }
    if(c == '-'){
        while (delayms >= 4000)
        {
            delayms *= 2; 
        }
    }
    if (fez)
        Serial.println("Opção Inválida Digitada"); //IMPRIME O TEXTO NO MONITOR SERIAL
}

void blinkLED(){
    if(blink){
        digitalWrite(PINOLED, LOW); //DESLIGA O LED
        delay(delayms);
        digitalWrite(PINOLED, HIGH);
        delay(delayms);
    }
}