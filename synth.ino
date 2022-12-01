double getFrequency(float root, int halfsteps) {
  // add 1 so we can count with 0;
  halfsteps += 1;
  return root * pow(halfsteps, 3 / 12.000);

  // float freq = 440.0 * powf(2.0, (float)(note - 69) * 0.08333333);
}

void playBassNote(uint32_t tick) {
  SEQUENCER_STEP_DATA step = all_sequences[_current_bass_seq_type][tick % MAX_STEP];

  if (DEBUG_PRINT_STEP) {
    Serial.print("playnote: ");
    Serial.println(step.note);

    Serial.print("root: ");
    Serial.println(BASS_ROOT);

    Serial.print("glide: ");
    Serial.println(step.glide);

    Serial.print("rest: ");
    Serial.println(step.rest);
  }

  double frequency = getFrequency(BASS_ROOT, step.note);

  if (!step.glide) {
    bassEnv.noteOff();
  }

  if (!step.rest && !step.glide) {
    bassEnv.noteOn();
  } else if (!step.rest && !bassEnv.isActive()) {
    bassEnv.noteOn();
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
  updateSynthValuesByConfig();

  bassOsc1.begin(0.3, 440, WAVEFORM_SINE);
  bassOsc2.begin(0.3, 440, WAVEFORM_SAWTOOTH);

  bassEnv.attack(configData[row_bass_attack][current_style]);  
  bassEnv.decay(configData[row_bass_decay][current_style]);  
  bassEnv.sustain(configData[row_bass_sustain][current_style]); 
  bassEnv.release(configData[row_bass_release][current_style]);
  bassEnv.hold(configData[row_bass_hold][current_style]);

  bassFilter.frequency(configData[row_filter_frequency][current_style]);
  bassFilter.resonance(configData[row_filter_resonance][current_style]);
}


void setupPad() {
  // padOsc1.begin(0.3, 440, WAVEFORM_SINE);
  // padOsc2.begin(0.3, 440, WAVEFORM_SINE);
}

void setupLead() {
}

void printAllSynthValues() {
}

void updateSynthValuesByConfig() {
  Serial.println("should update all synth values based on default values now");


  // lfo.amplitude(configData[row_lfo_amp][current_style]);
  // lfo.frequency(configData[row_lfo_freq][current_style]);
}