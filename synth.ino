double getFrequency(float root, int halfsteps) {
  // add 1 so we can count with 0;
  halfsteps += 1;
  return root * pow(halfsteps, 3 / 12.000);
}

void playBassNote(uint32_t tick) {
  SEQUENCER_STEP_DATA step = all_sequences[_current_bass_seq_type][tick % MAX_STEP];

  if (DEBUG_PRINT_STEP) {
    Serial.print("playnote: ");
    Serial.println(step.note);

    Serial.print("root: ");
    Serial.println(BASS_ROOT);
  }

  double frequency = getFrequency(BASS_ROOT, step.note);

  if (!step.glide) {
    envelope1.noteOff();
  }

  if (!step.rest) {
    envelope1.noteOn();
  }
  bassOsc1.frequency(frequency);
  bassOsc2.frequency(frequency);
  // }
};

void playPadNote() {
}

void playLeadNote() {
}

void setupBass() {
  bassOsc1.begin(0.3, 440, WAVEFORM_SINE);
  bassOsc2.begin(0.3, 440, WAVEFORM_SAWTOOTH);
}

void setupPad() {
  // padOsc1.begin(0.3, 440, WAVEFORM_SINE);
  // padOsc2.begin(0.3, 440, WAVEFORM_SINE);
}

void setupLead() {
}

void printAllSynthValues() {
  Serial.println("bass_osc_1_gain, ");
  Serial.print(bass_osc_1_gain);
  Serial.println("bass_osc_2_gain, ");
  Serial.print(bass_osc_2_gain);
  Serial.println("pad_osc_1_gain, ");
  Serial.print(pad_osc_1_gain);
  Serial.println("pad_osc_2_gain, ");
  Serial.print(pad_osc_2_gain);
  Serial.println("bass_env_attack, ");
  Serial.print(bass_env_attack);
  Serial.println("bass_env_decay, ");
  Serial.print(bass_env_decay);
  Serial.println("bass_env_sustain, ");
  Serial.print(bass_env_sustain);
  Serial.println("bass_env_release, ");
  Serial.print(bass_env_release);
  Serial.println("pad_env_attack, ");
  Serial.print(pad_env_attack);
  Serial.println("pad_env_decay, ");
  Serial.print(pad_env_decay);
  Serial.println("pad_env_sustain, ");
  Serial.print(pad_env_sustain);
  Serial.println("pad_env_release, ");
  Serial.print(pad_env_release);
  Serial.println("tempo, ");
  Serial.print(tempo);
}

void updateSynthValues() {
  Serial.println("should update all synth values based on default values now");
  Serial.print(bass_osc_1_gain);
  // double bass_osc_1_gain;
  // double bass_osc_2_gain;
  // double pad_osc_1_gain;
  // double pad_osc_2_gain;
  // double bass_env_attack;
  // double bass_env_decay;
  // double bass_env_sustain;
  // double bass_env_release;
  // double pad_env_attack;
  // double pad_env_decay;
  // double pad_env_sustain;
  // double pad_env_release;
  // double tempo;
  bassOsc1.begin(0.1, 440, WAVEFORM_SINE);
  bassOsc2.begin(0.1, 440, WAVEFORM_SAWTOOTH);

  envelope1.attack(9.2);    // 10 - 11880 ms
  envelope1.decay(31.4);    // 10 - 11880 ms
  envelope1.sustain(0.6);   // 0 - 1
  envelope1.release(84.5);  // 10 - 11880 ms
}