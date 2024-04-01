#include <FastLED.h> 

#define LED_PIN     5 
#define NUM_LEDS    300
#define CHIPSET     WS2813
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS]; 
#define BRIGHTNESS  254  

void pulseEffect() {
  int pulse1Pos = 0; 
  int pulse2Pos = NUM_LEDS - 1; 
  int pulseSpeed = 3; 
  CRGB pulse1Color = CRGB::Red;
  CRGB pulse2Color = CRGB::Blue;
  int pulseLength = 10; 
  int fadeLength = 30; 

  while (true) { 

    for (int i = pulse1Pos + pulseLength; i < min(pulse1Pos + pulseLength + fadeLength, NUM_LEDS); i++) {
      leds[i].fadeLightBy(20); 
    }
    for (int i = pulse2Pos - pulseLength - fadeLength; i < pulse2Pos - pulseLength; i++) {
      if (i >= 0) leds[i].fadeLightBy(20);
    }

    for (int i = 0; i < pulseLength; i++) {
      leds[pulse1Pos + i] = pulse1Color; 
      leds[pulse2Pos - i] = pulse2Color; 
    }

    pulse1Pos += pulseSpeed;
    pulse2Pos -= pulseSpeed;
    if (pulse1Pos + pulseLength >= pulse2Pos) {
      for (int i = pulse1Pos; i <= pulse2Pos; i++) {
        leds[i] = CRGB::White;  
      }
      FastLED.show();
      delay(50); 

      pulse1Color = CRGB::Green;
      pulse2Color = CRGB::Purple;
      pulse1Pos = NUM_LEDS / 2 - pulseLength - 5;  
      pulse2Pos = NUM_LEDS / 2 + pulseLength + 5; 
    }

    FastLED.show();
    delay(25); 
  }
}

void setup() {  
  delay( 3000 ); 
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );  
  FastLED.setBrightness( BRIGHTNESS );
  pulseEffect(); 
}

void loop() {

}
