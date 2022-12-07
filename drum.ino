#define SAMPLE_KICK 0
#define SAMPLE_SNARE 1
#define SAMPLE_HH 2
#define SAMPLE_CLAP 3

void setupDrum() {
  Serial.print("Should setup drum");
  drum_is_setup = true;
}

void playDrumStep(uint32_t tick) {
  if (tick % 2 == 0) {
    Serial.print("playa  drum step");
    int current_step = (abs(tick / 2) % MAX_STEP);

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
}