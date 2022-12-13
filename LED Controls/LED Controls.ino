#include <FastLED.h>
#include <Keypad.h>
// #include <Bounce2.h>

#define LED_PIN 32
#define NUM_LEDS 28

char keymap[3][3] = {
  { 7, 4, 1 },
  { 8, 5, 2 },
  { 9, 6, 3 }
};
byte rowPins[3] = { 0, 1, 2 };
byte colPins[3] = { 3, 4, 5 };


// CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  // FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(0, INPUT_PULLDOWN);
  pinMode(1, INPUT_PULLDOWN);
  pinMode(2, INPUT_PULLDOWN);
}
int delaytime = 25;

void loop() {
  // Serial.println("loopy");
  int selectedDigit = -1;

  for (int col = 3; col < 6; col++) {
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(col, HIGH);

    if (digitalRead(0) == HIGH) {
      selectedDigit = keymap[col - 3][0];
      Serial.print(selectedDigit);
      Serial.print(" bc ");
      Serial.print(col);
      Serial.print(".");
      Serial.println(0);
    } else if (digitalRead(1) == HIGH) {
      selectedDigit = keymap[col - 3][1];
      Serial.print(selectedDigit);
      Serial.print(" bc ");
      Serial.print(col);
      Serial.println(".1");
    } else if (digitalRead(2) == HIGH) {
      selectedDigit = keymap[col - 3][2];
      Serial.print(selectedDigit);
      Serial.print(" bc ");
      Serial.print(col);
      Serial.println(".2");
    };
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(50);
  }

  Serial.println(selectedDigit);
  
}