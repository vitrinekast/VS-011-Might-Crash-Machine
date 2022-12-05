// 2 types of lead, one arp, one slower.
// Timing for slower is based on modulo 3.

int lead_detune = 50;

void setupLead() {
  leadOsc1.begin(1, 440, WAVEFORM_SAWTOOTH);
  leadOsc2.begin(1, 440, WAVEFORM_SAWTOOTH);



  // sine2.frequency(1);
  // sine4.amplitude(.5);
  // sine4.frequency(0.01);
  leadEnv.attack(5);
  leadEnv.decay(340);
  leadEnv.sustain(.1);
  leadEnv.release(200);

  dc2.amplitude(1);

  // delay1.delay(0, 500);

  leadFilterEnv.attack(5);
  leadFilterEnv.decay(200);
  leadFilterEnv.sustain(0);
  leadFilterEnv.release(500);

  lead_is_setup = true;
}


void playLeadNote(uint32_t tick) {
  // int current_step = abs((tick - 2) / lead_modulo) % MAX_STEP;
  
  int current_step = round(tick / lead_modulo);
  bool should_play = (tick % lead_modulo) == 0;
  // Serial.println("Lead note: ");
  // Serial.print("Current step: ");
  // Serial.print(current_step);
  // Serial.print(" should play'");
  // Serial.print(should_play);

  if (should_play) {
    SEQUENCER_STEP_DATA step = all_sequences[_current_lead_seq_type][current_step];

    leadEnv.noteOn();
    leadFilterEnv.noteOn();
    leadEnv.releaseNoteOn(20);
    leadFilterEnv.releaseNoteOn(10);
    leadOsc1.frequency(getFrequency(LEAD_ROOT + step.note));
    leadOsc2.frequency(getFrequency(LEAD_ROOT + step.note - 12));
  }
}