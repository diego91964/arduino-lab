

/*
  Biblioteca SPI.h utilizada para os recursos:
  - MISO (Master In Slave Out) - A linha Slave enviando dados para o master,
  - MOSI (Master Out Slave In) - A linha Master enviando dados para os periféricos,
  - SCK (Serial Clock) - O sinal de clock que utilizado para sincronizar a transmissão com o master
*/
#include <SPI.h>

/*
  Biblioteca Gráfica utilizada para todos os display Adafruit
*/
#include <Adafruit_GFX.h>

/*
  Biblioteca Gráfica utilizada para todos os display Adafruit

  Realizar o download da biblioteca e realizar subistituições nos arquivos:

  Adafruit_PCD8544.cpp

  Onde está escrito: #include <avr/pgmspace.h>

  Substituir por:
  #ifdef ESP8266
    #include #include <pgmspace.h>
  #else
    #include <avr/pgmspace.h>
  #endif

  ---------------------------------------------

  Adafruit_PCD8544.h

  Onde está escrito:

  #if  defined(__SAM3X8E__) || defined(ARDUINO_ARCH_SAMD)
     typedef volatile RwReg PortReg;
     typedef uint32_t PortMask;
  #else
    typedef volatile uint8_t PortReg;
    typedef uint8_t PortMask;
  #endif

  Substituir por

  #if  defined(__SAM3X8E__) || defined(ARDUINO_ARCH_SAMD)
     typedef volatile RwReg PortReg;
     typedef uint32_t PortMask;
  #elif defined(ESP8266)
    typedef volatile uint32_t PortReg;
    typedef uint32_t PortMask;
  #else
    typedef volatile uint8_t PortReg;
    typedef uint8_t PortMask;
  #endif

  ---------------------------------------------

  Alem disso, as linhas de inicialização devem ser da seguinte forma:

  Adafruit_PCD8544 display = Adafruit_PCD8544(D0, D1, D2);


*/
#include <Adafruit_PCD8544.h>

/*
  Biblioteca Módulo Wifi

*/
#include <ESP8266WiFi.h>

/*

 Biblioteca Sensor de Temperatura

*/
#include "DHT.h"

//Definições de constantes
#define SSID_REDE     ""  //coloque aqui o nome da rede que se deseja conectar
#define SENHA_REDE    "" //coloque aqui a senha da rede que deseja conectar
#define INTERVALO_ENVIO_THINGSPEAK  30000  //intervalo entre envios de dados ao ThingSpeak (em ms)
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define DHTPIN 0 //D3
#define DHTTYPE DHT11 // DHT 11

//Variáveis globais
char EnderecoAPIThingSpeak[] = "api.thingspeak.com";
String ChaveEscritaThingSpeak = ""; // Coloque a chave de escrita gerada no site thingspeak.com/
long lastConnectionTime;
WiFiClient client;

/*

Portas utilizadas

Display

SCLK-------------------D5
MOSI-------------------D7
D/C--------------------D0
RST--------------------D2
SCE--------------------D1
GND--------------------GND
VCC--------------------3V3

DHT11 ----- D3
UMIDADE_SOLO ----- A0


*/

Adafruit_PCD8544 display = Adafruit_PCD8544(D0, D1, D2);
DHT dht(DHTPIN, DHTTYPE);


void EnviaInformacoesThingspeak(String StringDados);
void FazConexaoWiFi(void);


void EnviaInformacoesThingspeak(String StringDados)
{
    if (client.connect(EnderecoAPIThingSpeak, 80))
    {
        //faz a requisição HTTP ao ThingSpeak
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: "+ChaveEscritaThingSpeak+"\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(StringDados.length()); // A string deverá utilizar o formato de field1=$valor&field2=$valor
        client.print("\n\n");
        client.print(StringDados);

        lastConnectionTime = millis();
        Serial.println("- Informações enviadas ao ThingSpeak!");
     }
}

void FazConexaoWiFi(void)
{
    client.stop();
    Serial.println("Conectando-se à rede WiFi...");
    Serial.println();
    delay(1000);
    WiFi.begin(SSID_REDE, SENHA_REDE);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connectado com sucesso!");
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());

    delay(1000);
}



void setup()
{
    Serial.begin(9600);
    dht.begin();
    display.begin();

    lastConnectionTime = 0;
    FazConexaoWiFi();

    /*
      Se o contraste não for setado os valores não aparecem na tela
    */
    display.setContrast(50);

    /*
      Evita valores fantasmas na tela
    */
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(0,0);
    display.println("Conexao WIFI Realizada");
    /* Mostra informações adicionadas no buffer do display*/
    display.display();
    delay(2000);
}

//loop principal
void loop()
{
    int h = (int) dht.readHumidity();
    int t = (int) dht.readTemperature();
    int valorBrutoSensorUS = analogRead(0);   //978 -> 3,3V


    char fieldToThingSpeak[25];


    //Força desconexão ao ThingSpeak (se ainda estiver desconectado)
    if (client.connected())
    {
        client.stop();
        Serial.println("- Desconectado do ThingSpeak");
        Serial.println();
    }

    /*
      Informações utilizada para log
    */
    Serial.println("Temperatura: "+ String(t));
    Serial.println("Umidade: "+ String(h));
    Serial.println("Solo: "+ String(valorBrutoSensorUS));

    //verifica se está conectado no WiFi e se é o momento de enviar dados ao ThingSpeak
    if(!client.connected() &&
      (millis() - lastConnectionTime > INTERVALO_ENVIO_THINGSPEAK))
    {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(BLACK);
        display.setCursor(0,0);
        display.println("Umidade: " + String(h));
        display.println("Temperatura: " + String(t));
        display.println("Solo: " + String(valorBrutoSensorUS));
        display.display();
        sprintf(fieldToThingSpeak,"field1=%d&field2=%d&field3=%d",valorBrutoSensorUS,h,t);
        EnviaInformacoesThingspeak(fieldToThingSpeak);
    }

     delay(1000);
}
