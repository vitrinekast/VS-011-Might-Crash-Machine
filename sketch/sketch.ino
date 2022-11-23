// Acid StepSequencer, a Roland TB303 step sequencer engine clone

#include <uClock.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform waveform2;      //xy=123,594
AudioSynthWaveform waveform1;      //xy=129,546
AudioMixer4 mixer2;                //xy=316,575
AudioSynthSimpleDrum drum1;        //xy=337,775
AudioEffectEnvelope envelope1;     //xy=356,422
AudioMixer4 mixer1;                //xy=515,454
AudioFilterStateVariable filter1;  //xy=647,514
AudioOutputAnalog dac1;            //xy=819,559
AudioConnection patchCord1(waveform2, 0, mixer2, 1);
AudioConnection patchCord2(waveform1, 0, mixer2, 0);
AudioConnection patchCord3(mixer2, envelope1);
AudioConnection patchCord4(drum1, 0, mixer1, 1);
AudioConnection patchCord5(envelope1, 0, mixer1, 0);
AudioConnection patchCord6(mixer1, 0, filter1, 0);
AudioConnection patchCord7(filter1, 0, dac1, 0);
// GUItool: end automatically generated code

// GUItool: end automatically generated code

// Sequencer config
#define STEP_MAX_SIZE 8


// Sequencer data
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
} SEQUENCER_DRUM_DATA;

typedef struct
{
  uint8_t note;
  int8_t length;
} STACK_NOTE_DATA;


#define SYNTH_BASS 0
#define SYNTH_DRUM 1

#define MAX_STEP 8
#define MAX_BAR 4
#define MAX_PHRASE 2

#define BASE_A 220

class BassConfig {
public:
  double detune;
  double attack;
};


// main sequencer data
SEQUENCER_STEP_DATA _sequencer_bass[MAX_STEP];
SEQUENCER_STEP_DATA _sequencer_arp[MAX_STEP];
SEQUENCER_STEP_DATA _sequencer_pad[MAX_STEP];
SEQUENCER_STEP_DATA _sequencer_synth[MAX_STEP];
SEQUENCER_DRUM_DATA _sequencer_drum[MAX_STEP];


// [allbarlength][allinstrumentlength]
// https://docs.google.com/spreadsheets/d/1liqxYe1Ht9p84bwuuuADFOiAZGA8TLUPVn47AF2BULI/edit#gid=169379860
int djData[4][2] = { { 1, 0 }, { 1, 0 }, { 2, 2 }, { 2, 2 } };
int digit[8] = { 1, 1, 5, 1, 1, 6, 1, 2 };


uint16_t _step_length = STEP_MAX_SIZE;

int detune = 20;


void onClock16PPQN(uint32_t tick) {
  // makeStep(tick);
  playStep(tick);
}

void printStepInfo(SEQUENCER_STEP_DATA step) {
  Serial.println("Step: ");
  Serial.print("Note: ");
  Serial.print(step.note);
  Serial.print("accent: ");
  Serial.print(step.accent);
  Serial.print("glide: ");
  Serial.print(step.glide);
  Serial.print("rest: ");
  Serial.print(step.rest);
}


void playStep(uint32_t tick) {
  Serial.print("Bass will play: ");
  SEQUENCER_STEP_DATA step = _sequencer_bass[tick % MAX_STEP];


  printStepInfo(step);
  float frequency = BASE_A * pow(step.note, 3 / 12.000);


  if (!step.glide) {
    envelope1.noteOff();
  }

  if (!step.rest) {
    envelope1.noteOn();
    waveform1.frequency(frequency);
    waveform2.frequency((frequency * .5) + detune);
  }


  // now for the drums
  if (_sequencer_drum[tick % MAX_STEP].kick) {
    drum1.noteOn();
  }
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
    case 10:
      drum1.pitchMod(ourVal);
      break;
    // durm
    case 11:
      drum1.frequency(map(ourVal, 0, 1, 0, 200));
      break;
    // durm
    case 12:
      drum1.length(map(ourVal, 0, 1, 0, 1000));
      break;
    // OSC Shapes
    case 50:
      waveform1.pulseWidth(ourVal);
      break;
    case 51:
      waveform1.begin(getShapeSelector(ourVal));
      break;
    case 60:
      Serial.print("setting pusle width to");
      Serial.print(ourVal);
      waveform2.pulseWidth(ourVal);
      break;
    case 61:
      waveform2.begin(getShapeSelector(ourVal));
      break;
    case 62:
      detune = map(ourVal, 0, 1, 0, 100);
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
    case 100:
      mixer1.gain(0, ourVal);
      break;

    case 101:
      mixer1.gain(1, ourVal);
      break;

    case 102:
      mixer1.gain(2, ourVal);
      break;
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

void generateSequencerData(int digit) {
  Serial.println("generateSequencerData?");
}

void createRandomSequence() {
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(31250);
  AudioMemory(18);

  for (int i = 0; i < 8; i++) {
    Serial.print(digit[i]);
    int newDigit = (digit[i] * random(5));
    Serial.print(" - ");
    Serial.println(newDigit);
    digit[i] = newDigit;
  }

  usbMIDI.setHandleControlChange(onControlChange);


  Serial.println("Start script");

  waveform1.begin(0.3, 440, WAVEFORM_SINE);
  waveform2.begin(0.3, 440, WAVEFORM_SAWTOOTH);

  drum1.pitchMod(0.7);
  drum1.frequency(60);
  drum1.length(500);

  uClock.init();
  // Set the callback function for the step sequencer on 16ppqn;
  uClock.setClock16PPQNOutput(onClock16PPQN);
  uClock.setTempo(86);

  for (int i = 0; i < MAX_STEP; i++) {
    bool somerandom = random(3) < 1;
    _sequencer_bass[i].note = digit[i];
    _sequencer_bass[i].accent = false;
    _sequencer_bass[i].glide = somerandom;
    _sequencer_bass[i].rest = somerandom;
  }

  for (int i = 0; i < MAX_STEP; i++) {
    _sequencer_drum[i].kick = false;
  }

  _sequencer_drum[0].kick = true;
  _sequencer_drum[3].kick = true;


  envelope1.attack(9.2);    // 10 - 11880 ms
  envelope1.decay(31.4);    // 10 - 11880 ms
  envelope1.sustain(0.6);   // 0 - 1
  envelope1.release(84.5);  // 10 - 11880 ms

  mixer1.gain(0, 1);

  // this would be via the number input
  uClock.start();
}
float thingie = 0;
void loop() {
  usbMIDI.read();
}