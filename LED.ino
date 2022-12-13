#define LED_PIN 12
#define NUM_LEDS 28

CRGB leds[NUM_LEDS];

void setupLeds() {
  Serial.println("setupLeds()");
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

  showLEDStartSong();
}

void stopAllLeds() {
  Serial.println("stopAllLeds()");
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void showLEDDigitStep(int step, int count) {
  Serial.println("showLEDDigitStep(int step)");
  stopAllLeds();
  int ledsPerStep = floor(NUM_LEDS / 9);
  int startLed = floor(ledsPerStep * step);

  int maxCount = ceil(NUM_LEDS / MAX_STEP);
  int curCountLed = floor(maxCount * count);
  for (int i = 0; i < min(curCountLed + maxCount, NUM_LEDS); i++) {
    leds[i] = CRGB::Green;
  }

  for (int i = startLed; i < startLed + ledsPerStep; i++) {
    if (i <= NUM_LEDS) {
      leds[i] = CRGB::Blue;
      Serial.println(i);
    }
  }


  FastLED.show();
  delay(200);
}

void showAllLeds() {
  Serial.println("showSeqStep(int step)");
  // stopAllLeds();
  // int ledsPerStep = floor(NUM_LEDS / count);
  // int startLed = floor(ledsPerStep * step);

  for (int i = 0; i < NUM_LEDS; i++) {

    leds[i] = CRGB::Blue;
  }

  FastLED.show();
}


void showLEDStartSong() {
  Serial.println("showLEDStartSong()");

  stopAllLeds();

  int followDistance = floor(NUM_LEDS / 3);

  for (int i = 0; i < (NUM_LEDS + followDistance); i++) {
    if (i < NUM_LEDS) {
      leds[i] = CRGB(255, 255, 10 * i);
    }
    if (i - followDistance >= 0) {
      leds[i - followDistance] = CRGB::Black;
    }
    FastLED.show();
    delay(25);
  }
}