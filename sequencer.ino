int getCurrentBar(int stepCount, uint32_t tick) {
  if (stepCount == 16) {
    return (tick / 2) / MAX_STEP;
  } else if (stepCount == 64) {
    return (tick / 1) / MAX_STEP;
  } else {
    return 0;
  }
}

double getFrequency(int note) {
  // add 1 so we can count with 0;
  // 69 = A4;

  float freq = 440.0 * powf(2.0, (float)(note - 69) * 0.08333333);
  return freq;
}


int getCurrentStep(int stepCount, uint32_t tick) {
  if (stepCount == 16) {
    return (tick / 2) % MAX_STEP;
  } else {
    return 0;
  }
}

void setBaseSequence() {


  for (int i = 0; i < MAX_STEP; i++) {
    // TODO: translate towards closest note within minor scale;
    sequence[i].rest = random(0, 100) < 20;
    sequence[i].note = SCALE_MINOR[digit[i]];
  };
}


void updateEuclidIndex() {
  bool didChange = false;

  for (int i = 0; i < NUM_SEQ_CHANNELS; i++) {
    euclid_index[i]++;
  }

  for (int i = 0; i < NUM_SEQ_CHANNELS; i++) {
    if (euclid_index[i] > euclid_pattern_length[i]) {
      euclid_index[i] = 0;
      if (euclid_pattern_length_changed) {
        euclid(euclid_pattern_length[0], euclid_event_count[0], 0, 0);
        euclid(euclid_pattern_length[1], euclid_event_count[1], 1, 0);
        euclid(euclid_pattern_length[2], euclid_event_count[2], 2, 1);
      }
      euclid_pattern_length_changed = false;
    }
  }
}

void onStep16(uint32_t tick) {
  
  playLeadNote(tick);
  updateEuclidIndex();
  // if current step = 0, calculate the sequences to be taken for all 4 instruments -> makeSequences();
  // int bar = getCurrentBar(16, tick);

  // TODO: add check regarding lengths;


  // Only generate the sequences when current step = 8 and only the first time it is 8.
  // if (tick % 2 == 0 && getCurrentStep(16, tick) == 0) {
  //   // makeSequences(bar);
  //   // parseSongState();
  //   Serial.println("at beginning of a bar");
  // }
  playPadNote(tick);
  playBassNote(tick);
  playDrumStep(tick);
}
