void setupPad() {
  Serial.println("setupPad");
  padOsc1.begin(1, 440, WAVEFORM_SQUARE);
  padOsc2.begin(1, 440, WAVEFORM_SQUARE);
  padOsc3.begin(1, 440, WAVEFORM_SQUARE);
  padOsc4.begin(1, 440, WAVEFORM_PULSE);

  padEnv.attack(1000);
  padEnv.decay(600);
  padEnv.sustain(.8);
  padEnv.release(1800);

  padFilter.frequency(1000);
  padFilter.resonance(.7);

  padLFO1.amplitude(1);
  padLFO1.frequency(1);
  padLFO2.frequency(2);
  padLFO2.amplitude(1);

  padCombine.setCombineMode(AudioEffectDigitalCombine::XOR);

  padOscMix.gain(0, .5);
  padOscMix.gain(1, .5);
  padOscMix.gain(2, .5);
  padOscMix.gain(3, .5);
}

void playPadNote(uint32_t tick) {

  int current_step = (tick % 16) / 2;
  bool should_play = (tick % 2) == 0;


  SEQUENCER_STEP_DATA step = sequence[current_step];
  if (should_play) {
    // Serial.println("playPadNote");
    // over bars, do other stuf with pad.
    padOsc1.frequency(getFrequency(MIDI_ROOT + step.note));
    padOsc2.frequency(getFrequency(MIDI_ROOT + step.note + 3));
    padOsc3.frequency(getFrequency(MIDI_ROOT + step.note + 9));
    padOsc4.frequency(getFrequency(MIDI_ROOT + step.note - 12));

   
    if (current_step == 0) {
      padEnv.noteOn();
    }
  }
}
