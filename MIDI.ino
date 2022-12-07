float mapfloat(long x, long in_min, long in_max, long out_min, long out_max) {
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

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
    double val = mapfloat(value, 0, 127, 0, 500);
    Serial.println("adjusting towards");
    Serial.print(val);
    bassEnv.attack(val);
  }
  if (control == 1) {
    double val = mapfloat(value, 0, 127, 0, 5000);
    Serial.println("adjusting towards");
    Serial.print(val);
    bassEnv.decay(val);
  }
  if (control == 2) {
    double val = mapfloat(value, 0, 127, 0, 500);
    Serial.println("adjusting towards");
    Serial.print(val);
    leadEnv.attack(val);
  }
  if (control == 3) {
    double val = mapfloat(value, 0, 127, 0, 5000);
    Serial.println("adjusting towards");
    Serial.print(val);
    leadEnv.decay(val);
  }
  if (control == 4) {
    double val = mapfloat(value, 0, 127, 0, 5000);
    Serial.println("adjusting towards");
    Serial.print(val);
    leadEnv.hold(val);
  }

  // filter env amount
  if(control == 5) {
    double val = mapfloat(value, 0, 127, 0, 1);
    Serial.println("adjusting towards");
    Serial.print(val);
    dc2.amplitude(val);
  }




  // filters
  if (control == 10) {
    double val = mapfloat(value, 0, 127, 0, 5000);
    Serial.println("adjusting towards");
    Serial.print(val);
    filter3.frequency(val);
  }

  if (control == 11) {
    double val = mapfloat(value, 0, 127, 0.5, 7);
    Serial.println("adjusting towards");
    Serial.print(val);
    filter3.resonance(val);
  }



  // effects
  if(control == 20) {
    int val = map(value, 0, 127, 0, 5);
    Serial.println("adjusting towards");
    Serial.print(val);
    leadMixer.setCombineMode(val);
    // delay1.delay(0, val);
    // reverb1.reverbTime(val);
  }

  if(control == 21) {
    int val = map(value, 0, 127, 0, 8);
    Serial.println("adjusting towards");
    Serial.print(val);
    leadOsc1.begin(val);
    // delay1.delay(0, val);
    // reverb1.reverbTime(val);
  }

  if(control == 22) {
    int val = map(value, 0, 127, 0, 8);
    Serial.println("adjusting towards");
    Serial.print(val);
    leadOsc2.begin(val);
    // delay1.delay(0, val);
    // reverb1.reverbTime(val);
  }

  // detunes
  if(control == 30) {
    bass_detune = value;
    Serial.println("adjusting towards");
    Serial.print(bass_detune);
  }


  // mixers
  if(control == 50) {
    bass_detune = value;
    double val = mapfloat(value, 0, 127, 0, 1);
    Serial.println("adjusting towards");
    Serial.print(val);
    
  }
  if(control == 51) {
    bass_detune = value;
    double val = mapfloat(value, 0, 127, 0, 1);
    Serial.println("adjusting towards");
    Serial.print(val);
    
  }
}

void sendAllMidiValues() {
  for (unsigned i = 0; i < 30; i++) {
    double min = configData[i][COL_MIN];
    double max = configData[i][COL_MAX];
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
