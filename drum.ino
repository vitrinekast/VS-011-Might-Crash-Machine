#define SAMPLE_KICK 0
#define SAMPLE_SNARE 1
#define SAMPLE_HH 2
#define SAMPLE_CLAP 3

void setupDrum() {
  Serial.print("Should setup drum");
}

void playDrumStep(int current_step) {
  if (DEBUG_PRINT_STEP) {
    // Serial.print("play step drum: ");
  }

  SEQUENCER_DRUM_DATA step = all_sequences_drum[_current_drum_seq_type][current_step];
  sine1.amplitude(1.0);


  // playSdWav1.play("bd01.wav");
  if (step.kick) { sound0.play(AudioSampleKick); };
  if (step.snare) { sound1.play(AudioSampleSnare); };
  if (step.hh) { sound2.play(AudioSampleHihat); };
  if (step.clap) { sound3.play(AudioSampleTomtom); };
  // if (step.clap) { playSdWav1.play("cp01.wav"); };
}