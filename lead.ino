// 2 types of lead, one arp, one slower.
// Timing for slower is based on modulo 3.
bool leadIsArp = false;

void setupLead() {
  Serial.print("setting up the lead");
  leadOsc1.begin(.3, 440, WAVEFORM_SINE);
  leadOsc2.begin(.3, 440, WAVEFORM_SINE);

  leadEnv.attack(3);
  leadEnv.decay(220);
  leadEnv.sustain(.1);
  leadEnv.release(400);

  dc2.amplitude(1);

  // delay1.delay(0, 500);

  envelope4.attack(0);
  envelope4.decay(50);
  envelope4.sustain(0);
  envelope4.release(200);


  filter3.frequency(1200);
  filter3.resonance(1.3);

  if(leadIsArp) {
    leadEnv.decay(800);
    filter3.frequency(2700);
    filter3.resonance(5);
    
  }
  leadMixer.setCombineMode(0);
  lead_is_setup = true;
}

void setupArp() {
  leadIsArp = true;
  setupLead();
}

void playLeadNote(uint32_t tick) {
  int current_step = (tick % 16) / 2;
  bool should_play = (tick % 2) == 0;
  
  if (leadIsArp) {
    current_step = (tick % 3);
  }

  if (should_play || leadIsArp) {
    SEQUENCER_STEP_DATA step = all_sequences[_current_lead_seq_type][current_step];
    

    leadEnv.noteOn();
    envelope4.noteOn();
    // leadEnv.releaseNoteOn(20);
    // envelope4.releaseNoteOn(10);
    leadOsc1.frequency(getFrequency(MIDI_ROOT + step.note + 3 + ((getCurrentBar(64, tick)%4)*12)));
    leadOsc2.frequency(getFrequency(MIDI_ROOT + step.note + ((getCurrentBar(64, tick)%4)*12)));
  }
}