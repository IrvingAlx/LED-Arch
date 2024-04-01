#include <WiFi.h>
#include <WiFiClient.h> // Incluir para la comunicación con el cliente
#include <FastLED.h>

#define LED_PIN     5
#define COLOR_ORDER RGB
#define CHIPSET     WS2813 
#define NUM_LEDS    450
#define BRIGHTNESS  255
#define FRAMES_PER_SECOND 240 

#define COOLING  55
#define SPARKING 120

#define DISPLAYTIME 20  // Segundos de cada temperatura
#define BLACKTIME   3   // Segundos de fundido a negro

#define TEMPERATURE_1 Tungsten40W 
#define TEMPERATURE_2 OvercastSky 


CRGB leds[NUM_LEDS];
bool gReverseDirection = false; 


const char * ssid = "INFINITUM2AFC_2.4"; 
const char * password = "S5Gz8B7RHV"; 

// Puerto a utilizar para la comunicación
const int port = 8081;

// Crear una instancia del servidor WiFi
WiFiServer server(port);

void setup() {
  Serial.begin(115200);
  delay(10);

  // Conectarse a la red WiFi
  Serial.println();
  Serial.println("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Dirección IP:");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Servidor iniciado");
}

void loop() {
  // Comprobar si hay un cliente conectado
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Cliente conectado");

    // Recibir el mensaje del cliente
    while (client.connected()) {
      if (client.available()) { 
        char mensaje = client.read(); // Leer un carácter a la vez
        Serial.println(mensaje); 

        // Ejecutar efectos basados en el mensaje:
        if (mensaje == '1') {
            Serial.println("Entro al efecto Fire2012"); // Verificar si se llega aquí
            Fire2012();  
            FastLED.show(); 
            FastLED.delay(1000 / FRAMES_PER_SECOND);   
        } else if (mensaje == '2') {
            loopRainbow(); 
            FastLED.show(); 
            FastLED.delay(1000 / FRAMES_PER_SECOND);
        } else if (mensaje == '3') {
            colorTemperature(); 
            FastLED.show(); 
            FastLED.delay(1000 / FRAMES_PER_SECOND);
        }
      }
    }

    // Desconectarse del cliente
    client.stop();
    Serial.println("Cliente desconectado");
  }
}




void Fire2012()
{
  static uint8_t heat[NUM_LEDS];

    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    for( int j = 0; j < NUM_LEDS; j++) {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
}

void loopRainbow() {
  static uint8_t hue = 0;
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show(); 
    fadeall();
    delay(10);
  }
  for(int i = (NUM_LEDS)-1; i >= 0; i--) {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show(); 
    fadeall();
    delay(10);
  }
}

void colorTemperature() {
  static uint8_t secs = 0;
  // Elegir el perfil de temperatura
  if( secs % (DISPLAYTIME * 2) < DISPLAYTIME) {
    FastLED.setTemperature( TEMPERATURE_1 ); // Primera temperatura
    leds[0] = TEMPERATURE_1; // Indicador
  } else {
    FastLED.setTemperature( TEMPERATURE_2 ); // Segunda temperatura
    leds[0] = TEMPERATURE_2; // Indicador
  }
  // Mostrar color negro entre cambios
  if( (secs % DISPLAYTIME) < BLACKTIME) {
    memset8( leds, 0, NUM_LEDS * sizeof(CRGB));
  }
  FastLED.show();
  FastLED.delay(8);
  secs++;
}

void fadeall() { 
    for(int i = 0; i < NUM_LEDS; i++) { 
       leds[i].nscale8(250); 
    } 
}

