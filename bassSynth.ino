void setupBass()
{
  Serial.println("Setup: Bass");
  bassEnv.releaseNoteOn(0);
  bassFilterEnv.releaseNoteOn(0);

  bassMixer.gain(0, 1);
  bassMixer.gain(1, 1);

  dc1.amplitude(1);

  bassOsc1.begin(.8, BASS_ROOT, WAVEFORM_SAWTOOTH);
  bassOsc2.begin(.8, BASS_ROOT + 220, WAVEFORM_SINE);

  bassEnv.attack(3);
  bassEnv.decay(480);
  bassEnv.sustain(0.8);
  bassEnv.release(400);
  bassOsc1.phase(40);

  bassFilterEnv.attack(50);
  bassFilterEnv.decay(150);
  bassFilterEnv.sustain(.4);
  bassFilterEnv.release(599);

  // bassFilter.frequency(380);
  // bassFilter.resonance(.4);
}

void playSingleBassNote(int note)
{
  bassEnv.noteOn();
  bassFilterEnv.noteOn();
  double frequency = getFrequency(BASS_ROOT + note);
  bassOsc1.frequency(frequency);
  bassOsc2.frequency(frequency + 10);
}

// int seq_kick[SONG_STATE_OUTRO + 1][8] = {
//   {10, 0, 5, 0, 10, 0, 5, 0},
//   {10, 0, 5, 0, 10, 0, 5, 0},
//   {10, 0, 5, 0, 10, 0, 5, 0},
//   {10, 0, 5, 0, 10, 0, 5, 0},
//   {10, 0, 5, 0, 10, 0, 5, 0}
// };

// int seq_snare[SONG_STATE_OUTRO + 1][8] = {
//   {10, 0, 5, 0, 10, 0, 5, 0},
//   {10, 0, 5, 0, 10, 0, 5, 0},
//   {10, 0, 5, 0, 10, 0, 5, 0},
//   {10, 0, 5, 0, 10, 0, 5, 0},
//   {10, 0, 5, 0, 10, 0, 5, 0}
// };

// int seq_hh[SONG_STATE_OUTRO + 1][8] = {
//   {10, 0, 5, 0, 10, 0, 5, 0},
//   {10, 0, 5, 0, 10, 0, 5, 0},
//   {10, 0, 5, 0, 10, 0, 5, 0},
//   {10, 0, 5, 0, 10, 0, 5, 0},
//   {10, 0, 5, 0, 10, 0, 5, 0}
// };
void playBassNote(uint32_t tick)
{
  if ((tick % 2) == 0)
  {

    SEQUENCER_STEP_DATA step = sequence[(tick / 2) % MAX_STEP];
    // Serial.println("playBassNote");
    double frequency = getFrequency(BASS_ROOT + step.note);
    if (!step.rest || bass_endless)
    {
      bassEnv.noteOn();
      bassFilterEnv.noteOn();
    }
    if (step.rest && !bass_endless)
    {
      bassEnv.noteOff();
      bassFilterEnv.noteOff();
    }
    bassOsc1.frequency(frequency);
    bassOsc2.frequency(frequency*2);
  }

  // }
};
