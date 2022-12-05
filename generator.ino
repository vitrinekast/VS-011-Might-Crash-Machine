

void makeSequences(int bar) {
  // calculate the sequences for each instrument based on the current bar
  // also, if effect values need to change over time, set them here
  // Serial.print("MakeSequences: generate a needed sequence for bar ");
  // Serial.println(bar);

  if (!digitIsParsed) {
    parseDigit();
    setBaseSequence();

    digitIsParsed = true;
  }

  _current_bass_seq_type = singleSongData[bar][SYNTH_BASS];
  _current_drum_seq_type = singleSongData[bar][SYNTH_DRUM];
  _current_lead_seq_type = singleSongData[bar][SYNTH_LEAD];
  _current_pad_seq_type = singleSongData[bar][SYNTH_PAD];

  Serial.print("MakeSequences: _current_pad_seq_type ");
  Serial.println(_current_pad_seq_type);

  // For each instrument, check if the sequence has been generated;
  if (!generated_sequences[_current_bass_seq_type]) {
    setSequenceByType(SYNTH_BASS, _current_bass_seq_type);
    generated_sequences[_current_bass_seq_type] = true;
  } else {
    Serial.println("i've already generated this bass sequence");
  }


  if (!generated_sequences[_current_pad_seq_type]) {
    setSequenceByType(SYNTH_PAD, _current_pad_seq_type);
    generated_sequences[_current_pad_seq_type] = true;
  } else {
    Serial.println("i've already generated this pad sequence");
    Serial.print(_current_pad_seq_type);
  }

  if (!generated_sequences[_current_lead_seq_type]) {
    setSequenceByType(SYNTH_LEAD, _current_lead_seq_type);
    generated_sequences[_current_lead_seq_type] = true;
  } else {
    Serial.println("i've already generated this lead sequence");
    Serial.print(_current_lead_seq_type);
  }

  if (!generated_sequences[_current_drum_seq_type]) {
    setDrumSequence(_current_drum_seq_type);
    generated_sequences[_current_drum_seq_type] = true;
  } else {
    Serial.println("i've already generated this drum sequence");
    Serial.print(_current_drum_seq_type);
  }
}
void setRandomRythmData(int type) {
  for (int i = 0; i < MAX_STEP; i++) {
    all_sequences[type][i].rest = random(0, 100) < 0;
    all_sequences[type][i].accent = false;
    all_sequences[type][i].glide = random(0, 100) < 0;
    all_sequences[type][i].note = 0;
  };
  all_sequences[type][0].rest = false;
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
  Serial.print(" - intrument:");
  Serial.println(instrument);

  // set the base sequence
  switch (type) {
    // Transform digits to the current scale, this is also the base sequence.
    case 24:
      // Basic pad
      for (int i = 0; i < MAX_STEP; i++) {
        all_sequences[type][i].rest = true;
        all_sequences[type][i].accent = false;
        all_sequences[type][i].glide = true;
        all_sequences[type][i].note = SCALE_MINOR[digit[0]];
      };
      all_sequences[type][0].rest = false;
      break;
    case 25:
      // Basic pad
      for (int i = 0; i < MAX_STEP; i++) {
        all_sequences[type][i].rest = true;
        all_sequences[type][i].accent = false;
        all_sequences[type][i].glide = true;
        all_sequences[type][i].note = SCALE_MINOR[digit[2]];
      };
      all_sequences[type][0].rest = false;
      break;
    case 3:
      // Basic arp
      for (int i = 0; i < MAX_STEP; i++) {
        all_sequences[type][i].rest = false;
        all_sequences[type][i].accent = false;
        all_sequences[type][i].glide = true;
        all_sequences[type][i].note = SCALE_MINOR[digit[i]];
      };
      break;
  }
  // printSequenceData(all_sequences[type]);

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

void printSequenceData(SEQUENCER_STEP_DATA *sequence) {
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
  all_sequences_drum[type][2].kick = true;
  // all_sequences_drum[type][2].snare = true;
  // all_sequences_drum[type][6].snare = true;
  all_sequences_drum[type][4].kick = true;
  all_sequences_drum[type][6].kick = true;
}

// Set the initual sound design for all 4 instruments at the beginning of a new song, based on a "Style"
void makeSoundDesign(int style) {
  Serial.print("makeSoundDesign: Set design in style ");
  Serial.println(style);

  current_style = style;
  updateSynthValuesByConfig();
}