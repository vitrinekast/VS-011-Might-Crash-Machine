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
  drumMixer.gain(1, .2);
  drumMixer.gain(2, .2);
  drumMixer.gain(3, .2);
  drumMixer.gain(4, .2);
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
int part = 2;
int current_step = (tick/part) % 16;
int part_step = tick % 16;
bool isFirst = tick%part == 0;
Serial.print(current_step);

    if (isFirst && drum_eucl_sequence[0][current_step]> 0)
    {
      // soundKick.play(AudioSampleKick_2);
      soundSynth.frequency(20);
      soundSynth.noteOn();
    }
    if (drum_eucl_sequence[1][current_step]> 0 && random(10) > 3)
    {
      soundSnare.play(AudioSampleRim);
    }

    if (isFirst && drum_eucl_sequence[2][current_step]> 0)
    {
      soundSnare.play(AudioSampleSnare);
    }

    if (drum_eucl_sequence[3][current_step]> 0 && random(10) > 3)
    {
      soundHH.play(AudioSampleTom);
    }

    if (drum_eucl_sequence[4][current_step]> 0 && random(10) > 3)
    {
      soundClap.play(AudioSampleHh);
      drumMixer.gain(4, 10/(tick%part));
    }
  // }
// 
}