#define SAMPLE_KICK 0
#define SAMPLE_SNARE 1
#define SAMPLE_HH 2
#define SAMPLE_CLAP 3

int seq_kick[SONG_STATE_OUTRO + 1][8] = {
    {0, 0, 0, 0, 4, 0, 0, 0},
    {9, 0, 5, 0, 9, 0, 5, 0},
    {9, 0, 9, 0, 9, 0, 9, 0},
    {9, 0, 9, 0, 9, 0, 9, 0},
    {0, 0, 0, 0, 4, 0, 0, 0},
};

int seq_snare[SONG_STATE_OUTRO + 1][8] = {
    {0, 0, 5, 0, 9, 0, 5, 0},
    {9, 9, 9, 9, 9, 9, 9, 9},
    {0, 9, 0, 7, 0, 5, 0, 6},
    {0, 0, 9, 0, 0, 0, 9, 0},
    {9, 0, 5, 0, 9, 0, 5, 0}};

int seq_hh[SONG_STATE_OUTRO + 1][8] = {
    {0, 4, 0, 4, 0, 4, 4, 4},
    {0, 9, 0, 4, 0, 9, 0, 4},
    {8, 8, 8, 8, 8, 8, 8, 8},
    {0, 9, 0, 4, 0, 9, 0, 4},
    {0, 4, 0, 4, 0, 4, 4, 4},
};

void setupDrum()
{
  Serial.print("setupDrum()");
  drumMixer.gain(3, .8);
}

bool playByChance(int chance)
{

  if (chance != 0)
  {
    if (random(9) < chance)
    {

      return true;
    }
  }

  return false;
}

void playDrumStep(uint32_t tick)
{

  if (tick % 2 == 0) {
  int current_step = ((tick/2) % (MAX_STEP));

    if (playByChance(seq_kick[song_state][current_step]))
    {
      soundKick.play(AudioSampleKick_2);
    }

    if (playByChance(seq_snare[song_state][current_step]))
    {
      soundSnare.play(AudioSampleSnare);
    }

    if (playByChance(seq_hh[song_state][current_step]))
    {
      soundSnare.play(AudioSampleHh);
    }
  }
}