double getFrequency(int note) {
  // add 1 so we can count with 0;
  // 69 = A4;
  // return pow(2.0, ((float)(note - 69) / 12.0));
  float freq = 440.0 * powf(2.0, (float)(note - 69) * 0.08333333);
  return freq;
}

int bass_modulo = 16;

void playBassNote(uint32_t tick) {
  bool should_play = (tick % 2) == 0;

  if (should_play) {

    SEQUENCER_STEP_DATA step = sequence[(tick / 2) % MAX_STEP];
    // printStepInfo(SYNTH_BASS, step, current_step);

    double frequency = getFrequency(BASS_ROOT + step.note);
    if (!step.rest || play_all_bass_notes) {
      bassEnv.noteOn();
      bassFilterEnv.noteOn();
    }
    if (step.rest && !play_all_bass_notes) {
      bassEnv.noteOff();
      bassFilterEnv.noteOff();
    }
    bassOsc1.frequency(frequency);
    bassOsc2.frequency(frequency + 10);
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
  bassEnv.releaseNoteOn(0);
  bassFilterEnv.releaseNoteOn(0);

  dc1.amplitude(1);

  bassOsc1.begin(.5, BASS_ROOT, WAVEFORM_PULSE);
  bassOsc2.begin(.5, BASS_ROOT, WAVEFORM_SINE);

  bassEnv.attack(3);
  bassEnv.decay(480);
  bassEnv.sustain(0.2);
  bassEnv.release(100);
  bassOsc1.phase(40);

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