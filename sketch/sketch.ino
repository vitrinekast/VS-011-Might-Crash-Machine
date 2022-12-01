#include <uClock.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       bassOsc2;       //xy=395,785
AudioSynthWaveform       bassOsc1;       //xy=401,737
AudioSynthWaveform       padOsc1;        //xy=456,966
AudioSynthWaveform       padOsc2;        //xy=476,1029
AudioMixer4              bassMixer;      //xy=588,766
AudioMixer4              padMix;         //xy=666,990
AudioEffectEnvelope      envelope1;      //xy=767,750
AudioEffectEnvelope      padEnv;         //xy=838,988
AudioFilterStateVariable filter1;        //xy=937,752
AudioPlaySdWav           drumsd;     //xy=999,926
AudioOutputI2SQuad       i2s_quad2;      //xy=1231,767
AudioConnection          patchCord1(bassOsc2, 0, bassMixer, 1);
AudioConnection          patchCord2(bassOsc1, 0, bassMixer, 0);
AudioConnection          patchCord3(padOsc1, 0, padMix, 0);
AudioConnection          patchCord4(padOsc2, 0, padMix, 1);
AudioConnection          patchCord5(bassMixer, envelope1);
AudioConnection          patchCord6(padMix, padEnv);
AudioConnection          patchCord7(envelope1, 0, filter1, 0);
AudioConnection          patchCord8(padEnv, 0, i2s_quad2, 1);
AudioConnection          patchCord9(filter1, 0, i2s_quad2, 0);
AudioConnection          patchCord10(drumsd, 0, i2s_quad2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=893,614
AudioControlSGTL5000     sgtl5000_2;     //xy=893,684
// GUItool: end automatically generated code

Sd2Card card;

typedef struct
{
  uint8_t note;
  bool accent;
  bool glide;
  bool rest;
} SEQUENCER_STEP_DATA;

typedef struct
{
  bool kick;
  bool snare;
  bool hh;
  bool lowtom;
} SEQUENCER_DRUM_DATA;

// Sequencer config
#define STEP_MAX_SIZE 8
#define SYNTH_BASS 0
#define SYNTH_DRUM 1
#define SYNTH_ARP 2
#define SYNTH_PAD 3
#define SYNTH_LEAD 4
#define BASE_A 220

// [allbarlength][allinstrumentlength]
// https://docs.google.com/spreadsheets/d/1liqxYe1Ht9p84bwuuuADFOiAZGA8TLUPVn47AF2BULI/edit#gid=169379860
// Also get these defined values from sheet
#define MAX_STEP 8
#define MAX_BAR 4
#define MAX_PHRASE 2

// name[row][column];
int djData[32][5] = { { 1, 0, 0, 1, 0 }, { 1, 0, 0, 1, 0 }, { 2, 1, 0, 1, 1 }, { 2, 1, 0, 1, 1 }, { 1, 1, 1, 1, 0 }, { 1, 1, 1, 1, 0 }, { 1, 1, 1, 1, 0 }, { 1, 1, 1, 1, 1 }, { 1, 0, 0, 1, 0 }, { 1, 0, 0, 1, 0 }, { 2, 1, 0, 1, 1 }, { 2, 1, 0, 1, 1 }, { 1, 1, 1, 1, 0 }, { 1, 1, 1, 1, 0 }, { 1, 1, 1, 1, 0 }, { 1, 1, 1, 1, 1 }, { 1, 0, 0, 1, 0 }, { 1, 0, 0, 1, 0 }, { 2, 1, 0, 1, 1 }, { 2, 1, 0, 1, 1 }, { 1, 1, 1, 1, 0 }, { 1, 1, 1, 1, 0 }, { 1, 1, 1, 1, 0 }, { 1, 1, 1, 1, 1 }, { 1, 0, 0, 1, 0 }, { 1, 0, 0, 1, 0 }, { 2, 1, 0, 1, 1 }, { 2, 1, 0, 1, 1 }, { 1, 1, 1, 1, 0 }, { 1, 1, 1, 1, 0 }, { 1, 1, 1, 1, 0 }, { 1, 1, 1, 1, 1 } };
int digit[8] = { 1, 1, 5, 1, 1, 6, 1, 2 };

int bassSequences[2][8];

int bass_detune = 0;
int pad_detune = 0;

// main sequencer data
SEQUENCER_STEP_DATA _sequencer_bass[MAX_STEP];
SEQUENCER_DRUM_DATA _sequencer_drum[MAX_STEP];
SEQUENCER_STEP_DATA _sequencer_arp[MAX_STEP];
SEQUENCER_STEP_DATA _sequencer_pad[MAX_STEP];
SEQUENCER_STEP_DATA _sequencer_lead[MAX_STEP];

SEQUENCER_STEP_DATA currentBassSequence[MAX_STEP];
SEQUENCER_STEP_DATA currentPadSequence[MAX_STEP];

int currentBassSequenceType = -1;
int currentPadSequenceType = -1;

void onClock16PPQN(uint32_t tick) {
  // makeStep(tick);
  playStep(tick);
}

double getFrequency(int halfsteps) {
  return BASE_A * pow(halfsteps, 3 / 12.000);
}

void playStepDrum(uint32_t tick) {
  SEQUENCER_DRUM_DATA step = _sequencer_drum[tick % MAX_STEP];
  Serial.println("Drum: ");
  // now for the drums
  if (step.kick) {
    Serial.print(" - Play kick");
    drumsd.play("kick1.wav");
    // drum1.noteOn();
  }

  if (step.snare) {
    Serial.print(" - Should play snare");
    drumsd.play("clap1.wav");
  }

  if (step.hh) {
    Serial.print(" - Should play hh");
    drumsd.play("hh1.wav");
  }

  if (step.lowtom) {
    Serial.print(" - Should play lowtom");
  }
}

// this function only works for synth based sequences.
void setSequenceByType(SEQUENCER_STEP_DATA* sequence, int instrument, int type) {
  Serial.println("Set sequence");
  Serial.print(instrument);
  Serial.print(" - ");
  Serial.print(type);
  // Set all to empty
  if (type == 0) {
    for (int i = 0; i < MAX_STEP; i++) {
      sequence[i].rest = true;
      sequence[i].accent = false;
      sequence[i].glide = false;
      sequence[i].note = 0;
    }
  }

  // Base
  if (type == 1 && instrument == SYNTH_BASS) {
    for (int i = 0; i < MAX_STEP; i++) {
      sequence[i].note = digit[i];
      sequence[i].rest = false;
      sequence[i].accent = false;
      sequence[i].glide = false;
    }
  }

  if (type == 1 && instrument == SYNTH_PAD) {
    Serial.println("generating a pad sequence!");
    for (int i = 0; i < MAX_STEP; i++) {
      sequence[i].note = digit[0];
      sequence[i].rest = false;
      sequence[i].accent = false;
      sequence[i].glide = true;
    }
    sequence[0].glide = false;
    sequence[3].glide = false;
    sequence[2].rest = false;
    sequence[4].note = digit[0] + 2;
  }

  // higher 1octv.
  if (type == 2) {
    for (int i = 0; i < MAX_STEP; i++) {
      sequence[i].note = digit[i] + 12;
      sequence[i].rest = false;
      sequence[i].accent = false;
      sequence[i].glide = false;
    }
  }
}

void checkForSequence(uint32_t tick, SEQUENCER_STEP_DATA* sequence, int instrument, int sequenceType) {
  // if at first step, please find ur sequence;
  if ((tick % MAX_STEP) == 0) {
    Serial.print("----- checkForSequence - First step so find a sequence");

    if (djData[abs(tick / MAX_BAR)][instrument] != sequenceType) {
      Serial.print(" - generate the new one");
      sequenceType = djData[abs(tick / MAX_BAR)][instrument];
      setSequenceByType(sequence, instrument, sequenceType);
    } else {
      Serial.print(" - continue with previous sequence");
    }
  }
}


void playStepBass(uint32_t tick) {
  checkForSequence(tick, currentBassSequence, SYNTH_BASS, currentBassSequenceType);

  SEQUENCER_STEP_DATA step = currentBassSequence[tick % MAX_STEP];
  Serial.print("------- playnote: ");
  Serial.print(step.note);
  double frequency = getFrequency(step.note);
  if (!step.glide) {
    envelope1.noteOff();
  }

  if (!step.rest) {
    envelope1.noteOn();
    bassOsc1.frequency(frequency);
    bassOsc2.frequency((frequency * .5) + bass_detune);
  }
}

void playStepPad(uint32_t tick) {
  Serial.println("");
  Serial.println("Pad: ");

  checkForSequence(tick, currentPadSequence, SYNTH_PAD, currentPadSequenceType);
  SEQUENCER_STEP_DATA step = currentPadSequence[tick % MAX_STEP];
  Serial.print("------- playnote: ");
  Serial.print(step.note);
  if (!step.glide) {
    Serial.print("note off");
    padEnv.noteOff();

    if (!step.rest) {
      Serial.print("note on");
      padEnv.noteOn();
    }
  }

  if (!step.rest) {
    Serial.print("note freq: ");
    Serial.print(step.note);

    // minor chord
    padOsc1.frequency(getFrequency(step.note));
    padOsc2.frequency((getFrequency(step.note + 3)) + pad_detune);
  }
}

void playStepArp(uint32_t tick) {
  Serial.println("Arp: ");
}

void playStepLead(uint32_t tick) {
  Serial.println("Lead: ");
}


void playStep(uint32_t tick) {
  playStepBass(tick);
  playStepDrum(tick);
  playStepPad(tick);
  // playStepArp(tick);
  // playStepLead(tick);
}


void makeStep(uint32_t tick) {
  Serial.print("SEQ - tick: ");
  Serial.print(tick);
  Serial.print(" step: ");
  Serial.print(tick % MAX_STEP);

  Serial.print(" bar: ");
  Serial.print(abs(tick / MAX_BAR));

  Serial.print(" phrase: ");

  Serial.println(abs(tick / (MAX_BAR * MAX_PHRASE)));

  if (tick % MAX_STEP == 0) {
    Serial.println("SEQ: Finish bar");
  }

  if (tick % (MAX_STEP * MAX_BAR) == 0) {
    Serial.println("SEQ: Finish phrase");
  }

  if (tick % (MAX_STEP * MAX_BAR * MAX_PHRASE) == 0) {
    Serial.println("SEQ: Finish song");
  }
}

int getShapeSelector(float val) {
  if (val < 0.25) {
    return WAVEFORM_SINE;
  } else if (val < 0.5) {
    return WAVEFORM_SAWTOOTH;
  } else if (val < 0.75) {
    return WAVEFORM_SQUARE;
  } else {
    return WAVEFORM_TRIANGLE;
  }
}

void onControlChange(byte channel, byte control, byte value) {

  float ourVal = (float)value / 127;

  switch (control) {
    // durm
    // case 10:
    //   drum1.pitchMod(ourVal);
    //   break;
    // case 11:
    //   drum1.frequency(map(ourVal, 0, 1, 0, 200));
    //   break;
    // case 12:
    //   drum1.length(map(ourVal, 0, 1, 0, 1000));
    //   break;


    // OSC Shapes
    case 50:
      bassOsc1.pulseWidth(ourVal);
      break;
    case 51:
      bassOsc1.begin(getShapeSelector(ourVal));
      break;
    case 52:
      bassOsc2.pulseWidth(ourVal);
      break;
    case 53:
      bassOsc2.begin(getShapeSelector(ourVal));
      break;
    case 54:
      bass_detune = map(ourVal, 0, 1, 0, 100);
      break;
    case 55:
      padOsc1.pulseWidth(ourVal);
      break;
    case 56:
      padOsc1.begin(getShapeSelector(ourVal));
      break;
    case 57:
      padOsc2.pulseWidth(ourVal);
      break;
    case 58:
      padOsc2.begin(getShapeSelector(ourVal));
      break;
    case 59:
      pad_detune = map(ourVal, 0, 1, 0, 100);
      break;


      // ADSR
    case 80:
      envelope1.attack(map(ourVal, 0, 1, 10, 500));
      break;
    case 81:
      envelope1.decay(map(ourVal, 0, 1, 10, 500));
      break;
    case 82:
      envelope1.sustain(map(ourVal, 0, 1, 0, 1));
      break;
    case 83:
      envelope1.release(map(ourVal, 0, 1, 10, 500));
      break;
      // ADSR
    case 84:
      padEnv.attack(map(ourVal, 0, 1, 10, 500));
      break;
    case 85:
      padEnv.decay(map(ourVal, 0, 1, 10, 500));
      break;
    case 86:
      padEnv.sustain(map(ourVal, 0, 1, 0, 1));
      break;
    case 87:
      padEnv.release(map(ourVal, 0, 1, 10, 500));
      break;



    // case 100:
    //   mixer1.gain(0, ourVal);
    //   break;

    // case 101:
    //   mixer1.gain(1, ourVal);
    //   break;

    // case 102:
    //   mixer1.gain(2, ourVal);
    //   break;
    // case 103:
    //   mixer1.gain(2, ourVal);
    //   break;

    case 110:
      filter1.frequency(map(ourVal, 0, 1, 0, 4000));
      break;

    case 111:
      filter1.resonance(map(ourVal, 0, 1, 0.7, 5));
      break;
    // general
    case 1:
      uClock.setTempo(map(ourVal, 0, 1, 0, 250));
      break;
  }
}

void fillSequenceTypes() {

  // ideally, here we would generate all needed sequences that are mentioned in the sheet, so during the playing, we can select from here.
  // drums however, is a different story


  for (int i = 0; i < MAX_STEP; i++) {
    _sequencer_drum[i].kick = false;
  }

  _sequencer_drum[0].kick = true;
  _sequencer_drum[3].kick = true;
}

void setSynthValues() {
  bass_detune = 0;
  pad_detune = 0;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(31250);
  AudioMemory(190);
  Serial.println("Start script");

  fillSequenceTypes();
  setSynthValues();

  
  // usbMIDI.setHandleControlChange(onControlChange);

  uClock.init();
  uClock.setClock16PPQNOutput(onClock16PPQN);

  // setting all these init values;
  uClock.setTempo(40);

  bassOsc1.begin(0.3, 440, WAVEFORM_SINE);
  bassOsc2.begin(0.3, 440, WAVEFORM_SAWTOOTH);

  padOsc1.begin(0.3, 440, WAVEFORM_SINE);
  padOsc2.begin(0.3, 440, WAVEFORM_SINE);

  // drum1.pitchMod(0.7);
  // drum1.frequency(60);
  // drum1.length(500);

  envelope1.attack(9.2);    // 10 - 11880 ms
  envelope1.decay(31.4);    // 10 - 11880 ms
  envelope1.sustain(0.6);   // 0 - 1
  envelope1.release(84.5);  // 10 - 11880 ms

  padEnv.attack(9.2);    // 10 - 11880 ms
  padEnv.decay(31.4);    // 10 - 11880 ms
  padEnv.sustain(0.6);   // 0 - 1
  padEnv.release(84.5);  // 10 - 11880 ms

  // mixer1.gain(0, 1);
  // mixer1.gain(1, 1);
  // mixer1.gain(2, 1);
  // mixer1.gain(3, 1);

  padMix.gain(0, 1);
  padMix.gain(1, 1);
  padMix.gain(2, 1);
  padMix.gain(3, 1);

  bassMixer.gain(0, 1);
  bassMixer.gain(1, 1);
  bassMixer.gain(2, 1);
  bassMixer.gain(3, 1);


   // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, BUILTIN_SDCARD)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return;
  } else {
   Serial.println("Wiring is correct and a card is present.");
  //  drumsd.play("song.wav");
   uClock.start();
  }

}

void loop() {
  // usbMIDI.read();
}