CRGB leds[NUM_LEDS];

void setAllLeds(CRGB color)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = color;
  }
  FastLED.show();
}

void showLEDBit(int val, int time)
{
  leds[val] = CRGB::Blue;
  FastLED.show();
  delay(500);
  leds[val] = CRGB::Black;
  FastLED.show();
}

void setLEDUntill(int max, float delayMultiplier)
{
  for (int i = NUM_LEDS; i > (NUM_LEDS - max); i--)
  {
    leds[i] = CRGB::Blue;

    // delay((NUM_LEDS - i) * delayMultiplier);
  }
  FastLED.show();
  delay(500);

  for (int i = (NUM_LEDS - max); i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
    // delay(i * delayMultiplier);
  }
  FastLED.show();
}

void setupLeds()
{
  Serial.println("setupLeds()");
  // FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);

  // Go once past all LEDS and blink 2x when turning the device on.
  for (int i = 0; i < (NUM_LEDS + 4); i++)
  {
    if (i < NUM_LEDS)
    {
      leds[i] = CRGB::Blue;
    }
    if (i > 4)
    {
      leds[i - 4] = CRGB::Black;
    }
    FastLED.show();
    delay(floor(i));
  }

  setAllLeds(CRGB::Black);
  delay(200);
  setAllLeds(CRGB::Blue);
  delay(200);
  setAllLeds(CRGB::Black);
  delay(200);
  setAllLeds(CRGB::Blue);
  delay(200);
  setAllLeds(CRGB::Black);
}

void cleanupLeds()
{
  Serial.println("cleanupLeds()");
  // FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  setAllLeds(CRGB::Black);
}
