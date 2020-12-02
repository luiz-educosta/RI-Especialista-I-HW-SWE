/*
RI-Especialista-I-HW-SWE
Cenário: Violação da Porta
Autor: Luiz Eduardo Costa Rodrigues
IDE utilizada: Arduino
Microcontrolador utilizado: Módulo ESP32 WROOM 32
*/
#include <WiFi.h>

#define SSID "Luiz"
#define PASSWORD "02122020"
#define SERVER_PORT 5000

//Protocolo que o Server e o Client utilizarão para se comunicar
enum Protocol{
    PIN, //Pino que se deseja alterar o estado
    VALUE, //Estado para qual o pino deve ir (HIGH = 1 ou LOW = 0)
    PIN1,
    VALUE1,
    PIN2,
    VALUE2,
    PIN3,
    VALUE3,
    BUFFER_SIZE //O tamanho do nosso protocolo. 
};


#ifndef IS_SERVER

//pinagem
int LEDVM = 13;
int LEDVD = 14;
int BUZZER = 27;
#define SENSOR  4

int estadoSensor = 0;

void setup(){

    Serial.begin(115200);
    delay(500);
   
    
    //Pinos em modo de leitura
    pinMode(LEDVM, OUTPUT);
    pinMode(SENSOR, INPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(LEDVD, OUTPUT);
    
    //Conecta ao Access Point criadopelo outro ESP
    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.println("Conectadon a LoRa...");
    }
    Serial.println("LoRa conectado!");
}


void loop(){
  
    //Variável que utliza para conectar ao servidor
    WiFiClient client;
    //Se não conseguiu se conectar então retornamos
    if (!client.connect(WiFi.gatewayIP(), SERVER_PORT)){
        return;
    }

      //lógica para enviar os dados da trava do banco
      estadoSensor = digitalRead(SENSOR);
      
      if (estadoSensor == HIGH){
          digitalWrite(LEDVM, 1);
          digitalWrite(BUZZER, 1);
          digitalWrite(LEDVD, 0);
                  
        } else {
          digitalWrite(LEDVM, 0);
          digitalWrite(BUZZER, 0);
          digitalWrite(LEDVD, 1);
          }
     
      //buffer para colocar os dados
      uint8_t buffer[Protocol::BUFFER_SIZE];
      
      //leitura do pino
      int sensor = digitalRead(SENSOR);
      int ledvm = digitalRead(LEDVM);
      int buzzer = digitalRead(BUZZER);
      int ledvd = digitalRead(LEDVD);
            
      //Coloca no buffer o número do pino o estado queremos enviar
      buffer[Protocol::PIN] = SENSOR;
      buffer[Protocol::PIN1] = LEDVM;
      buffer[Protocol::PIN2] = BUZZER;
      buffer[Protocol::PIN3] = LEDVD;
           
      //Coloca no buffer o estado atual do pino
      buffer[Protocol::VALUE] = sensor;
      buffer[Protocol::VALUE1] = ledvm;
      buffer[Protocol::VALUE2] = buzzer;
      buffer[Protocol::VALUE3] = ledvd;
          
      //Envia e finaliza a conexão
      client.write(buffer, Protocol::BUFFER_SIZE);
      client.flush();
      client.stop();  
      
}
//Encerra o #ifndef do começo do arquivo
#endif
