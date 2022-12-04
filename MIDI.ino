void myProgramChange(byte channel, byte program) {
  Serial.println("MIDI: got a program change: ");
  Serial.print("channel: ");
  Serial.print(channel);
  Serial.print("program: ");
  Serial.print(program);
}

void myControlChange(byte channel, byte control, byte value) {
  Serial.println("MIDI: got a change: ");
  Serial.print("channel: ");
  Serial.print(channel);
  Serial.print("control: ");
  Serial.print(control);
  Serial.print("value: ");
  Serial.print(value);
  // TODO: add button to print all of the current values;
  // Make this smarter and faster!;


  if (control == 0) {
    double min = configData[row_pad_filter_resonance][col_min];
    double max = configData[row_pad_filter_resonance][col_max];
    configData[row_pad_filter_resonance][current_style] = map(value, 0, 127, min, max);
    padFilter.resonance(configData[row_pad_filter_resonance][current_style]);

  } else if (control == 1) {
    double min = configData[row_pad_filter_frequency][col_min];
    double max = configData[row_pad_filter_frequency][col_max];

    configData[row_pad_filter_frequency][current_style] = map(value, 0, 127, min, max);
    padFilter.frequency(configData[row_pad_filter_frequency][current_style]);
  } else if (control == 2) {
    double min = configData[row_pad_attack][col_min];
    double max = configData[row_pad_attack][col_max];

    configData[row_pad_attack][current_style] = map(value, 0, 127, min, max);
    Serial.println("attack(configData[row_pad_attack][current_style]");
    Serial.print(configData[row_pad_attack][current_style]);
    padEnv.attack(configData[row_pad_attack][current_style]);
  } else if (control == 3) {
    // double min = configData[row_pad_decay][col_min];
    // double max = configData[row_pad_decay][col_max];

    // configData[row_pad_decay][current_style] = map(value, 0, 127, min, max);
    // Serial.println("decay(configData[row_pad_decay][current_style]");
    // Serial.print(configData[row_pad_decay][current_style]);
    // padEnv.decay(configData[row_pad_decay][current_style]);
    Serial.print("change sine1");
    padFilterLFO.frequency(map(value, 0, 127, 0, 50));
  } else if (control == 4) {
    Serial.print("change sine2");
    
  } else if (control == 5) {
    int val = map(value, 0, 127, 0, 5000);
    Serial.println(val);
    padEnv.attack(val);
  } else if (control == 6) {
    int val = map(value, 0, 127, 0, 5000);
    Serial.println(val);
    padEnv.decay(val);
  } else if (control == 7) {
    int val = map(value, 0, 127, 0, 2);
    Serial.println(val);
    padEnv.sustain(val);
  } else if (control == 8) {
    int val = map(value, 0, 127, 0, 5000);
    Serial.println(val);
    padEnv.release(val);
  }


  if (control == 99) {
    Serial.println("");
    Serial.println("Attack: ");
    Serial.print(configData[row_pad_attack][current_style]);
    Serial.print(" decay: ");
    Serial.print(configData[row_pad_decay][current_style]);
    Serial.print(" sustain: ");
    Serial.print(configData[row_pad_sustain][current_style]);
    Serial.print(" release: ");
    Serial.print(configData[row_pad_release][current_style]);
    Serial.print(" hold: ");
    Serial.println(configData[row_pad_hold][current_style]);
  }




  // if (control == row_bass_attack) {
  //   bassEnv.attack(configData[row_bass_attack][current_style]);
  // } else if (control == row_bass_decay) {
  //   bassEnv.decay(configData[row_bass_decay][current_style]);
  // } else if (control == row_bass_sustain) {
  //   bassEnv.sustain(configData[row_bass_sustain][current_style]);
  // } else if (control == row_bass_release) {
  //   bassEnv.release(configData[row_bass_release][current_style]);
  // } else if (control == row_bass_hold) {
  //   bassEnv.hold(configData[row_bass_hold][current_style]);
  // } else if (control == row_pad_attack) {
  //   padEnv.attack(configData[row_pad_attack][current_style]);
  // } else if (control == row_pad_decay) {
  //   padEnv.decay(configData[row_pad_decay][current_style]);
  // } else if (control == row_pad_sustain) {
  //   padEnv.sustain(configData[row_pad_sustain][current_style]);
  // } else if (control == row_pad_release) {
  //   padEnv.release(configData[row_pad_release][current_style]);
  // } else if (control == row_pad_hold) {
  //   padEnv.hold(configData[row_pad_hold][current_style]);
  // } else if (control == row_bass_filter_resonance) {
  //   bassFilter.resonance(configData[row_bass_filter_resonance][current_style]);
  // } else if (control == row_bass_filter_frequency) {
  //   bassFilter.frequency(configData[row_bass_filter_frequency][current_style]);
  // } else if (control == row_pad_filter_resonance) {
  //   padFilter.resonance(configData[row_pad_filter_resonance][current_style]);
  // } else if (control == row_pad_filter_frequency) {
  //   padFilter.frequency(configData[row_pad_filter_frequency][current_style]);
  // } else if (control == row_padOsc1Shape) {
  //   padOsc1.begin(round(configData[row_padOsc1Shape][current_style]));
  // } else if (control == row_padOsc2Shape) {
  //   padOsc2.begin(round(configData[row_padOsc2Shape][current_style]));
  // } else if (control == row_padOsc3Shape) {
  //   padOsc3.begin(round(configData[row_padOsc3Shape][current_style]));
  // } else if (control == row_padOsc4Shape) {
  //   padOsc4.begin(round(configData[row_padOsc4Shape][current_style]));
  // } else if (control == row_leadOsc1Shape) {
  //   leadOsc1.begin(round(configData[row_leadOsc1Shape][current_style]));
  // } else if (control == row_leadOsc2Shape) {
  //   leadOsc2.begin(round(configData[row_leadOsc2Shape][current_style]));
  // } else if (control == row_bassOsc1Shape) {
  //   bassOsc1.begin(round(configData[row_bassOsc1Shape][current_style]));
  // } else if (control == row_bassOsc2Shape) {
  //   bassOsc2.begin(round(configData[row_bassOsc2Shape][current_style]));
  // } else if (control == row_lead_attack) {
  //   leadEnv.attack(row_lead_attack);
  // } else if (control == row_lead_decay) {
  //   leadEnv.decay(row_lead_decay);
  // } else if (control == row_lead_sustain) {
  //   leadEnv.sustain(row_lead_sustain);
  // } else if (control == row_lead_release) {
  //   leadEnv.release(row_lead_release);
  // } else if (control == row_lead_hold) {
  //   leadEnv.hold(row_lead_hold);
  // } else {
  //   Serial.print("no control found");
  // }
}

void sendAllMidiValues() {
  for (unsigned i = 0; i < 30; i++) {
    double min = configData[i][col_min];
    double max = configData[i][col_max];
    double val = configData[i][current_style];

    int midiVal = map(val, min, max, 0, 127);
    Serial.println("setting midi! i : ");
    Serial.print(i);
    Serial.print(" val: ");
    Serial.print(val);
    Serial.print(" midiVal: ");
    Serial.println(midiVal);
    usbMIDI.sendControlChange(i, midiVal, 2);
  }
}
