#define SAMPLE_KICK 0
#define SAMPLE_SNARE 1
#define SAMPLE_HH 2
#define SAMPLE_CLAP 3

void setupDrum() {
  Serial.print("Should setup drum");
}

void playDrumStep(int current_step) {
  if (DEBUG_PRINT_STEP) {
    Serial.print("play step drum: ");
  }

  SEQUENCER_DRUM_DATA step = all_sequences_drum[_current_drum_seq_type][current_step];


  if (step.kick) { playSample(SAMPLE_KICK); };
  if (step.snare) { playSample(SAMPLE_SNARE); }
  if (step.hh) { playSample(SAMPLE_HH); }
  if (step.clap) { playSample(SAMPLE_CLAP); }
}

void playSample(int type) {
}