void setupPad() {
  Serial.println("setup paad");
  padOsc1.begin(1, 440, WAVEFORM_SQUARE);
  padOsc2.begin(1, 440, WAVEFORM_SQUARE);
  padOsc3.begin(1, 440, WAVEFORM_SQUARE);
  padOsc4.begin(1, 440, WAVEFORM_PULSE);

  padEnv.attack(configData[row_pad_attack][current_style]);
  padEnv.decay(configData[row_pad_decay][current_style]);
  padEnv.sustain(configData[row_pad_sustain][current_style]);
  padEnv.release(configData[row_pad_release][current_style]);

  padFilter.frequency(configData[row_pad_filter_frequency][current_style]);
  padFilter.resonance(configData[row_pad_filter_resonance][current_style]);

  padLFO1.amplitude(1);
  padLFO1.frequency(1);
  padLFO2.frequency(2);
  padLFO2.amplitude(1);

  padCombine.setCombineMode(AudioEffectDigitalCombine::XOR);

  padOscMix.gain(0, .5);
  padOscMix.gain(1, .5);
  padOscMix.gain(2, .5);
  padOscMix.gain(3, .5);

  pad_is_setup = true;
}

void playPadNote(uint32_t tick) {

  int current_step = (tick % 16) / 2;
  bool should_play = (tick % 2) == 0;


  SEQUENCER_STEP_DATA step = all_sequences[_current_pad_seq_type][current_step];

  int note = PAD_ROOT + all_sequences[_current_pad_seq_type][0].note;

  if (should_play) {

    Serial.print("play pad note!");

    // over bars, do other stuf with pad.
    padOsc1.frequency(getFrequency(note));
    padOsc2.frequency(getFrequency(note + 3));
    padOsc3.frequency(getFrequency(note + 9));
    padOsc4.frequency(getFrequency(note - 12));

    if (!step.glide) {
      padEnv.noteOff();
    }

    if (!step.rest && !step.glide) {
      padEnv.noteOn();
    } else if (!step.rest) {
      padEnv.noteOn();
    }
  }
}
