void printStepInfo(uint32_t tick) {
  Serial.println("");
  Serial.print("Tick: ");
  Serial.print(tick);

  Serial.print("Step");
  Serial.print(getCurrentStep(16, tick));

  Serial.print("bar");
  Serial.print((tick / 2) / MAX_STEP);
}

int getCurrentStep(int stepCount, uint32_t tick) {
  if (stepCount == 16) {
    return (tick / 2) % MAX_STEP;
  } else {
    return 0;
  }
}

int getCurrentBar(int stepCount, uint32_t tick) {
  if (stepCount == 16) {
    return (tick / 2) / MAX_STEP;
  } else if (stepCount == 64) {
    return (tick / 1) / MAX_STEP;
  } else {
    return 0;
  }
}


void onStep16(uint32_t tick) {

  // if current step = 0, calculate the sequences to be taken for all 4 instruments -> makeSequences();
  int bar = getCurrentBar(16, tick);


  if (bar == SONG_LENGTH) {
    uClock.stop();
    Serial.println("restart");
    uClock.start();

  } else {
    // Only generate the sequences when current step = 8 and only the first time it is 8.
    if (tick % 2 == 0 && getCurrentStep(16, tick) == 0) {
      makeSequences(bar);
      Serial.print(bar);
    }

    // int current_step = (tick / 2) % MAX_STEP;

    // do the actual sequences
    if (bass_is_setup) {
      playBassNote(tick);
    }
    if (pad_is_setup) {
      playPadNote(tick);
    }

    // if (drum_is_setup) {
    //   playDrumStep(tick);
    // }

    if (lead_is_setup) {
      playLeadNote(tick);
    }
  }
}
