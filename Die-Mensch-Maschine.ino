#include <uClock.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform bassOsc1;       //xy=145,528
AudioSynthWaveform bassOsc2;       //xy=152,582
AudioEffectMultiply multiply1;     //xy=329,542
AudioEffectEnvelope envelope1;     //xy=505,544
AudioFilterStateVariable filter1;  //xy=668,554
AudioAmplifier amp1;               //xy=830,555
AudioOutputI2SQuad i2s_quad1;      //xy=1015,699
AudioConnection patchCord1(bassOsc1, 0, multiply1, 0);
AudioConnection patchCord2(bassOsc2, 0, multiply1, 1);
AudioConnection patchCord3(multiply1, envelope1);
AudioConnection patchCord4(envelope1, 0, filter1, 0);
AudioConnection patchCord5(filter1, 0, amp1, 0);
AudioConnection patchCord6(amp1, 0, i2s_quad1, 0);
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

double bass_osc_1_gain;
double bass_osc_2_gain;
double pad_osc_1_gain;
double pad_osc_2_gain;
double bass_env_attack;
double bass_env_decay;
double bass_env_sustain;
double bass_env_release;
double pad_env_attack;
double pad_env_decay;
double pad_env_sustain;
double pad_env_release;
double tempo;

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
  makeSoundDesign(1);
  sgtl5000_1.enable();
  sgtl5000_1.volume(.7);
  sgtl5000_2.enable();
  sgtl5000_2.volume(.7);
  sgtl5000_1.setAddress(LOW);
  sgtl5000_2.setAddress(HIGH);

  setupBass();
  setupPad();
  setupLead();
  setupDrum();

  Serial.println("Setup: Should setup SD");
  Serial.println("Setup: Should if SD is ready, start uClock");
  uClock.start();
  Serial.println("Setup: Should show LED ready animations");
  Serial.println("Setup: Should Connect all buttons and Pots");
  // Init listening for the keypad
  setupMIDI();
}

void loop() {
  // init the sequencer when everything is ready
  loopMIDI();

  // get any pot changes
  // get any button state changes

  // apply any effect changes to audio channels
  // call monitor function with AudioProcessorUsage(); (if debugging);
}
