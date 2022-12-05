double getFrequency(int note) {
  // add 1 so we can count with 0;
  // 69 = A4;
  // return pow(2.0, ((float)(note - 69) / 12.0));
  float freq = 440.0 * powf(2.0, (float)(note - 69) * 0.08333333);
  return freq;
}

int bass_modulo = 16;

void playBassNote(uint32_t tick) {
  int current_step = (tick % bass_modulo) / 2;
  bool should_play = (tick % 2) == 0;

  if (should_play) {

    SEQUENCER_STEP_DATA step = all_sequences[_current_bass_seq_type][current_step];
    printStepInfo(SYNTH_BASS, step, current_step);

    double frequency = getFrequency(BASS_ROOT + step.note);

    // bassFilterEnv.noteOn();
    if (!step.glide) {
      // bassEnv.noteOff();
    }

    if (!step.rest && !step.glide) {
      bassEnv.noteOn();
      bassFilterEnv.noteOn();
    } else if (!step.rest && !bassEnv.isActive()) {
      bassEnv.noteOn();
      bassFilterEnv.noteOn();
    }

    bassOsc1.frequency(frequency);
    bassOsc2.frequency(frequency);
  }

  // }
};

void printStepInfo(int name, SEQUENCER_STEP_DATA step, int cur) {
  if (DEBUG_PRINT_STEP) {
    Serial.println("");
    Serial.print("step: ");
    Serial.print(cur);
    Serial.print(" instru : ");
    Serial.print(name);
    Serial.print(": play note ");
    Serial.print(step.note);

    Serial.print(" glide: ");
    Serial.print(step.glide);

    Serial.print(" rest: ");
    Serial.println(step.rest);
  }
}

void setupBass() {
  Serial.println("setting up the bass");
  updateSynthValuesByConfig();

  bassEnv.releaseNoteOn(40);
  bassFilterEnv.releaseNoteOn(4);

  dc1.amplitude(1);

  bassOsc1.begin(1, BASS_ROOT, WAVEFORM_SINE);
  bassOsc2.begin(1, BASS_ROOT, WAVEFORM_SQUARE);

  // bassEnv.attack(configData[row_bass_attack][current_style]);
  // bassEnv.decay(configData[row_bass_decay][current_style]);
  // bassEnv.sustain(configData[row_bass_sustain][current_style]);
  // bassEnv.release(configData[row_bass_release][current_style]);

  bassEnv.attack(300);
  bassEnv.decay(3000);
  bassEnv.sustain(0.1);
  bassEnv.release(2000);

  bassFilterEnv.attack(configData[row_bass_attack][current_style] / 2);
  bassFilterEnv.decay(configData[row_bass_decay][current_style] / 2);
  bassFilterEnv.sustain(configData[row_bass_sustain][current_style] / 2);
  bassFilterEnv.release(configData[row_bass_release][current_style] / 2);


  // bassEnv.hold(configData[row_bass_hold][current_style]);

  bassFilter.frequency(configData[row_bass_filter_frequency][current_style]);
  bassFilter.resonance(configData[row_bass_filter_resonance][current_style]);

  bass_is_setup = true;
}




void printAllSynthValues() {
}

void updateSynthValuesByConfig() {
  Serial.println("should update all synth values based on default values now");


  // lfo.amplitude(configData[row_lfo_amp][current_style]);
  // lfo.frequency(configData[row_lfo_freq][current_style]);
}