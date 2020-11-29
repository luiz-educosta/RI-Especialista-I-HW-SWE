/*
Tester ICC HW
Cenário: Violação da Porta
Autor: Luiz Eduardo Costa Rodrigues
IDE utilizada: Arduino
Microcontrolador utilizado: Módulo ESP32 LoRa 868/915Mhz com OLED 0.96″
*/

#include <LoRa.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
/* Definições para comunicação com rádio LoRa */
#define SCK_LORA           5
#define MISO_LORA          19
#define MOSI_LORA          27
#define RESET_PIN_LORA     14
#define SS_PIN_LORA        18
 
/* Definições do OLED */
#define OLED_SDA_PIN    4
#define OLED_SCL_PIN    15
#define SCREEN_WIDTH    128 
#define SCREEN_HEIGHT   64  
#define OLED_ADDR       0x3C 
#define OLED_RESET      16
 
/* Offset de linhas no display OLED */
#define OLED_LINE1     0
#define OLED_LINE2     10
#define OLED_LINE3     20
#define OLED_LINE4     30
#define OLED_LINE5     40
#define OLED_LINE6     50 

#define GANHOLORA         20  /* dBm */
#define FREQ               915E6  /* 915MHz de frequência */

/* Variaveis e objetos globais */
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void inicializacaoDisplay(void);
bool comunicacao_gateway_lora(void);

bool comunicacao_gateway_lora(void)
{
    bool status_comunicacao = false;
    Serial.println("Tentando iniciar comunicação com o rádio LoRa...");
    SPI.begin(SCK_LORA, MISO_LORA, MOSI_LORA, SS_PIN_LORA);
    LoRa.setPins(SS_PIN_LORA, RESET_PIN_LORA, LORA_DEFAULT_DIO0_PIN);
     
    if (!LoRa.begin(FREQ)){
        Serial.println("Tentando iniciar comunicação com o rádio LoRa, aguarde...");
        
        /* Escrevendo a mensagem para tentar a comunicação em 5 segundos */
        display.clearDisplay();    
        display.setCursor(0, OLED_LINE1);
        display.print("Tentando iniciar comunicação com o rádio LoRa, aguarde...");
        display.display();
        delay(5000);
        status_comunicacao = false;
    }else {   
        LoRa.setTxPower(GANHOLORA); 
        status_comunicacao = true;
        
        Serial.println("Comunicação com o rádio LoRa ok!");
        
        display.clearDisplay();   
        display.setCursor(0, OLED_LINE1);
        display.print("Ganho da antena estabelecido: ");
        display.println(GANHOLORA);
        display.setCursor(0, OLED_LINE2);
        display.print("Comunicação com o rádio LoRa ok!");
        display.setCursor(0, OLED_LINE3);
        display.display();
        
        //coloca no modulo receptor continuo
        LoRa.receive();
    }
 
    return status_comunicacao;
}

void inicializacaoDisplay(void)
{
    if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)){
        Serial.println("Falha ao inicializar comunicacao com OLED");        
    }else{
        Serial.println("Comunicacao com OLED inicializada com sucesso");
     
        /* Limpa display e configura tamanho de fonte */
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        
    }
}

void setup() {

    /* Configuracao da I²C para o display OLED */
    Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);
 
    /* Inicializando o display */
    inicializacaoDisplay();
 
    /* Escrevendo a mensagem para esperar */
    display.clearDisplay();    
    display.setCursor(0, OLED_LINE1);
    display.print("Aguarde...");
    display.display();
    
    Serial.begin(115200);
    while (!Serial);
    
    /* Verificando a comunicação com LoRa */
    while(comunicacao_gateway_lora() == false);       
  
}
 
void loop() {
   
   /*O pacote é a notificação que o sensor envia via LoRa*/
    string byte_recebido;
    string ultimo_byte_recebido;
    int pacoteRecebido = 0;
    int lora_rssi = 0;

    //notificando que tem informação para receber
    pacoteRecebido = LoRa.parsePacket();

    if(pacoteRecebido) {
    
        //Informando que esta recebendo informação
        display.clearDisplay();   
        display.setCursor(0, OLED_LINE1);
        display.print("RSSI: ");
        display.println(lora_rssi);
        display.setCursor(0, OLED_LINE2);
        display.print("Sensor detectado!");
        display.setCursor(0, OLED_LINE3);
        display.display();

        //verificando a informação que o tx enviou
        while (LoRa.available()) {
        byte_recebido = LoRa.readString();
        ultimo_byte_recebido = LoRa.peek();            
        } 

        /* Escreve RSSI de recepção e informação recebida */
        lora_rssi = LoRa.packetRssi();
        display.clearDisplay();   
        display.setCursor(0, OLED_LINE1);
        display.print("RSSI: ");
        display.println(lora_rssi);
        display.setCursor(0, OLED_LINE2);
        display.print("Dados enviados: ");
        display.setCursor(0, OLED_LINE3);
        display.println(byte_recebido);
        display.display();       
    } else {
        /*quando a violação for resolvida, 
        verifica se o led verde acendeu*/
        lora_rssi = LoRa.packetRssi();
        display.clearDisplay();   
        display.setCursor(0, OLED_LINE1);
        display.print("RSSI: ");
        display.println(lora_rssi);
        display.setCursor(0, OLED_LINE2);
        display.print("Ultimos dados enviados: ");
        display.setCursor(0, OLED_LINE3);
        display.println(ultimo_byte_recebido);
        display.display();
    }   
}
