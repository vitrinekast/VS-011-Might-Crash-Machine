void divideByThree(int* arr, int total) {

  arr[0] = floor(total / 3) - round(total / 20);
  arr[1] = floor(total / 3);
  arr[2] = floor(total / 3) + round(total / 5);

  if (arr[0] == 0) {
    arr[0] = 1;
  }
  int dif = total - (arr[0] + arr[1] + arr[2]);
  arr[2] += dif;
}

//--------------- The Euclid Thingy -------------------- => S/O https://github.com/iroth/nanoeuclid/blob/master/NanoEuclid.ino
void offset_pattern(int chan, int offset, int length) {
  if (offset == 0) {
    return;
  }
  int abs_off = abs(offset);

  for (int i = 0; i < abs_off; i++) {
    if (offset < 0) {
      int keep = euclid_pattern[chan][0];
      for (int j = 0; j < length - 1; j++) {
        euclid_pattern[chan][j] = euclid_pattern[chan][j + 1];
      }
      euclid_pattern[chan][length - 1] = keep;
    } else {
      int keep = euclid_pattern[chan][length - 1];
      for (int j = length - 1; j > 0; j--) {
        euclid_pattern[chan][j] = euclid_pattern[chan][j - 1];
      }
      euclid_pattern[chan][0] = keep;
    }
  }
}

int findCloseScale(int target) {
  

  // We start off with the first entry as the nearest.
  byte nearindex = 0;
  // abs returns the positive portion of a value, so -40 becomes 40.
  int neardiff = abs(SCALE_MINOR[0] - target);

  // Now scan the rest of the array.
  for (byte i = 1; i < 7; i++) {
    // Is the difference from the target value for this entry smaller than the currently recorded one?
    if (abs(SCALE_MINOR[i] - target) < neardiff) {
      // Yes, so save the index number along with the current difference.
      nearindex = i;
      neardiff = abs(SCALE_MINOR[i] - target);
    }
  }
  Serial.print("The closest match is: ");
  Serial.println(SCALE_MINOR[nearindex]);
  return SCALE_MINOR[nearindex];
}

void euclid(int length, int k, int chan, int offset) {
  int spaces = length - k;
  float per_pulse = (float)length / (float)k;
  float per_space = (float)length / (float)spaces;
  int i;
  float pos = 0.0f;

  if (per_space > per_pulse) {
    for (i = 0; i < length; i++) {  // empty array to 1
      euclid_pattern[chan][i] = 1;
    }
    for (i = 0; i < spaces; i++) {
      int p = (int)pos;
      euclid_pattern[chan][p] = 0;
      pos = pos + per_space;
    }
  } else {
    for (i = 0; i < length; i++) {  // empty array
      euclid_pattern[chan][i] = 0;
    }
    for (i = 0; i < k; i++) {
      int p = (int)pos;
      euclid_pattern[chan][p] = 1;
      pos = pos + per_pulse;
    }
  }
  int digitCounter = 0;

  // Attach digits to new sequence.
  Serial.print("TODO");
  for (i = 0; i < length; i++) {

    if (euclid_pattern[chan][i] == 1) {
      // TODO: set this to sequence.note to be in scale, once order of things is cleaned up.
      euclid_pattern[chan][i] = findCloseScale(digit[digitCounter]);
      if(euclid_pattern[chan][i] == 0) {
        euclid_pattern[chan][i] = SCALE_MINOR[1];
      }
      digitCounter++;
      if (digitCounter == MAX_STEP) {
        digitCounter = 0;
      }
    }
  }
  offset_pattern(chan, offset, length);
}
