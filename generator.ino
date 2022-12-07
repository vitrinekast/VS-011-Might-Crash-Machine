void parseParamChanges() {
  if (_current_lead_seq_type == 13) {
    lead_modulo = 1;
  } else {
    lead_modulo = 6;
  }
}


void makeSequences(int bar) {
  // calculate the sequences for each instrument based on the current bar
  // also, if effect values need to change over time, set them here

  if (!digitIsParsed) {
    parseDigit();
    setBaseSequence();

    digitIsParsed = true;
  }

  _current_bass_seq_type = singleSongData[bar][SYNTH_BASS];
  _current_drum_seq_type = singleSongData[bar][SYNTH_DRUM];
  _current_lead_seq_type = singleSongData[bar][SYNTH_LEAD];
  _current_pad_seq_type = singleSongData[bar][SYNTH_PAD];

  parseParamChanges();



  // For each instrument, check if the sequence has been generated;
  if (!generated_sequences[_current_bass_seq_type]) {
    setSequenceByType(SYNTH_BASS, _current_bass_seq_type);
    generated_sequences[_current_bass_seq_type] = true;
  }
  if (!generated_sequences[_current_pad_seq_type]) {
    setSequenceByType(SYNTH_PAD, _current_pad_seq_type);
    generated_sequences[_current_pad_seq_type] = true;
  }
  if (!generated_sequences[_current_lead_seq_type]) {
    setSequenceByType(SYNTH_LEAD, _current_lead_seq_type);
    generated_sequences[_current_lead_seq_type] = true;
  }
  if (!generated_sequences[_current_drum_seq_type]) {
    setDrumSequence(_current_drum_seq_type);
    generated_sequences[_current_drum_seq_type] = true;
  }

  // Serial.println("I've created the following sequences:");
  // for (int i = 0; i < MAX_SEQUENCE_TYPES; i++) {
  //   if (generated_sequences[i]) {
  //     Serial.println(i);
  //   }
  // }
}


void setRandomRythmData(int type) {
  for (int i = 0; i < MAX_STEP; i++) {
    all_sequences[type][i].rest = random(0, 100) < 0;
    all_sequences[type][i].accent = false;
    all_sequences[type][i].glide = random(0, 100) < 0;
    all_sequences[type][i].note = 0;
    all_sequences[type][i].root = MIDI_ROOT;
  };
  all_sequences[type][0].rest = false;
}



