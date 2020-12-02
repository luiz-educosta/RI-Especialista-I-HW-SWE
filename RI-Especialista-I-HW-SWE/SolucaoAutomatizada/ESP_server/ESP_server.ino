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

int statussensor = 0;
int statusledvm = 0;
int statusbuzzer = 0;
int statusledvd = 0;
int comunicacaoOK = 1;

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
    BUFFER_SIZE 
};

#define IS_SERVER
#ifdef IS_SERVER

//Cria o server na porta definida por 'SERVER_PORT'
WiFiServer server(SERVER_PORT);

void setup()
{
    Serial.begin(115200);
    delay(500);
    
    //Coloca este ESP como Access Point
    WiFi.mode(WIFI_AP);
    //SSID e Senha para se conectarem a este ESP
    WiFi.softAP(SSID, PASSWORD);
    
    //Inicia o server
    server.begin();
    Serial.println("LoRa Conectado");
}

void loop()
{
    //Verifica se tem algum cliente se conectando
    WiFiClient client = server.available();
    
    if (client)
    {      
        //Se o cliente tem dados que deseja nos enviar
        if (client.available())
        {
            //buffer para colocar os dados
            uint8_t buffer[Protocol::BUFFER_SIZE];
            //Colocamos os dados enviados pelo cliente no buffer
            int len = client.read(buffer, Protocol::BUFFER_SIZE);
            
            //Verifica qual o pino que o cliente enviou
            int pinNumber = buffer[Protocol::PIN];
            int pinNumber1 = buffer[Protocol::PIN1];
            int pinNumber2 = buffer[Protocol::PIN2];
            int pinNumber3 = buffer[Protocol::PIN3];
            
            //Verifica qual o valor deste pino
            int sensor = buffer[Protocol::VALUE];
            int ledvm = buffer[Protocol::VALUE1];
            int buzzer = buffer[Protocol::VALUE2];
            int ledvd = buffer[Protocol::VALUE3];
            
            //Coloca o pino em modo de saída
            pinMode(pinNumber, OUTPUT);
            pinMode(pinNumber1, OUTPUT);
            pinMode(pinNumber2, OUTPUT);
            pinMode(pinNumber3, OUTPUT);
            
            //Altera o estado do pino para o valor passado
            digitalWrite(pinNumber, sensor);
            digitalWrite(pinNumber1, ledvm);
            digitalWrite(pinNumber2, buzzer);
            digitalWrite(pinNumber3, ledvd);            
            
            statussensor = digitalRead(sensor);
            statusledvm = digitalRead(ledvm);
            statusbuzzer = digitalRead(buzzer);
            statusledvd = digitalRead(ledvd);

            //lógica para leitura dos dados recebidos
           if(sensor == HIGH){
              Serial.println("Sensor detectado!");
              Serial.println("Status Led Vermelho:");
              Serial.println(ledvm);
              Serial.println("Status Buzzer:");
              Serial.println(buzzer);
              
              delay(500);
            }else{
              Serial.println("");
              Serial.println("Sensor Desativado!");
              Serial.println("Status Led Verde:");
              Serial.println(ledvd);
              }  
        }
        //Fecha a conexão com o cliente
        client.stop();
    }
}
//Encerra o #ifdef do começo do arquivo
#endif
