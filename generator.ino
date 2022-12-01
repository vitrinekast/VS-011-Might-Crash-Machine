// Place these from the spreadsheet https://docs.google.com/spreadsheets/d/1liqxYe1Ht9p84bwuuuADFOiAZGA8TLUPVn47AF2BULI/edit#gid=1079230721
double configData[2][4] = { { 0.5, 1, 1, 1 }, { 0.7, 1, 1, 1 } };
int current_style = 0;

int singleSongData[56][5] = { { 1,4,0,24 },{ 1,4,0,24 },{ 1,4,0,24 },{ 1,5,0,24 },{ 1,5,19,24 },{ 1,5,20,24 },{ 1,5,20,24 },{ 1,5,21,24 },{ 1,6,22,24 },{ 1,6,22,24 },{ 1,6,22,24 },{ 1,6,22,24 },{ 1,6,22,24 },{ 1,6,22,24 },{ 1,6,22,24 },{ 1,6,22,25 },{ 1,7,22,26 },{ 1,7,22,26 },{ 1,7,22,26 },{ 1,7,22,26 },{ 1,7,22,26 },{ 1,7,22,26 },{ 1,7,22,26 },{ 12,8,26 },{ 1,7,22,26 },{ 1,7,22,26 },{ 1,7,22,26 },{ 1,7,22,26 },{ 1,7,22,26 },{ 1,7,22,26 },{ 1,7,22,26 },{ 1,7,22,26 },{ 1,7,22,26 },{ 1,7,22,26 },{ 1,7,22,26 },{ 14,4 },{ 14,4 },{ 14,4 },{ 14,4 },{ 1,9,23,27 },{ 1,9,23,27 },{ 1,9,23,27 },{ 1,9,23,27 },{ 1,9,23,27 },{ 1,9,23,27 },{ 1,9,23,27 } };
// [bar, instrument]

void makeSequences(int bar) {
  // calculate the sequences for each instrument based on the current bar
  // also, if effect values need to change over time, set them here
  Serial.print("MakeSequences: generate a needed sequence for bar ");
  Serial.println(bar);

  if (!digitIsParsed) {
    parseDigit();
    setBaseSequence();

    digitIsParsed = true;
  }

  _current_bass_seq_type = singleSongData[bar][SYNTH_BASS];
  _current_pad_seq_type = singleSongData[bar][SYNTH_PAD];
  _current_drum_seq_type = singleSongData[bar][SYNTH_DRUM];
  _current_lead_seq_type = singleSongData[bar][SYNTH_LEAD];

  // For each instrument, check if the sequence has been generated;
  if (!generated_sequences[_current_bass_seq_type]) {
    setSequenceByType(SYNTH_BASS, _current_bass_seq_type);
    generated_sequences[_current_bass_seq_type] = true;
  } else {
    Serial.println("i've already generated this sequence");
  }
  // if (!generated_sequences[_current_pad_seq_type]) {
  //   setSequenceByType(SYNTH_PAD, _current_pad_seq_type);
  // }
  // if (!generated_sequences[_current_drum_seq_type]) {
  //   setDrumSequence(_current_drum_seq_type);
  // }
  // if (!generated_sequences[_current_lead_seq_type]) {
  //   setSequenceByType(SYNTH_LEAD, _current_lead_seq_type);
  // }
  
}
void setRandomRythmData(int type) {
  for (int i = 0; i < MAX_STEP; i++) {
    all_sequences[type][i].rest = random(0,100) < 20;
    all_sequences[type][i].accent = false;
    all_sequences[type][i].glide = random(0,100) < 60;
    all_sequences[type][i].note = 0;
  };
}

void parseDigit() {
  // TODO: make sure digit is 8 steps!;
  int maxVal = 0;
  int minVal = 100;

  for (unsigned i = 0; i < (sizeof(digit) / sizeof(digit[0])); i++) {
    maxVal = max(digit[i], maxVal);
    minVal = min(digit[i], minVal);
  }

  if (minVal > 0) {
    for (unsigned i = 0; i < (sizeof(digit) / sizeof(digit[0])); i++) {
      digit[i] -= minVal;
    }
  }
}

void setBaseSequence() {
  // Also same as type 1.
  // TODO: decide on root note and scale based on song selection..

  setRandomRythmData(1);
  for (int i = 0; i < MAX_STEP; i++) {
    all_sequences[1][i].note = SCALE_MINOR[digit[i]];
  };
}

void setSequenceByType(int instrument, int type) {
  

  Serial.print("setSequenceByType: ");
  Serial.print(type);
  Serial.print(" - ");
  Serial.println(instrument);



  // set the base sequence
  switch (type) {
    // Transform digits to the current scale, this is also the base sequence.
    case 1:
      // this has been set, no need to do anything.
      break;
  }
  printSequenceData(all_sequences[type]);

  // switch (type) {
  //   case 5:
  //     setEffectChanges("tempo", 5, 5);
  // }
}
// double allEffects[];

void setEffectChanges(char variable, int target_bar, double newValue) {
  // allEffects[variable + "_new"] = newValue;
}

void processEffectChanges() {
}


void printSequenceData(SEQUENCER_STEP_DATA* sequence) {
  Serial.println("Printing sequence data");

  for (int i = 0; i < MAX_STEP; i++) {
    Serial.print("step ");
    Serial.print(i);
    Serial.print(" rest ");
    Serial.print(sequence[i].rest);
    Serial.print(" accent ");
    Serial.print(sequence[i].accent);
    Serial.print(" glide ");
    Serial.print(sequence[i].glide);
    Serial.print(" note ");
    Serial.println(sequence[i].note);
  }
}

void setDrumSequence(int type) {
  // Set a drum sequence;
  Serial.println("setDrumSequence: Should generate it in a unique way. Now just boring");

  for (int i = 0; i < MAX_STEP; i++) {
    all_sequences_drum[type][i].kick = false;
  }

  all_sequences_drum[type][0].kick = true;
  all_sequences_drum[type][3].kick = true;
}


// Set the initual sound design for all 4 instruments at the beginning of a new song, based on a "Style"
void makeSoundDesign(int style) {
  Serial.print("makeSoundDesign: Set design in style ");
  Serial.println(style);

  current_style = style;

  // get all these values from the spreadsheet;
  bass_osc_1_gain = configData[current_style][0];
  bass_osc_2_gain = configData[current_style][0];
  pad_osc_1_gain = configData[current_style][0];
  pad_osc_2_gain = configData[current_style][0];
  bass_env_attack = configData[current_style][0];
  bass_env_decay = configData[current_style][0];
  bass_env_sustain = configData[current_style][0];
  bass_env_release = configData[current_style][0];
  pad_env_attack = configData[current_style][0];
  pad_env_decay = configData[current_style][0];
  pad_env_sustain = configData[current_style][0];
  pad_env_release = configData[current_style][0];
  tempo = configData[current_style][0];

  updateSynthValues();
}