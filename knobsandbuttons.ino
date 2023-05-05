float mapfloat(long x, long in_min, long in_max, long out_min, long out_max) {
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

int prevDigit = -1;
#define POT_OFFSET 50
int speed_prev_val = -100;
int env1_prev_val = -100;
int env2_prev_val = -100;
int filter1_prev_val = -100;
int filter2_prev_val = -100;
int lfo_prev_val = -100;
int note_amount_prev_val = -100;
int channel_length_prev_val = -100;

int switch_on_off_prev_val = -1;
int switch_drum_state_prev_val = -1;
int switch_bass_state_prev_val = -1;
int switch_song_state_prev_val = -1;

void setupSwitches() {
  Serial.println("TODO: setup the switches to the pins");
  // pinMode(SWITCH_ON_OFF_PIN, INPUT_PULLUP);
  // pinMode(SWITCH_DRUM_STATE_PIN, INPUT_PULLUP);
  // pinMode(SWITCH_BASS_STATE_PIN, INPUT_PULLUP);
  // pinMode(SWITCH_SONG_STATE_PIN, INPUT_PULLUP);
}

void readSwitches() {
  
  int switch_on_off_val = digitalRead(SWITCH_ON_OFF_PIN);
  int switch_drum_state_val = digitalRead(SWITCH_DRUM_STATE_PIN);
  int switch_bass_state_val = digitalRead(SWITCH_BASS_STATE_PIN);
  int switch_song_state_val = digitalRead(SWITCH_SONG_STATE_PIN);

  if (switch_on_off_prev_val != digitalRead(SWITCH_ON_OFF_PIN)) {
    // Serial.println("update switch_on_off");
    switch_on_off_prev_val = switch_on_off_val;
  };

  if (switch_drum_state_prev_val != digitalRead(SWITCH_DRUM_STATE_PIN)) {
    // Serial.println("update_ switch_drum_state");
    switch_drum_state_prev_val = switch_drum_state_val;
    song_state = switch_on_off_val == HIGH ? SONG_STATE_INTRO : SONG_STATE_BUILDUP;
  };
  if (switch_bass_state_prev_val != digitalRead(SWITCH_BASS_STATE_PIN)) {
    // Serial.println("update switch_bass_state");
    switch_bass_state_prev_val = switch_bass_state_val;
    bass_endless = (switch_bass_state_val == HIGH ? true : false);
  };

  if (switch_song_state_prev_val != digitalRead(SWITCH_SONG_STATE_PIN)) {
    // Serial.println("update switch_song_state");
    switch_song_state_prev_val = switch_song_state_val;
    
    song_state = switch_on_off_val == HIGH ? SONG_STATE_INTRO : SONG_STATE_BUILDUP;
  };
}

void parseSongState(int song, int drum) {
  if (song == HIGH && drum == HIGH) {
    last_song_state = song_state;
    song_state = SONG_STATE_CHORUS;
  } else if (song == HIGH && drum == LOW) {
    last_song_state = song_state;
    song_state = SONG_STATE_OUTRO;
  } else if (song == LOW && drum == LOW) {
    song_state = last_song_state;
  } else if (song == LOW && drum == HIGH) {
    last_song_state = song_state;
    song_state = SONG_STATE_BUILDUP;
  }
  Serial.println(song_state);
}
void parsePots() {
  // speed_prev_val = analogRead(POT_SPEED_PIN);
  env1_prev_val = analogRead(POT_ENV1_PIN);
  env2_prev_val = analogRead(POT_ENV2_PIN);
  filter1_prev_val = analogRead(POT_FILTER1_PIN);
  filter2_prev_val = analogRead(POT_FILTER2_PIN);
  lfo_prev_val = analogRead(POT_LFO_PIN);
  note_amount_prev_val = analogRead(POT_NOTE_AMOUNT_PIN);
  channel_length_prev_val = analogRead(POT_CHANNEL_LENGTH_PIN);
  pots_parsed = true;
}
void readPotentiometers() {

  if (pots_parsed) {

    // int speed_val = analogRead(POT_SPEED_PIN);
    int env1_val = analogRead(POT_ENV1_PIN);
    int env2_val = analogRead(POT_ENV2_PIN);
    int filter1_val = analogRead(POT_FILTER1_PIN);
    int filter2_val = analogRead(POT_FILTER2_PIN);
    int lfo_val = analogRead(POT_LFO_PIN);
    int note_amount_val = analogRead(POT_NOTE_AMOUNT_PIN);
    int channel_length_val = analogRead(POT_CHANNEL_LENGTH_PIN);

    // Serial.print("speed: ");
    // Serial.print(speed_val);
    // Serial.print("env1: ");
    // Serial.print(env1_val);
    // Serial.print("env2: ");
    // Serial.print(env2_val);
    // Serial.print("filter1: ");
    // Serial.print(filter1_val);
    // Serial.print("filter2: ");
    // Serial.print(filter2_val);
    // Serial.print("lfo: ");
    // Serial.print(lfo_val);
    // Serial.print("note_amount: ");
    // Serial.print(note_amount_val);
    // Serial.print("channel_length: ");
    // Serial.print(channel_length_val);
    // Serial.println();


    // if (abs(speed_val - speed_prev_val) > POT_OFFSET) {
    //   speed_prev_val = speed_val;
    //   // Serial.println("update speed_val");
    //   uClock.setTempo(map(speed_val, 0, 1033, 50, 200));
    // }


    if (abs(env1_val - env1_prev_val) > POT_OFFSET) {
      env1_prev_val = env1_val;
      // Serial.println("update env1_val");

      double attack = mapfloat(env1_val, 0, 1033, 0, 10);
      double decay = mapfloat(env1_val, 0, 1033, 100, 1400);
      double sustain = mapfloat(env1_val, 0, 1033, .2, 1);
      double release = mapfloat(env1_val, 0, 1033, 10, 200);

      bassEnv.attack(attack);
      bassEnv.decay(decay);
      bassEnv.sustain(sustain);
      bassEnv.release(release);
    }




    if (abs(env2_val - env2_prev_val) > POT_OFFSET) {
      env2_prev_val = env2_val;
      // Serial.println("update env2_val");

      double attack = mapfloat(env2_val, 0, 1033, 2, 15);
      double decay = mapfloat(env2_val, 0, 1033, 5, 1400);
      double sustain = mapfloat(env2_val, 0, 1033, .2, 1);

      leadEnv.attack(attack);
      leadEnv.decay(decay);
      leadEnv.sustain(sustain);
    }



    if (abs(filter1_val - filter1_prev_val) > POT_OFFSET) {
      filter1_prev_val = filter1_val;
      // Serial.println("update filter1_val");
      double val = mapfloat(filter1_val, 0, 1033, 0, 3000);
      bassFilter.frequency(val);
    }


    if (abs(filter2_val - filter2_prev_val) > POT_OFFSET) {
      filter2_prev_val = filter2_val;
      // Serial.println("update filter2_val");
      double val = mapfloat(filter2_val, 0, 1033, 0, 3000);
      leadFilter.frequency(val);
    }

    if (abs(lfo_val - lfo_prev_val) > POT_OFFSET) {
      lfo_prev_val = lfo_val;
      // Serial.println("update lfo_val");
      double val = mapfloat(lfo_val, 0, 1033, 0, 1);

      dc2.amplitude(val);
    }


    if (abs(note_amount_val - note_amount_prev_val) > POT_OFFSET) {
      note_amount_prev_val = note_amount_val;
      // Serial.println("update note_amount_val");

      int val = mapfloat(note_amount_val, 0, 1033, 0, 100);

      divideByThree(euclid_event_count, val);
      euclid(euclid_pattern_length[0], euclid_event_count[0], 0, 0);
      euclid(euclid_pattern_length[1], euclid_event_count[1], 1, 0);
    }


    if (abs(channel_length_val - channel_length_prev_val) > POT_OFFSET) {
      channel_length_prev_val = channel_length_val;
      // Serial.println("update channel_length_val");

      int val = mapfloat(channel_length_val, 0, 1033, 3, 150);

      divideByThree(euclid_pattern_length, val);
      euclid_pattern_length_changed = true;
    }
  }
}

// Function to read the keypad matrix and return the key pressed
int getKey() {
  // Scan the rows and columns of the keypad matrix for a key press
  for (int row = 0; row < 3; row++) {
    // Set the current row pin to low
    digitalWrite(rowPins[row], LOW);

    // Check each column to see if a key is pressed
    for (int col = 0; col < 3; col++) {
      if (digitalRead(colPins[col]) == LOW) {
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
  return -1;
}