#include <uClock.h>
#include <MIDI.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       bassOsc1;      //xy=145,528
AudioSynthWaveform       bassOsc2;      //xy=152,582
AudioSynthWaveformSine   sine2;          //xy=176,758
AudioEffectMultiply      multiply1;      //xy=329,542
AudioEffectEnvelope      bassEnv;      //xy=505,544
AudioFilterStateVariable bassFilter;        //xy=668,554
AudioAmplifier           amp1;           //xy=830,555
AudioOutputI2SQuad       i2s_quad1;      //xy=1015,699
AudioConnection          patchCord1(bassOsc1, 0, multiply1, 0);
AudioConnection          patchCord2(bassOsc2, 0, multiply1, 1);
AudioConnection          patchCord3(sine2, 0, bassFilter, 1);
AudioConnection          patchCord4(multiply1, bassEnv);
AudioConnection          patchCord5(bassEnv, 0, bassFilter, 0);
AudioConnection          patchCord6(bassFilter, 0, amp1, 0);
AudioConnection          patchCord7(amp1, 0, i2s_quad1, 2);
AudioConnection          patchCord8(amp1, 0, i2s_quad1, 0);
// GUItool: end automatically generated code


//AudioConnection patchCord10(drumsd, 0, i2s_quad2, 1);
AudioControlSGTL5000 sgtl5000_1;  // xy=893,614
AudioControlSGTL5000 sgtl5000_2;  // xy=893,684
// GUItool: end automatically generated code

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
  bool clap;
} SEQUENCER_DRUM_DATA;

// Sequencer config
#define STEP_MAX_SIZE 8
#define SYNTH_BASS 0
#define SYNTH_DRUM 1
#define SYNTH_LEAD 2
#define SYNTH_PAD 3
#define BASE_A 220

int SCALE_FULL[12] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
int SCALE_MINOR[7] = { 0, 2, 3, 5, 7, 8, 10 };
int SCALE_MAJOR[8] = { 0, 2, 4, 5, 7, 9, 11 };
float ROOT_NOTES[12] = { 130.8127827, 138.5913155, 146.832384, 155.5634919, 164.8137785, 174.6141157, 184.9972114, 195.997718, 207.6523488, 220, 233.0818808, 246.9416506 };
int ROOT_NOTE = 9;
// 0 = BASE_A;
int BASS_ROOT = BASE_A / 2 / 2;

#define DEBUG_PRINT_STEP false

// Place these from the spreadsheet https://docs.google.com/spreadsheets/d/1liqxYe1Ht9p84bwuuuADFOiAZGA8TLUPVn47AF2BULI/edit#gid=1079230721
double configData[15][6] = { { 50,200,120,122,124,126 },{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 },{ 2,500,2,4,6,8 },{ 0,1000,80,80,80,80 },{ 0,1,0,0,0,0 },{ 1,500,1,1,1,1 },{ 0,500,1,1,1,1 },{ 0,1,1,1,1,1 },{ 1,3,1,1,1,1 },{ 0.4,2,1,0.4,0.4,0.4 },{ 20,40,30,30,30,30 },{ 0.7,5,4,4,4,4 },{ 0,10000,3000,3000,3000,3000 },{ 2.5,3,2.5,2.5,2.5,2.5 } };
int col_min = 0;
int col_max = 1;
int current_style = 2;

int singleSongData[56][5] = { { 1, 4, 0, 24 }, { 1, 4, 0, 24 }, { 1, 4, 0, 24 }, { 1, 5, 0, 24 }, { 1, 5, 19, 24 }, { 1, 5, 20, 24 }, { 1, 5, 20, 24 }, { 1, 5, 21, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 25 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 12, 8, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 14, 4 }, { 14, 4 }, { 14, 4 }, { 14, 4 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 } };
// [bar, instrument]


// [allbarlength][allinstrumentlength]
// https://docs.google.com/spreadsheets/d/1liqxYe1Ht9p84bwuuuADFOiAZGA8TLUPVn47AF2BULI/edit#gid=169379860
// Also get these defined values from sheet
#define MAX_STEP 8
#define MAX_BAR 4
#define MAX_PHRASE 2
#define MAX_SEQUENCE_TYPES 20

int digit[8] = { 1, 1, 5, 1, 1, 6, 1, 2 };
// int digit[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
bool digitIsParsed = false;

// SEQUENCER_DRUM_DATA _sequencer_drum[MAX_STEP];
SEQUENCER_STEP_DATA all_sequences[MAX_SEQUENCE_TYPES][MAX_STEP];
SEQUENCER_DRUM_DATA all_sequences_drum[MAX_SEQUENCE_TYPES][MAX_STEP];
bool generated_sequences[MAX_SEQUENCE_TYPES];

int _current_bass_seq_type;
int _current_pad_seq_type;
int _current_drum_seq_type;
int _current_lead_seq_type;

// configData references
int row_tempo = 0;
int row_sine_1_freq = 1;
int row_sine_1_amp = 2;
int row_bass_attack = 3;
int row_bass_decay = 4;
int row_bass_sustain = 5;
int row_bass_release = 6;
int row_bass_hold = 7;
int row_lfo_amp = 8;
int row_lfo_freq = 9;
int row_sine_fm_amp = 10;
int row_sine_fm_freq = 11;
int row_filter_resonance = 12;
int row_filter_frequency = 13;
int row_filter_octavecontrol = 14;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
void setup() {
  Serial.begin(9600);

  Serial.print("Setup!");
  AudioMemory(160);

  // Inits the clock
  Serial.println("Setup: Setup the uClock");
  uClock.init();

  uClock.setClock16PPQNOutput(onStep16);
  uClock.setTempo(120);
  Serial.println("Setup: Should call makeSoundDesign after the digit input, but do it rightaway now");
  makeSoundDesign(current_style);
  sgtl5000_1.enable();
  sgtl5000_1.volume(.7);
  sgtl5000_2.enable();
  sgtl5000_2.volume(.7);
  sgtl5000_1.setAddress(LOW);
  sgtl5000_2.setAddress(HIGH);

  setupBass();
  // setupPad();
  // setupLead();
  // setupDrum();

  uClock.start();
  // Init listening for the keypad
  MIDI.begin();
  
  sendAllMidiValues();
  
  MIDI.setHandleControlChange(onControlChange);
  usbMIDI.setHandleControlChange(onControlChange);
}

void loop() {
  // init the sequencer when everything is ready
  usbMIDI.read();
  MIDI.read();

  // get any pot changes
  // get any button state changes

  // apply any effect changes to audio channels
  // call monitor function with AudioProcessorUsage(); (if debugging);
}
