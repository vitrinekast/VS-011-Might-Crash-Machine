
void loopMIDI() {
}

void onControlChange(byte channel, byte control, byte value) {
  Serial.println("MIDI: got a change: ");
  Serial.print("channel: ");
  Serial.print(channel);
  Serial.print("control: ");
  Serial.print(control);
  Serial.print("value: ");
  Serial.print(value);
  // TODO: add button to print all of the current values;
  // Make this smarter and faster!;
  double min = configData[control][col_min];
  double max = configData[control][col_max];
  Serial.print("min: ");
  Serial.print(min);
  Serial.print("max: ");
  Serial.print(max);
  double mappedValue = map(value, 0, 127, min, max);

  Serial.print("mappedValue: ");
  Serial.print(mappedValue);

  configData[control][current_style] = mappedValue;
  // updateSynthValuesByConfig();

  switch (control) {
    case 0:
      Serial.println("SHOULD UPDATE SPEED");
      break;
    case 1:
      Serial.println("OPEN");
      break;
    case 2:
      Serial.println("OPEN");
      break;
    case 3:
      Serial.println("set attack to");
      bassEnv.attack(configData[row_bass_attack][current_style]);
      break;
    case 4:
      Serial.println("set decay to");
      bassEnv.decay(configData[row_bass_decay][current_style]);
      break;
    case 5:
      Serial.println("set sustain to");
      bassEnv.sustain(configData[row_bass_sustain][current_style]);
      break;
    case 6:
      Serial.println("set release to");
      bassEnv.release(configData[row_bass_release][current_style]);
      break;
    case 7:
      Serial.println("set hold to");
      bassEnv.hold(configData[row_bass_hold][current_style]);
      break;
    case 8:
      Serial.println("LFO AMP");
      break;
    case 9:
      Serial.println("LFO FREQ");
      break;
    case 10:
      Serial.println("FM AMP");
      break;
    case 11:
      Serial.println("FM FREQ");
      break;
    case 12:
      Serial.println("FILTER RES");
      bassFilter.resonance(configData[row_filter_resonance][current_style]);
      break;
    case 13:
      Serial.println("FILTER FQ");
      bassFilter.frequency(configData[row_filter_frequency][current_style]);
      break;
    case 14:
      Serial.println("FILTER OCTVCNTRL");
      break;
  }

  Serial.print(mappedValue);
}

void sendAllMidiValues() {
  for (unsigned i = 0; i < 15; i++) {
    double min = configData[i][col_min];
    double max = configData[i][col_max];
    double val = configData[i][current_style];

    int midiVal = map(val, min, max, 0, 127);

    usbMIDI.sendControlChange(i, midiVal, 2);
  }
}
