#include <WiFi.h>
#include <WiFiClient.h> 
#include <FastLED.h>

#define LED_PIN     5
#define COLOR_ORDER RGB
#define CHIPSET     WS2813 
#define NUM_LEDS    450
#define BRIGHTNESS  40
#define FRAMES_PER_SECOND 240 

#define COOLING  55
#define SPARKING 120


CRGB leds[NUM_LEDS];
bool gReverseDirection = false; 


const char * ssid = "INFINITUM2AFC_2.4"; 
const char * password = "S5Gz8B7RHV"; 

// Puerto a utilizar para la comunicación
const int port = 8080;

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

  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

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
            FastLED.show(); 
            FastLED.delay(1000 / FRAMES_PER_SECOND);   

        } else if (mensaje == '2') {
            Serial.println("Entro al efecto Blanco"); // Verificar si se llega aquí
            whiteFill();
            FastLED.show();
            FastLED.delay(1000 / FRAMES_PER_SECOND);
        } else if (mensaje == '3') {
            Serial.println("Entro al efecto 3"); // Verificar si se llega aquí
            whiteFill2();
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

void whiteFill() {
  fill_solid(leds, NUM_LEDS, CRGB::White);
}
void whiteFill2() {
  fill_solid(leds, NUM_LEDS, CRGB::Green);
}