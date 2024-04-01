#include <FastLED.h>
 
#define LED_PIN     5
 
#define NUM_LEDS    450
#define CHIPSET     WS2813
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];
 
#define BRIGHTNESS  254
 
 

#define TEMPERATURE_1 Tungsten100W
#define TEMPERATURE_2 OvercastSky
 
#define DISPLAYTIME 20
#define BLACKTIME   0
 
void loop()
{
  static uint8_t starthue = 0;
  fill_rainbow( leds + 5, NUM_LEDS - 5, --starthue, 20);
 
  uint8_t secs = (millis() / 1000) % (DISPLAYTIME * 2);
  if( secs < DISPLAYTIME) {
    FastLED.setTemperature( TEMPERATURE_1 ); 
    leds[0] = TEMPERATURE_1; 
  } else {
    FastLED.setTemperature( TEMPERATURE_2 ); 
    leds[0] = TEMPERATURE_2; 
  }
 
  if( (secs % DISPLAYTIME) < BLACKTIME) {
    memset8( leds, 0, NUM_LEDS * sizeof(CRGB));
  }
  
  FastLED.show();
  FastLED.delay(8);
}
 
void setup() {
  delay( 3000 ); 
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );
}