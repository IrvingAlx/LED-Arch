#include <FastLED.h>

#define LED_PIN     5
#define COLOR_ORDER RGB
#define CHIPSET     WS2813
#define NUM_LEDS    450

#define BRIGHTNESS  40
#define FRAMES_PER_SECOND 240

bool gReverseDirection = false;

CRGB leds[NUM_LEDS];

void setup() {
  delay(3000); 
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<CHIPSET, 6, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip ); 
  FastLED.addLeds<CHIPSET, 7, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip ); 

  FastLED.setBrightness( BRIGHTNESS );
}

void loop()
{

  Fire2012(); 
  
  FastLED.show(); 
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}
#define COOLING  55

#define SPARKING 120


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