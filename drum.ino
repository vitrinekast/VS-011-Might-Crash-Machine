#define SAMPLE_KICK 0
#define SAMPLE_SNARE 1
#define SAMPLE_HH 2
#define SAMPLE_CLAP 3

void setupDrum() {
  Serial.print("Should setup drum");
  drum_is_setup = true;
}

void playDrumStep(uint32_t tick) {
  if(tick % 2 == 0) {
  int current_step = (abs(tick / 2) % MAX_STEP);
  Serial.print("Drummerboi");
  Serial.print(current_step);
  Serial.print("tick: ");
  Serial.println(tick);

  switch (current_step) {
    case 0:
        soundSnare.play(AudioSampleKick);
        break;
    case 3:
        // soundSnare.play(AudioSampleSnare);
        break;
    case 4:
        soundSnare.play(AudioSampleKick);
        break;
    case 7:
        // soundSnare.play(AudioSampleSnare);
        break;
  }
  }

  // soundSnare.play(AudioSampleHihat);
  // if (DEBUG_PRINT_STEP) {
  //   // Serial.print("play step drum: ");
  // }

  // SEQUENCER_DRUM_DATA step = all_sequences_drum[_current_drum_seq_type][current_step];

  // playSdWav1.play("bd01.wav");
  // if (step.kick) { soundKick.play(AudioSampleKick); };
  // if (step.snare) { soundSnare.play(AudioSampleSnare); };
  // if (step.hh) { soundHH.play(AudioSampleHihat); };

  // if (step.clap) { soundClap.play(AudioSampleTomtom); };
  // if (step.clap) { playSdWav1.play("cp01.wav"); };
}