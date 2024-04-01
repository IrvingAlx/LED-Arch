#include <FastLED.h> 

#define LED_PIN     5 
#define NUM_LEDS    300
#define CHIPSET     WS2813
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS]; 
#define BRIGHTNESS  254  

void setup() {  
  delay( 3000 ); 
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );  
  FastLED.setBrightness( BRIGHTNESS );

  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.show();
}

void loop() {
}
