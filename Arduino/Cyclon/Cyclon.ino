 
#include <FastLED.h>
 
#define NUM_LEDS 450
 
#define DATA_PIN 5
#define CLOCK_PIN 13
 
CRGB leds[NUM_LEDS];
 
void setup() { 
    Serial.begin(57600);
    Serial.println("resetting");
    FastLED.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
    FastLED.setBrightness(84);
}
 
void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }
 
void loop() { 
    static uint8_t hue = 0;
    Serial.print("x");
    for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(hue++, 255, 255);
        FastLED.show(); 
        fadeall();
        delay(10);
    }
    Serial.print("x");
 
    for(int i = (NUM_LEDS)-1; i >= 0; i--) {
        leds[i] = CHSV(hue++, 255, 255);
        FastLED.show();
        fadeall();
        delay(10);
    }
}