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
    bassOsc2.frequency(frequency + bass_detune);
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

  bassEnv.releaseNoteOn(20);
  bassFilterEnv.releaseNoteOn(10);

  dc1.amplitude(1);

  bassOsc1.begin(.5, BASS_ROOT, WAVEFORM_PULSE);
  bassOsc2.begin(.5, BASS_ROOT, WAVEFORM_SINE);

  bassEnv.attack(3);
  bassEnv.decay(480);
  bassEnv.sustain(0.2);
  bassEnv.release(100);
  bassOsc1.phase(10);

  bassFilterEnv.attack(50);
  bassFilterEnv.decay(50);
  bassFilterEnv.sustain(.1);
  bassFilterEnv.release(50);
// 
  // combine2.setCombineMode(AudioEffectDigitalCombine::AND);

  // bassEnv.hold(configData[row_bass_hold][current_style]);

  bassFilter.frequency(600);
  bassFilter.resonance(.7);

  bass_is_setup = true;
}




void printAllSynthValues() {
}

void updateSynthValuesByConfig() {
  Serial.println("should update all synth values based on default values now");


  // lfo.amplitude(configData[row_lfo_amp][current_style]);
  // lfo.frequency(configData[row_lfo_freq][current_style]);
}