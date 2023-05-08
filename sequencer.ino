int getCurrentBar(int stepCount, uint32_t tick)
{
  if (stepCount == 16)
  {
    return (tick / 2) / MAX_STEP;
  }
  else if (stepCount == 64)
  {
    return (tick / 1) / MAX_STEP;
  }
  else
  {
    return 0;
  }
}

double getFrequency(int note)
{
  // add 1 so we can count with 0;
  // 69 = A4;

  float freq = 440.0 * powf(2.0, (float)(note - 69) * 0.08333333);
  return freq;
}

int getCurrentStep(int stepCount, uint32_t tick)
{
  if (stepCount == 16)
  {
    return (tick / 2) % MAX_STEP;
  }
  else
  {
    return 0;
  }
}

void setBaseSequence()
{

  for (int i = 0; i < MAX_STEP; i++)
  {
    // TODO: translate towards closest note within minor scale;
    sequence[i].rest = random(0, 100) < 60;
    sequence[i].note = SCALE_MINOR[digit[i]];
  };
}

void updateEuclidIndex()
{
  // bool didChange = false;

  for (int i = 0; i < NUM_SEQ_CHANNELS; i++)
  {
    euclid_index[i]++;
  }

  for (int i = 0; i < NUM_SEQ_CHANNELS; i++)
  {
    if (euclid_index[i] > euclid_pattern_length[i])
    {
      euclid_index[i] = 0;
      if (euclid_pattern_length_changed)
      {
        euclid(euclid_pattern_length[0], euclid_event_count[0], 0, 0);
        euclid(euclid_pattern_length[1], euclid_event_count[1], 1, 0);
        
      }
      euclid_pattern_length_changed = false;
    }
  }
}

void updateSongState(int state)
{
  Serial.println("phase: ");
  Serial.print(state);
  song_state = state;
  Serial.println("song state is now");
  Serial.print(song_state);

  euclid_pattern_length_changed = true;
  setDrumEuclid();
  switch (state)
  {
  case SONG_STATE_BUILDUP:
    euclid_pattern_length[0] = 2;
    euclid_pattern_length[1] = 3;

    euclid_event_count[0] = 1;
    euclid_event_count[1] = 1;

    break;
  case SONG_STATE_INTRO:
    euclid_event_count[0] = 0;
    euclid_event_count[1] = 0;

    break;
  case SONG_STATE_CHORUS:
    euclid_pattern_length[0] = 8;
    euclid_pattern_length[1] = 8;

    euclid_event_count[0] = 3;
    euclid_event_count[1] = 2;

    break;
  default:
    euclid_pattern_length[0] = 22;
    euclid_pattern_length[1] = 16;

    euclid_event_count[0] = 2;
    euclid_event_count[1] = 1;

    break;
  }
}

void checkSongState(int bar)
{
  Serial.print("============current song state: ");
  Serial.print(song_state);
  Serial.println();
  if (song_state == SONG_STATE_INTRO && bar == 8)
  {
    updateSongState(SONG_STATE_BUILDUP);
  }
  else if (song_state == SONG_STATE_BUILDUP && bar == 12)
  {
    updateSongState(SONG_STATE_CHORUS);
  }
  else if (song_state == SONG_STATE_CHORUS && bar == 28)
  {
    updateSongState(SONG_STATE_BETWEEN);
  }
  else if (song_state == SONG_STATE_BETWEEN && bar == 60)
  {
    updateSongState(SONG_STATE_BUILDUP);
  }
  else if (song_state == SONG_STATE_BUILDUP && bar == 64)
  {
    updateSongState(SONG_STATE_CHORUS);
  }
  else if (song_state == SONG_STATE_CHORUS && bar == 80)
  {
    updateSongState(SONG_STATE_OUTRO);
  }
  else if (song_state == SONG_STATE_OUTRO && bar > 88)
  {
    Serial.println("stop the song!");
    song_state = -1;
  }
}

void onStep(uint32_t tick)
{

  // playLeadNote(tick);
  updateEuclidIndex();
  // if current step = 0, calculate the sequences to be taken for all 4 instruments -> makeSequences();

  int step = tick % (MAX_STEP * 2);
  if (step == 0)
  {
    checkSongState(getCurrentBar(16, tick));
  }
  // TODO: add check regarding lengths;

  // Only generate the sequences when current step = 8 and only the first time it is 8.
  // if (tick % 2 == 0 && getCurrentStep(16, tick) == 0) {
  //   // makeSequences(bar);
  //   // parseSongState();
  //   Serial.println("at beginning of a bar");
  // }
  // playPadNote(tick);
  playBassNote(tick);
  playDrumStep(tick);
}