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

  bassFilter.frequency(600);
  bassFilter.resonance(.7);
}

void playBassNote(uint32_t tick) {
  bool should_play = (tick % 2) == 0;

  if (should_play) {

    SEQUENCER_STEP_DATA step = sequence[(tick / 2) % MAX_STEP];
  Serial.print("bsss");
    double frequency = getFrequency(BASS_ROOT + step.note);
    if (!step.rest || bass_endless) {
      bassEnv.noteOn();
      bassFilterEnv.noteOn();
      
    }
    if (step.rest && !bass_endless) {
      bassEnv.noteOff();
      bassFilterEnv.noteOff();
    }
    bassOsc1.frequency(frequency);
    bassOsc2.frequency(frequency + 10);
  }

  // }
};
