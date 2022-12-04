double getFrequency(int note) {
  // add 1 so we can count with 0;
  // 69 = A4;
  // return pow(2.0, ((float)(note - 69) / 12.0));
  float freq = 440.0 * powf(2.0, (float)(note - 69) * 0.08333333);
  return freq;
}

void playBassNote(uint32_t tick) {
  SEQUENCER_STEP_DATA step = all_sequences[_current_bass_seq_type][tick % MAX_STEP];
  // printStepInfo(SYNTH_BASS, step);

  double frequency = getFrequency(BASS_ROOT + step.note);

  bassFilterEnv.noteOn();
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

void printStepInfo(int name, SEQUENCER_STEP_DATA step, int cur) {
  if (DEBUG_PRINT_STEP) {
    Serial.println("step: ");
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

void playPadNote(uint32_t tick) {
  SEQUENCER_STEP_DATA step = all_sequences[_current_pad_seq_type][tick % MAX_STEP];

  printStepInfo(SYNTH_PAD, step, tick % MAX_STEP);
  int note = PAD_ROOT + all_sequences[_current_pad_seq_type][0].note;

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

void playLeadNote(uint32_t tick) {
  int cur_step = floor(tick / MAX_STEP);
  SEQUENCER_STEP_DATA step = all_sequences[_current_lead_seq_type][cur_step];

  // printStepInfo(SYNTH_LEAD, step);
  leadEnv.noteOff();
  leadEnv.noteOn();

  int arp_note = all_sequences[_current_lead_seq_type][cur_step].note + ARP_MINOR[tick % 4];
  double frequency = getFrequency(LEAD_ROOT + arp_note);
  leadOsc1.frequency(frequency);
  leadOsc2.frequency(frequency);
}

void setupBass() {
  updateSynthValuesByConfig();

  bassEnv.releaseNoteOn(40);
  bassFilterEnv.releaseNoteOn(4);

  dc1.amplitude(1);

  bassOsc1.begin(1, BASS_ROOT, WAVEFORM_SAWTOOTH);
  // bassOsc2.begin(0.3, BASS_ROOT, WAVEFORM_SAWTOOTH);

  bassEnv.attack(configData[row_bass_attack][current_style]);
  bassEnv.decay(configData[row_bass_decay][current_style]);
  bassEnv.sustain(configData[row_bass_sustain][current_style]);
  bassEnv.release(configData[row_bass_release][current_style]);

  bassFilterEnv.attack(configData[row_bass_attack][current_style]/2);
  bassFilterEnv.decay(configData[row_bass_decay][current_style]/2);
  bassFilterEnv.sustain(configData[row_bass_sustain][current_style]/2);
  bassFilterEnv.release(configData[row_bass_release][current_style]/2);

  
  // bassEnv.hold(configData[row_bass_hold][current_style]);

  bassFilter.frequency(configData[row_bass_filter_frequency][current_style]);
  bassFilter.resonance(configData[row_bass_filter_resonance][current_style]);
}


void setupPad() {

  padOsc1.begin(0.3, 440, WAVEFORM_SQUARE);
  padOsc2.begin(0.3, 440, WAVEFORM_SQUARE);
  padOsc4.begin(0.3, 440, WAVEFORM_PULSE);

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
}

void setupLead() {
  leadOsc1.begin(0.3, LEAD_ROOT, WAVEFORM_SINE);
  leadOsc2.begin(0.3, LEAD_ROOT, WAVEFORM_SAWTOOTH);

  leadEnv.attack(configData[row_lead_attack][current_style]);
  leadEnv.decay(configData[row_lead_decay][current_style]);
  leadEnv.sustain(configData[row_lead_sustain][current_style]);
  leadEnv.release(configData[row_lead_release][current_style]);
  leadEnv.hold(configData[row_lead_hold][current_style]);
}

void printAllSynthValues() {
}

void updateSynthValuesByConfig() {
  Serial.println("should update all synth values based on default values now");


  // lfo.amplitude(configData[row_lfo_amp][current_style]);
  // lfo.frequency(configData[row_lfo_freq][current_style]);
}