// 2 types of lead, one arp, one slower.
// Timing for slower is based on modulo 3.
void setupLead()
{
  Serial.print("setupLead();");
  leadOsc1.begin(.5, 440, WAVEFORM_PULSE);
  leadOsc2.begin(.5, 440, WAVEFORM_SINE);

  leadEnv.attack(3);
  leadEnv.decay(20);
  leadEnv.sustain(20);
  leadEnv.release(0);

  dc2.amplitude(0);

  envelope4.attack(0);
  envelope4.decay(20);
  envelope4.sustain(20);
  envelope4.release(0);

  leadFilter.frequency(600);
  leadFilter.resonance(4);

  leadMixer.gain(0, .4);
  leadMixer.gain(1, .4);

  //  Serial.print("setupLead();");
  // leadOsc1.begin(.5, 440, WAVEFORM_PULSE);
  // leadOsc2.begin(.5, 440, WAVEFORM_SINE);

  // leadEnv.attack(3);
  // leadEnv.decay(20);
  // leadEnv.sustain(.81);
  // leadEnv.release(200);

  // dc2.amplitude(0);

  // envelope4.attack(0);
  // envelope4.decay(20);
  // envelope4.sustain(0);
  // envelope4.release(300);

  // leadFilter.frequency(880);
  // leadFilter.resonance(2.3);

  // leadMixer.gain(0, 1);
  // leadMixer.gain(1, 1);
}

void playLeadNote(uint32_t tick)
{
  if (tick % 2 == 0)
  {

    int current_step = (tick % 16) / 2;
    bool hasNote = false;

    for (int i = 0; i < NUM_SEQ_CHANNELS; i++)
    {
      if (euclid_pattern[i][euclid_index[i]] > 0)
      {
        hasNote = true;
      }
    }

    if (!hasNote)
    {

      leadEnv.noteOff();
      envelope4.noteOff();
    }
    
    for (int i = 0; i < NUM_SEQ_CHANNELS; i++)
    {
      if (euclid_pattern[i][euclid_index[i]] > 0)
      {
        leadOsc1.frequency(getFrequency(MIDI_ROOT + digit[current_step]));
        leadOsc2.frequency(getFrequency(MIDI_ROOT + digit[current_step]));

        leadEnv.noteOn();
        envelope4.noteOn();

        leadEnv.releaseNoteOn(0);
        envelope4.releaseNoteOn(0);
        break;
      }
    }
  }
}