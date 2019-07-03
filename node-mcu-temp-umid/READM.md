
  Biblioteca SPI.h utilizada para os recursos:
  - MISO (Master In Slave Out) - A linha Slave enviando dados para o master,
  - MOSI (Master Out Slave In) - A linha Master enviando dados para os periféricos,
  - SCK (Serial Clock) - O sinal de clock que utilizado para sincronizar a transmissão com o master

#include <SPI.h>


  Biblioteca Gráfica utilizada para todos os display Adafruit

#include <Adafruit_GFX.h>


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



#include <Adafruit_PCD8544.h>


  Biblioteca Módulo Wifi


#include <ESP8266WiFi.h>



 Biblioteca Sensor de Temperatura


