
#include <uClock.h>
#include <FastLED.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// #include "AudioSampleHandclp2.h"
// #include "AudioSampleHh_open.h"
#include "AudioSampleHh.h"
#include "AudioSampleHhspecial.h"
// #include "AudioSampleKick_1.h"
#include "AudioSampleKick_2.h"
// #include "AudioSampleKick_3.h"
#include "AudioSampleRim.h"
#include "AudioSampleSnare.h"
// #include "AudioSampleTom.h"

// GUItool: begin automatically generated code
AudioSynthWaveform padOsc2;            //xy=419,787
AudioSynthWaveform padOsc3;            //xy=419,852
AudioSynthWaveform padOsc4;            //xy=436,923
AudioSynthWaveform padOsc1;            //xy=439,728
AudioSynthWaveform leadOsc1;           //xy=545,1241
AudioSynthWaveform leadOsc2;           //xy=549,1292
AudioSynthWaveform bassOsc1;           //xy=588,466
AudioSynthWaveform bassOsc2;           //xy=592,545
AudioMixer4 padOscMix;                 //xy=631,804
AudioSynthWaveformSine padLFO2;        //xy=634,1009
AudioSynthWaveformSine padLFO1;        //xy=637,924
AudioMixer4 leadMixer;                 //xy=727,1276
AudioSynthWaveformDc dc2;              //xy=734,1383
AudioMixer4 bassMixer;                 //xy=765,534
AudioSynthWaveformDc dc1;              //xy=778,635
AudioEffectDigitalCombine padCombine;  //xy=821,956
AudioEffectEnvelope padEnv;            //xy=858,785
AudioEffectEnvelope envelope4;         //xy=886,1390
AudioEffectEnvelope leadEnv;           //xy=890,1271
AudioEffectEnvelope bassEnv;           //xy=941,533
AudioEffectEnvelope bassFilterEnv;     //xy=960,631
AudioFilterStateVariable padFilter;    //xy=1027,861
AudioPlayMemory soundKick;             //xy=1027,963
AudioPlayMemory soundHH;               //xy=1029,1063
AudioPlayMemory soundSnare;            //xy=1030,1002
AudioPlayMemory soundClap;             //xy=1036,1113
AudioFilterStateVariable leadFilter;   //xy=1073,1271
AudioFilterStateVariable bassFilter;   //xy=1108,545
AudioMixer4 drumMixer;                 //xy=1442,1001
AudioOutputUSB usb1;                   //xy=1704,994
AudioOutputI2S i2s1;                   //xy=1710,936
AudioMixer4 endmixer;                  //xy=1442,1001
AudioConnection patchCord1(padOsc2, 0, padOscMix, 1);
AudioConnection patchCord2(padOsc3, 0, padOscMix, 2);
AudioConnection patchCord3(padOsc4, 0, padOscMix, 3);
AudioConnection patchCord4(padOsc1, 0, padOscMix, 0);
AudioConnection patchCord5(leadOsc1, 0, leadMixer, 0);
AudioConnection patchCord6(leadOsc2, 0, leadMixer, 1);
AudioConnection patchCord7(bassOsc1, 0, bassMixer, 0);
AudioConnection patchCord8(bassOsc2, 0, bassMixer, 1);
AudioConnection patchCord9(padOscMix, padEnv);
AudioConnection patchCord10(padLFO2, 0, padCombine, 1);
AudioConnection patchCord11(padLFO1, 0, padCombine, 0);
AudioConnection patchCord12(leadMixer, leadEnv);
AudioConnection patchCord13(dc2, envelope4);
AudioConnection patchCord14(bassMixer, bassEnv);
AudioConnection patchCord15(dc1, bassFilterEnv);
AudioConnection patchCord16(padCombine, 0, padFilter, 1);
AudioConnection patchCord17(padEnv, 0, padFilter, 0);
AudioConnection patchCord18(envelope4, 0, leadFilter, 1);
AudioConnection patchCord19(leadEnv, 0, leadFilter, 0);
AudioConnection patchCord20(bassEnv, 0, bassFilter, 0);
AudioConnection patchCord21(bassFilterEnv, 0, bassFilter, 1);
AudioConnection patchCord22(endmixer, 0, usb1, 0);
AudioConnection patchCord23(soundKick, 0, drumMixer, 0);
AudioConnection patchCord24(soundHH, 0, drumMixer, 2);
AudioConnection patchCord25(soundSnare, 0, drumMixer, 1);
AudioConnection patchCord26(soundClap, 0, drumMixer, 3);
AudioConnection patchCord27(leadFilter, 0, i2s1, 0);
AudioConnection patchCord33(leadFilter, 0, i2s1, 1);
AudioConnection patchCord28(bassFilter, 0, endmixer, 1);
// AudioConnection patchCord30(padFilter, 0, endmixer, 0);
AudioConnection patchCord29(drumMixer, 0, usb1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=267,412
AudioControlSGTL5000 sgtl5000_2;  //xy=295,499.9999999999999
// GUItool: end automatically generated code

// Teensy IO
#define KEYPAD_X_1 0 
#define KEYPAD_X_2 1
#define KEYPAD_X_3 2
#define KEYPAD_Y_1 3
#define KEYPAD_Y_2 4
#define KEYPAD_Y_3 5
#define SWITCH_ON_OFF_PIN 28
#define SWITCH_DRUM_STATE_PIN 30
#define SWITCH_BASS_STATE_PIN 29
#define SWITCH_SONG_STATE_PIN 31
#define POT_SPEED_PIN A17
#define POT_ENV1_PIN A16
#define POT_ENV2_PIN A12
#define POT_FILTER1_PIN A15
#define POT_FILTER2_PIN A14
#define POT_LFO_PIN A13
#define POT_NOTE_AMOUNT_PIN A10
#define POT_CHANNEL_LENGTH_PIN A11

// Config variables
#define DEBOUNCE_DELAY 100
#define MAX_STEP 8
#define NUM_SEQ_CHANNELS 3
#define MIDI_ROOT 57
#define BASS_ROOT 33

// Debug variables
#define DEBUG_DIGIT_FAKE true
#define DEBUG_PRINT_POT false

#define SONG_STATE_INTRO 0
#define SONG_STATE_BUILDUP 1
#define SONG_STATE_CHORUS 2
#define SONG_STATE_OUTRO 3

#define PLAY_STATE_STOP 0
#define PLAY_STATE_STARTING 1
#define PLAY_STATE_PLAY 2

// typedefs

typedef struct
{
  int note;
  bool accent;
  bool glide;
  bool rest;
  int root;
} SEQUENCER_STEP_DATA;

// States
int isPlaying = PLAY_STATE_STOP;
int lastDebounceTime;
int song_state;
int last_song_state = 0;


// Sequence info
int digit[MAX_STEP] = { -1, -1, -1, -1, -1, -1, -1, -1 };
int euclid_pattern_length[NUM_SEQ_CHANNELS] = { 12, 15, 8 };
int euclid_event_count[NUM_SEQ_CHANNELS] = { 12, 15, 8 };
int euclid_pattern[NUM_SEQ_CHANNELS][16];
int euclid_index[NUM_SEQ_CHANNELS] = { 0, 0, 0 };
bool euclid_pattern_length_changed = false;
SEQUENCER_STEP_DATA sequence[MAX_STEP];

int SCALE_MINOR[7] = { 0, 2, 3, 5, 7, 8, 10 };



// Synth states
bool lead_endless = false;
bool bass_endless = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  AudioMemory(48);

  Serial.print("Setup!");

  uClock.init();

  uClock.setClock16PPQNOutput(onStep16);
  uClock.setTempo(110);

  sgtl5000_1.enable();
  sgtl5000_1.volume(.5);

  sgtl5000_2.enable();
  sgtl5000_2.volume(.5);

  sgtl5000_1.setAddress(LOW);
  sgtl5000_2.setAddress(HIGH);

  // Teensy IO
  pinMode(KEYPAD_Y_1, OUTPUT);
  pinMode(KEYPAD_Y_2, OUTPUT);
  pinMode(KEYPAD_Y_3, OUTPUT);
  pinMode(KEYPAD_X_1, INPUT_PULLDOWN);
  pinMode(KEYPAD_X_2, INPUT_PULLDOWN);
  pinMode(KEYPAD_X_3, INPUT_PULLDOWN);

  pinMode(SWITCH_ON_OFF_PIN, INPUT_PULLUP);
  pinMode(SWITCH_DRUM_STATE_PIN, INPUT_PULLUP);
  pinMode(SWITCH_BASS_STATE_PIN, INPUT_PULLUP);
  pinMode(SWITCH_SONG_STATE_PIN, INPUT_PULLUP);
  uClock.start();
  setupLeds();
  setupBass();
  setupPad();
  setupLead();
  // setupArp();
  setupDrum();
  endmixer.gain(.5, 0);
  endmixer.gain(.5, 1);
  if (DEBUG_DIGIT_FAKE) {
    for (int i = 0; i < MAX_STEP; i++) {
      digit[i] = SCALE_MINOR[random(0, 6)];
    }
  }


  divideByThree(euclid_pattern_length, 35);
  divideByThree(euclid_event_count, 5);

  euclid(euclid_pattern_length[0], euclid_event_count[0], 0, 0);
  euclid(euclid_pattern_length[1], euclid_event_count[1], 1, 0);
  euclid(euclid_pattern_length[2], euclid_event_count[2], 2, 1);
}


int starting_debounce;
bool pots_parsed = false;

void startSong() {
  setBaseSequence();
  showLEDStartSong();
  isPlaying = PLAY_STATE_STARTING;
  isPlaying = PLAY_STATE_PLAY;

  parsePots();
  uClock.start();
  song_state = SONG_STATE_INTRO;
  showAllLeds();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (isPlaying == PLAY_STATE_PLAY) {
    readSwitches();
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
      readPotentiometers();
      lastDebounceTime = millis();
    }
  } else {
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
      readKeypadEvents();
    }

    if (digit[MAX_STEP - 1] != -1) {
      delay(500);
      startSong();
    }
  }
}