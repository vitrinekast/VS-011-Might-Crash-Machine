#define SAMPLE_KICK 0
#define SAMPLE_SNARE 1
#define SAMPLE_HH 2
#define SAMPLE_CLAP 3

// #include "909/AudioSampleHandclp2.h"
// #include "909/AudioSampleHh_open.h"
// #include "909/AudioSampleHh.h"
// #include "909/AudioSampleHhspecial.h"
// #include "909/AudioSampleKick_1.h"
// #include "909/AudioSampleKick_2.h"
// #include "909/AudioSampleKick_3.h"
// #include "909/AudioSampleRim.h"
// #include "909/AudioSampleSnare.h"
// #include "909/AudioSampleTom.h"

void setupDrum() {
  Serial.print("Should setup drum");
  drumMixer.gain(3, .8);
}

void playDrumStep(uint32_t tick) {


  if (tick % 2 == 0) {
    int current_step = (abs(tick / 2) % MAX_STEP);

    // if (song_state == SONG_STATE_BUILDUP) {
    //   soundSnare.play(AudioSampleSnare);
    // }
    // if (song_state == SONG_STATE_INTRO) {

    switch (current_step) {
      case 0:
        soundKick.play(AudioSampleKick_2);
        break;
      case 2:
        soundKick.play(AudioSampleKick_2);
        break;
      case 3:
        soundSnare.play(AudioSampleSnare);
        soundSnare.play(AudioSampleHh);
        break;
      case 4:
        soundKick.play(AudioSampleKick_2);
        soundSnare.play(AudioSampleSnare);
        break;
      case 6:
        soundKick.play(AudioSampleKick_2);
        soundSnare.play(AudioSampleHh);
        break;
      case 7:
        soundSnare.play(AudioSampleHh);
        break;
        // }
    }
  }
}