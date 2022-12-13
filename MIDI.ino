// float mapfloat(long x, long in_min, long in_max, long out_min, long out_max) {
//   return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
// }
int prevDigit = -1;
void readKeypadEvents() {
  int newDigit = -1;

  for (int col = KEYPAD_Y_1; col < KEYPAD_Y_3 + 1; col++) {
    digitalWrite(KEYPAD_Y_1, LOW);
    digitalWrite(KEYPAD_Y_2, LOW);
    digitalWrite(KEYPAD_Y_3, LOW);
    digitalWrite(col, HIGH);

    if (digitalRead(KEYPAD_X_1) == HIGH) {
      newDigit = keymap[col - 3][0];
    } else if (digitalRead(KEYPAD_X_2) == HIGH) {
      newDigit = keymap[col - 3][1];
    } else if (digitalRead(KEYPAD_X_3) == HIGH) {
      newDigit = keymap[col - 3][2];
    };
    digitalWrite(col, LOW);
  }

  if (newDigit != -1 && (newDigit != prevDigit)) {
    Serial.println("Got a new digit!");
    lastDebounceTime = millis();
    Serial.println(newDigit);
    showLEDDigitStep(newDigit);
    for (int i = 0; i < MAX_STEP; i++) {
      if (digit[i] == -1) {
        digit[i] = newDigit;
        break;
      }
    }
  }
  prevDigit = newDigit;
}

// void readPotentiometers() {
//   // Serial.println();

//   // Serial.print("POT_SPEED");
//   // Serial.print(analogRead(POT_SPEED));
//   // Serial.print("POT_ENV1");
//   // Serial.print(analogRead(POT_ENV1));
//   // Serial.print("POT_ENV2");
//   // Serial.print(analogRead(POT_ENV2));
//   // Serial.print("POT_FILTER1");
//   // Serial.print(analogRead(POT_FILTER1));
//   // Serial.print("POT_FILTER2");
//   // Serial.print(analogRead(POT_FILTER2));
//   // Serial.print("POT_LFO");
//   // Serial.print(analogRead(POT_LFO));
//   // Serial.print("POT_NOTE_AMOUNT");
//   // Serial.print(analogRead(POT_NOTE_AMOUNT));
//   // Serial.print("POT_CHANNEL_LENGTH");
//   // Serial.print(analogRead(POT_CHANNEL_LENGTH));

//   // Serial.print(" 28: ");
//   // Serial.print(digitalRead(28));


//   // Serial.print(" 29: ");
//   // Serial.print(digitalRead(29));


//   // Serial.print(" 30: ");
//   // Serial.print(digitalRead(30));

//   // Serial.print(" 31: ");
//   // Serial.print(digitalRead(31));
//   // Serial.println();

//   // uClock.setTempo(map(analogRead(A10), 0, 1020, 5, 200));

//   // bassFilter.frequency(mapfloat(analogRead(A11), 0, 1020, 0, 3000));
// }

// void myControlChange(byte channel, byte control, byte value) {
//   Serial.println("MIDI: got a change: ");
//   Serial.print("channel: ");
//   Serial.print(channel);
//   Serial.print("control: ");
//   Serial.print(control);
//   Serial.print("value: ");
//   Serial.print(value);

//   lastDebounceTime = millis();

//   // Speed
//   if (control == 1) {
//     int val = map(value, 0, 127, 5, 200);
//     Serial.println("adjusting towards");
//     Serial.print(val);
//     uClock.setTempo(val);
//   }

//   // env1
//   if (control == 2) {
//     double attack = mapfloat(value, 0, 127, 0, 10);
//     double decay = mapfloat(value, 0, 127, 100, 1400);
//     double sustain = mapfloat(value, 0, 127, .2, 1);
//     double release = mapfloat(value, 0, 127, 10, 200);

//     bassEnv.attack(attack);
//     bassEnv.decay(decay);
//     bassEnv.sustain(sustain);
//     bassEnv.release(release);
//   }

//   // env2
//   if (control == 3) {
//     double attack = mapfloat(value, 0, 127, 2, 15);
//     double decay = mapfloat(value, 0, 127, 5, 1400);
//     double sustain = mapfloat(value, 0, 127, .2, 1);

//     leadEnv.attack(attack);
//     leadEnv.decay(decay);
//     leadEnv.sustain(sustain);
//   }

//   // filter 1
//   if (control == 4) {
//     double val = mapfloat(value, 0, 127, 0, 3000);
//     Serial.println("adjusting towards");
//     Serial.print(val);
//     bassFilter.frequency(val);
//   }

//   // filter 2
//   if (control == 5) {
//     double val = mapfloat(value, 0, 127, 0, 3000);
//     Serial.println("adjusting towards");
//     Serial.print(val);
//     leadFilter.frequency(val);
//   }

//   // LFO
//   if (control == 6) {
//     double val = mapfloat(value, 0, 127, 0, 1);
//     Serial.println("adjusting towards");
//     Serial.print(val);
//     dc2.amplitude(val);
//   }


//   // noteAmount
//   if (control == 7) {
//     int val = mapfloat(value, 0, 127, 0, 100);
//     Serial.println("adjusting towards");
//     Serial.print(val);

//     divideByThree(euclid_event_count, val);
//     euclid(euclid_pattern_length[0], euclid_event_count[0], 0, 0);
//     euclid(euclid_pattern_length[1], euclid_event_count[1], 1, 0);
//     euclid(euclid_pattern_length[2], euclid_event_count[2], 2, 1);
//   }

//   // channel length
//   if (control == 8) {
//     int val = mapfloat(value, 0, 127, 3, 150);
//     Serial.println("adjusting towards");
//     Serial.print(val);
//     divideByThree(euclid_pattern_length, val);
//     euclid_pattern_length_changed = true;
//   }

//   // Switches:
//   // noteOff
//   if (control == 40) {
//     endless_lead_note = value == 1 ? true : false;
//   }

//   // bass fill
//   if (control == 41) {
//     play_all_bass_notes = value == 1 ? true : false;
//   }


//   // buildup phase
//   if (control == 42) {
//     if (value == 1) {
//       NEW_PHASE = PHASE_BUILDUP;
//     } else {
//       NEW_PHASE = PHASE_BASE;
//     }
//   }

//   // harde beets
//   if (control == 43) {
//     double val = mapfloat(value, 0, 127, 0, 1);
//     Serial.println("adjusting towards");
//     Serial.print(val);
//     dc2.amplitude(val);
//   }
// }

// void sendAllMidiValues() {
//   for (unsigned i = 0; i < 30; i++) {
//     double min = configData[i][COL_MIN];
//     double max = configData[i][COL_MAX];
//     double val = configData[i][2];

//     int midiVal = map(val, min, max, 0, 127);
//     Serial.println("setting midi! i : ");
//     Serial.print(i);
//     Serial.print(" val: ");
//     Serial.print(val);
//     Serial.print(" midiVal: ");
//     Serial.println(midiVal);
//     usbMIDI.sendControlChange(i, midiVal, 2);
//   }
// }