void parseDigit() {
  Serial.println("Parse the digit");
  // TODO: make sure digit is 8 steps!;
  digit_lowest = 0;
  digit_highest = 100;

  for (unsigned i = 0; i < (sizeof(digit) / sizeof(digit[0])); i++) {
    digit_highest = max(digit[i], digit_highest);
    digit_lowest = min(digit[i], digit_lowest);
  }

  if (digit_lowest > 0) {
    for (unsigned i = 0; i < (sizeof(digit) / sizeof(digit[0])); i++) {
      digit[i] -= digit_lowest;
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

void copySequence(int originalIndex, int targetIndex) {
  for (int i = 0; i < MAX_STEP; i++) {
    all_sequences[originalIndex][i] = all_sequences[targetIndex][i];
  }
}

void setSequenceByType(int instrument, int type) {

  Serial.print("setSequenceByType: ");
  Serial.print(type);
  Serial.print(" - intrument:");
  Serial.print(instrument);

  // set the base sequence
  switch (type) {
    case 0:
      Serial.println("This sequence is empty - do not play anything");
      for (int i = 0; i < MAX_STEP; i++) {
        all_sequences[type][i].rest = true;
      }
      break;
    case 1:
      Serial.println("This is the bass base sequence");
      break;

    case 2:
      Serial.println("1 iets lower");
      copySequence(type, 1);
      for (int i = 0; i < MAX_STEP; i++) {
        Serial.print(all_sequences[type][i].note);
        Serial.print(" - ");
        all_sequences[type][i].note -= ARP_MINOR[1];
        Serial.println(all_sequences[type][i].note);
      }
      break;
    case 3:
      Serial.println("1 nog ets lower");
      copySequence(type, 1);
      for (int i = 0; i < MAX_STEP; i++) {
        all_sequences[type][i].note -= ARP_MINOR[2];
      }
      break;
    case 4:
      Serial.println("1 iets omhoog");
      copySequence(type, 1);
      for (int i = 0; i < MAX_STEP; i++) {
        all_sequences[type][i].note += (12 - ARP_MINOR[2]);
      }
      break;

    case 20:
      Serial.println("Copy bass sequence but then a bit higer");
      copySequence(type, 1);
      for (int i = 0; i < MAX_STEP; i++) {
        all_sequences[type][i].note += 24;
      }
      break;
    case 22:
      Serial.println("Copy bass sequence but then a bit higer");
      copySequence(type, 1);
      for (int i = 0; i < MAX_STEP; i++) {
        all_sequences[type][i].note += (24 - ARP_MINOR[1]);
      }
      break;
    case 23:
      Serial.println("Copy bass sequence but then a bit higer");
      copySequence(type, 1);
      for (int i = 0; i < MAX_STEP; i++) {
        all_sequences[type][i].note += (24 - ARP_MINOR[2]);
      }
      break;
    case 24:
      Serial.println("Copy bass sequence but then a bit higer");
      copySequence(type, 1);
      for (int i = 0; i < MAX_STEP; i++) {
        all_sequences[type][i].note += (24 - ARP_MINOR[2]);
      }
      break;
    case 30:
      Serial.println("Create simple arp");
      for (int i = 0; i < MAX_STEP; i++) {
        all_sequences[type][i].rest = false;
        all_sequences[type][i].accent = false;
        all_sequences[type][i].glide = false;
        all_sequences[type][i].note = SCALE_MINOR[digit[i]] + 24 - 3;
      };
      break;
    case 32:
      Serial.println("Create simple arp");
      for (int i = 0; i < MAX_STEP; i++) {
        all_sequences[type][i].rest = false;
        all_sequences[type][i].accent = false;
        all_sequences[type][i].glide = false;
        all_sequences[type][i].note = SCALE_MINOR[digit[i]] + 24 - 7;
      };
      break;
    case 33:
      Serial.println("Create simple arp");
      for (int i = 0; i < MAX_STEP; i++) {
        all_sequences[type][i].rest = false;
        all_sequences[type][i].accent = false;
        all_sequences[type][i].glide = false;
        all_sequences[type][i].note = SCALE_MINOR[digit[i]] + 24;
      };
      break;
    case 40:
      Serial.println("Create simple arp");
      for (int i = 0; i < MAX_STEP; i++) {
        all_sequences[type][i].rest = true;
        all_sequences[type][i].accent = false;
        all_sequences[type][i].glide = false;
        all_sequences[type][i].note = SCALE_MINOR[digit[0]];
      };
      all_sequences[type][0].rest = false;
      break;
    case 41:
      Serial.println("Create simple arp");
      for (int i = 0; i < MAX_STEP; i++) {
        all_sequences[type][i].rest = true;
        all_sequences[type][i].accent = false;
        all_sequences[type][i].glide = false;
        all_sequences[type][i].note = SCALE_MINOR[digit[0]] + ARP_MINOR[1];
      };
      all_sequences[type][0].rest = false;
      break;
    case 42:
      Serial.println("Create simple arp");
      for (int i = 0; i < MAX_STEP; i++) {
        all_sequences[type][i].rest = true;
        all_sequences[type][i].accent = false;
        all_sequences[type][i].glide = false;
        all_sequences[type][i].note = SCALE_MINOR[digit[0]] + ARP_MINOR[2];
      };
      all_sequences[type][0].rest = false;
      break;
    case 43:
      // yes.
      Serial.println("Create simple arp");
      for (int i = 0; i < MAX_STEP; i++) {
        all_sequences[type][i].rest = true;
        all_sequences[type][i].accent = false;
        all_sequences[type][i].glide = false;
        all_sequences[type][i].note = SCALE_MINOR[digit[0]] - 5;
      };
      all_sequences[type][0].rest = false;
      break;
    default:
      Serial.print("Oh no couldnt generate!");
      break;
  }

  // printSequenceData(all_sequences[type]);
  // switch (type) {
  //   // Transform digits to the current scale, this is also the base sequence.
  //   case 33:
  //     // slow bass!
  //     Serial.println("Generating a slow bass sequence");
  //     for (int i = 0; i < MAX_STEP; i++) {
  //       all_sequences[type][i].rest = true;
  //       all_sequences[type][i].accent = false;
  //       all_sequences[type][i].glide = true;
  //       all_sequences[type][i].sixtienth = 2;
  //       all_sequences[type][i].note = SCALE_MINOR[digit[0]];
  //     };
  //     all_sequences[type][0].rest = false;
  //     all_sequences[type][0].glide = false;

  //     break;
  //   case 34:
  //     // slow bass bit up!
  //     Serial.println("Generating a slow bass sequence");
  //     for (int i = 0; i < MAX_STEP; i++) {
  //       all_sequences[type][i].rest = true;
  //       all_sequences[type][i].accent = false;
  //       all_sequences[type][i].glide = true;
  //       all_sequences[type][i].sixtienth = 2;
  //       all_sequences[type][i].note = SCALE_MINOR[digit[0] + 3];
  //     };
  //     all_sequences[type][0].rest = false;
  //     all_sequences[type][0].glide = false;

  //     break;
  //   case 24:
  //     // Basic pad
  //     for (int i = 0; i < MAX_STEP; i++) {
  //       all_sequences[type][i].rest = true;
  //       all_sequences[type][i].accent = false;
  //       all_sequences[type][i].glide = true;
  //       all_sequences[type][i].sixtienth = 2;
  //       all_sequences[type][i].note = SCALE_MINOR[digit[0]];
  //     };
  //     all_sequences[type][0].rest = false;
  //     break;
  //   case 25:
  //     // Basic pad
  //     for (int i = 0; i < MAX_STEP; i++) {
  //       all_sequences[type][i].rest = true;
  //       all_sequences[type][i].accent = false;
  //       all_sequences[type][i].glide = true;
  //       all_sequences[type][i].sixtienth = 2;
  //       all_sequences[type][i].note = SCALE_MINOR[digit[2]];
  //     };
  //     all_sequences[type][0].rest = false;
  //     break;
  //   case 3:
  //     // Basic lead
  //     for (int i = 0; i < MAX_STEP; i++) {
  //       all_sequences[type][i].rest = false;
  //       all_sequences[type][i].accent = false;
  //       all_sequences[type][i].glide = true;
  //       all_sequences[type][i].sixtienth = 3;
  //       all_sequences[type][i].note = SCALE_MINOR[digit[i]];
  //     };
  //     break;
  //   case 13:
  //     // Basic arp
  //     Serial.println("making the arp");
  //     for (int i = 0; i < MAX_STEP; i++) {
  //       all_sequences[type][i].rest = false;
  //       all_sequences[type][i].accent = false;
  //       all_sequences[type][i].glide = true;
  //       all_sequences[type][i].sixtienth = 1;
  //       all_sequences[type][i].note = SCALE_MINOR[digit[i]];
  //     };
  //     printSequenceData(all_sequences[type]);
  //     break;
  // }
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