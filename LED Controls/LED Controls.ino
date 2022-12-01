#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    60

CRGB leds[NUM_LEDS];

void setup() {
Serial.begin(9600);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
}
int delaytime = 25;
void loop() {
  Serial.println("loop");
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 0, 0);
    FastLED.show();
    delay(i*3);  
  }

  for(int i = NUM_LEDS; i > 0; i--) {
    leds[i] = CRGB(0, 0, 0);
    FastLED.show();
    delay(delaytime);  
  }

  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 255, 0);
    FastLED.show();
    delay(delaytime);  
  }

  for(int i = NUM_LEDS; i > 0; i--) {
    leds[i] = CRGB(0, 255, 0);
    FastLED.show();
    delay(delaytime);  
  }

}