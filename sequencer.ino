void onStep16(uint32_t tick) {
  //Needed to make the 8step sequence:
  playLeadNote(tick);
  if (tick % 2 == 0) {
    return false;
  }

  tick = tick / 2;

  int current_step = tick % MAX_STEP;

  // if current step = 0, calculate the sequences to be taken for all 4 instruments -> makeSequences();
  // do the actual sequences



  if ((tick % MAX_STEP) == 0) {
    makeSequences(tick / MAX_STEP);
  }

  playBassNote(current_step);
  playPadNote(current_step);

  playDrumStep(current_step);
}

