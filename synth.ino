

int bass_modulo = 16;
bool play_all_bass_notes = false;
void playBassNoteinSynth(uint32_t tick) {
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