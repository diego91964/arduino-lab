/* Este código é utilizado para salvar a temperatura e umidade
em um cartão de memória.

Recursos utilizados:

- Arduino Mega 2560
- Sensor 3 pinos DHT11
-- '+' : 5v
-- '-' : GND
-- ' outro pino': A1 (Analógico)
- SD Card Module
-- MOSI - pin 51
-- MISO - pin 50
-- CLK  - pin 52
-- CS   - pin 53

As portas se alteram para o arduíno UNO e NANO.

Verificar: https://www.arduino.cc/en/reference/SPI
*/

#include <SD.h>
#include "DHT.h"

#define DHTPIN A1 //Definição do pino conectado
#define DHTTYPE DHT11 // DHT 11


DHT dht(DHTPIN, DHTTYPE);
const int chipSelect = 53;

void setup()
{
  Serial.begin(9600);
  Serial.print("Inicializando SD card...");
  pinMode(53, OUTPUT);

  if (!SD.begin(chipSelect)) {
    Serial.println("Inicialização falhou, cartão não está presente");
    return;
  }
  Serial.println("Cartão Inicializado.");

  dht.begin(); //Inicializa DHT (Sensor de Temperatura e Humidade)
}

void loop()
{

  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h))
  {
    Serial.println("Falha ao ler o sensor DHT");
  }
  else
  {
    // Apenas para verificar o log no serial
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.print(" %t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");

    // Montando a string para salvar no arquivo

    String dataString = "";

    dataString += "Umidade: ";
    dataString += String(h);
    dataString += "- Temperatura: ";
    dataString += String(t);
    dataString += " *C";

    // Caso dê certo, abrir o arquivo para salvar dados
    // Somente um arquivo pode ser aberto por vez
    File dataFile = SD.open("data.txt", FILE_WRITE);

    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      Serial.println(dataString);
    }else {
      Serial.println("erro ao abrir data.txt");
    }

    // Aguardando tempo (2s) para nova leitura
    delay(2000);
  }

}
