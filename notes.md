24 tm 32
13 tm 23
41 tm 33

pinMode(pushButton, INPUT);

digitalRead(pushButton);

for()



#include <FastLED.h>
	#define NUM_LEDS 28
	CRGB leds[NUM_LEDS];
	
	
	void setup() {
	  Serial.begin(9600);
	  FastLED.addLeds<NEOPIXEL, 12>(leds, NUM_LEDS);
	}
	void loop() {
	  int r = random(0, 255);
	  int g = random(0, 255);
	  int b = random(0, 255);
	  Serial.println(r);
	  for (int i = 0; i < NUM_LEDS; i++) {
		// leds[i] = CRGB::Red;
		leds[i].setRGB(r, g, b);
		leds[i].setHue( 10);
	
	
	
		FastLED.show();
		delay(i * 2);
		// leds[i] = CRGB::Black;
	  }
	
	  for (int i = NUM_LEDS; i > 0; i--) {
		leds[i] = CRGB::Black;
		FastLED.show();
		delay(i * 2);
		// leds[i] = CRGB::Black;
	  }
	}

	






const byte ROWS = 3;  //four rows
const byte COLS = 3;  //three columns
char keys[ROWS][COLS] = {
  { '7', '8', '9' },
  { '4', '5', '6' },
  { '1', '2', '3' }
};
byte rowPins[ROWS] = { 35, 36, 37 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 10, 33, 34 };  //connect to the column pinouts of the keypad
const char NO_KEY = '\0';

// Function to read the keypad matrix and return the key pressed
char getKey() {
  // Scan the rows and columns of the keypad matrix for a key press
  for (int row = 0; row < ROWS; row++) {
    // Set the current row pin to low
    digitalWrite(rowPins[row], LOW);

    // Check each column to see if a key is pressed
    for (int col = 0; col < COLS; col++) {
      if (digitalRead(colPins[col]) == LOW) {
        // Wait for the key to be released
        Serial.print("row: ");
        Serial.print(row);
        Serial.print("row pin");
        Serial.print(rowPins[row]);
        Serial.print("Col: ");
        Serial.print(col);
        Serial.print(" col pin: ");
        Serial.print(colPins[col]);
        Serial.print(" val ");
        Serial.print(keys[row][col]);
        // Reset the current row pin to high
        digitalWrite(rowPins[row], HIGH);

        // Return the key pressed
        return keys[row][col];
      }
    }

    // Reset the current row pin to high
    digitalWrite(rowPins[row], HIGH);
  }

  // Return NO_KEY if no key is pressed
  return NO_KEY;
}

void setup() {
  Serial.begin(9600);
  Serial.print("start");

  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }

  // Set the column pins as inputs with pull-ups
  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }
}

void loop() {

  char key = getKey();

  if (key != NO_KEY) {
    Serial.println(key);
  } else {
    Serial.println("nokey");
  };
}
