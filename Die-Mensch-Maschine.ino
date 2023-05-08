#include <uClock.h>
// #define NO_HARDWARE_PIN_SUPPORT
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
#include "AudioSampleTom.h"

// GUItool: begin automatically generated code
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform padOsc4;  // xy=58,238
AudioSynthWaveform padOsc1;  // xy=58,280
AudioSynthWaveform padOsc3;  // xy=58,327
AudioSynthWaveform padOsc2;  // xy=58,417
AudioSynthWaveform bassOsc1; // xy=61,81
AudioSynthWaveform bassOsc2; // xy=61,119
AudioSynthWaveform leadOsc1; // xy=59.5,564
AudioSynthWaveform leadOsc2; // xy=59.5,628
AudioPlayMemory soundSnare;  // xy=182,817
AudioMixer4 leadMixer;       // xy=198,596
AudioPlayMemory soundHH;     // xy=201,847
AudioMixer4 padOscMix;       // xy=223,217
AudioPlayMemory soundClap;   // xy=229,895
AudioPlayMemory soundKick;   // xy=234.5,787
AudioSynthSimpleDrum soundSynth;
AudioSynthWaveformSine padLFO2;       // xy=262,369
AudioMixer4 bassMixer;                // xy=272,54
AudioSynthWaveformSine padLFO1;       // xy=277,317
AudioSynthWaveformDc dc1;             // xy=279,122
AudioSynthWaveformDc dc2;             // xy=300,648
AudioEffectEnvelope padEnv;           // xy=362,195
AudioMixer4 drumMixer;                // xy=407.5,827
AudioEffectEnvelope leadEnv;          // xy=436,598
AudioEffectEnvelope envelope4;        // xy=447,647
AudioEffectEnvelope bassEnv;          // xy=460,71
AudioEffectDigitalCombine padCombine; // xy=460,367
AudioEffectEnvelope bassFilterEnv;    // xy=474,128
AudioFilterStateVariable padFilter;   // xy=599,268
AudioFilterStateVariable leadFilter;  // xy=647,609
AudioFilterStateVariable bassFilter;  // xy=702,111
AudioMixer4 endmixer;                 // xy=886,437
AudioOutputI2S i2s1;                  // xy=1047,671
AudioOutputUSB usb1;                  // xy=1059,586
AudioConnection patchCord1(padOsc4, 0, padOscMix, 3);
AudioConnection patchCord2(padOsc1, 0, padOscMix, 0);
AudioConnection patchCord3(padOsc3, 0, padOscMix, 2);
AudioConnection patchCord4(padOsc2, 0, padOscMix, 1);
AudioConnection patchCord5(bassOsc1, 0, bassMixer, 0);
AudioConnection patchCord6(bassOsc2, 0, bassMixer, 1);
AudioConnection patchCord7(leadOsc1, 0, leadMixer, 0);
AudioConnection patchCord8(leadOsc2, 0, leadMixer, 1);
AudioConnection patchCord9(soundSnare, 0, drumMixer, 1);
AudioConnection patchCord10(leadMixer, leadEnv);
AudioConnection patchCord11(soundHH, 0, drumMixer, 2);
AudioConnection patchCord12(padOscMix, padEnv);
AudioConnection patchCord13(soundClap, 0, drumMixer, 3);
AudioConnection patchCord14(soundSynth, 0, drumMixer, 0);
AudioConnection patchCord15(padLFO2, 0, padCombine, 1);
AudioConnection patchCord16(bassMixer, bassEnv);
AudioConnection patchCord17(padLFO1, 0, padCombine, 0);
AudioConnection patchCord18(dc1, bassFilterEnv);
AudioConnection patchCord19(dc2, envelope4);
AudioConnection patchCord20(padEnv, 0, padFilter, 0);
AudioConnection patchCord21(drumMixer, 0, usb1, 1);
AudioConnection patchCord22(leadEnv, 0, leadFilter, 0);
AudioConnection patchCord23(envelope4, 0, leadFilter, 1);
AudioConnection patchCord24(bassEnv, 0, bassFilter, 0);
AudioConnection patchCord25(padCombine, 0, padFilter, 1);
// AudioConnection          patchCord26(bassFilterEnv, 0, bassFilter, 1);
AudioConnection patchCord27(leadFilter, 0, endmixer, 0);
AudioConnection patchCord28(bassFilter, 0, endmixer, 1);
AudioConnection patchCord29(endmixer, 0, usb1, 0);
AudioControlSGTL5000 sgtl5000_2; // xy=682,30
AudioControlSGTL5000 sgtl5000_1; // xy=810,29
// GUItool: end automatically generated code

// Teensy IO

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
#define DEBOUNCE_DELAY 10
#define MAX_STEP 8
#define NUM_SEQ_CHANNELS 2
#define MIDI_ROOT 57
#define BASS_ROOT 33

// Debug variables
#define DEBUG_DIGIT_FAKE true
#define DEBUG_PRINT_POT false
#define DEBUG_PRINT_STEP false

#define SONG_STATE_INTRO 0
#define SONG_STATE_BUILDUP 1
#define SONG_STATE_CHORUS 2
#define SONG_STATE_BETWEEN 3
#define SONG_STATE_OUTRO 4

#define PLAY_STATE_STOP 0
#define PLAY_STATE_STARTING 1
#define PLAY_STATE_PLAY 2

#define LED_PIN 12
#define NUM_LEDS 28

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
int digit[MAX_STEP] = {-1, -1, -1, -1, -1, -1, -1, -1};
int euclid_pattern_length[NUM_SEQ_CHANNELS] = {12, 15};
int euclid_event_count[NUM_SEQ_CHANNELS] = {0, 0};
int euclid_pattern[NUM_SEQ_CHANNELS][16];
int euclid_index[NUM_SEQ_CHANNELS] = {0, 0};
bool euclid_pattern_length_changed = false;
SEQUENCER_STEP_DATA sequence[MAX_STEP];

#define DRUM_SEQ_LAYERS 5
int drum_eucl_sequence[DRUM_SEQ_LAYERS][16];

// for each layer, set the structure of the songs, 5 being the phases. The array contaibns the amount of pulses.
int drum_eucl_structure[DRUM_SEQ_LAYERS][5] = {
    {4, 5, 8, 5},
    {3, 5, 8, 5},
    {1, 5, 8, 5},
    {1, 5, 8, 5},
    {5, 5, 8, 5},
};

int SCALE_MINOR[7] = {0, 2, 3, 5, 7, 8, 10};

int keys[3][3] = {
    {7, 8, 9},
    {4, 5, 6},
    {1, 2, 3}};
byte rowPins[3] = {35, 36, 37};
byte colPins[3] = {10, 33, 34};

// Synth states
bool lead_endless = false;
bool bass_endless = false;

// To clean up
int starting_debounce;
bool pots_parsed = false;

int lastReadKey = -2;
int digitIndex = 0;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  AudioMemory(48);

  Serial.println("======Setup!=====");

  uClock.init();

  uClock.setClock16PPQNOutput(onStep);
  // uClock.setClock32PPQNOutput(onStep32);
  uClock.setTempo(120);

  sgtl5000_1.enable();
  sgtl5000_1.volume(.5);

  sgtl5000_2.enable();
  sgtl5000_2.volume(.5);

  sgtl5000_1.setAddress(LOW);
  sgtl5000_2.setAddress(HIGH);

  // Teensy IO
  for (int i = 0; i < 3; i++)
  {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }

  // Set the column pins as inputs with pull-ups
  for (int i = 0; i < 3; i++)
  {
    pinMode(colPins[i], INPUT_PULLUP);
  }

  // setupSwitches();
  // setupLeds();
  // cleanupLeds();
  setupBass();
  // setupPad();
  // setupLead();
  // setupArp();
  setupDrum();

  endmixer.gain(0, .5);
  endmixer.gain(1, .5);

  if (DEBUG_DIGIT_FAKE)
  {
    Serial.println("faking a debug digit");
    for (int i = 0; i < MAX_STEP; i++)
    {
      digit[i] = SCALE_MINOR[random(3)];
    }
    parseDigit();
  }

  // divideByThree(euclid_pattern_length, 35);
  // divideByThree(euclid_event_count, 5);

  // euclid(euclid_pattern_length[0], euclid_event_count[0], 0, 0);
  // euclid(euclid_pattern_length[1], euclid_event_count[1], 1, 0);

  setDrumEuclid();
}

void parseDigit()
{
  String seed = "";

  for (int i = 0; i < MAX_STEP; i++)
  {
    seed += digit[i];
  }
  Serial.println("Starting with digit");
  randomSeed(seed.toInt());
}

void startSong()
{
  Serial.println("----startSong()");
  setBaseSequence();
  isPlaying = PLAY_STATE_STARTING;
  isPlaying = PLAY_STATE_PLAY;

  parsePots();
  uClock.start();
  song_state = SONG_STATE_INTRO;
  // showAllLeds();
}

void stopSong()
{
  Serial.println("----stopSong()");
  setBaseSequence();
  isPlaying = PLAY_STATE_STOP;

  uClock.stop();
  lastReadKey = -2;
  digitIndex = 0;
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (isPlaying == PLAY_STATE_PLAY)
  {
    // readSwitches();
    // if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY)
    // {
    //   readPotentiometers();
    //   lastDebounceTime = millis();
    // }
  }
  else
  {
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY)
    {
      // readKeypadEvents();
      int key = getKey();

      if (key != lastReadKey)
      {
        Serial.println("Waiting for digits!");
        Serial.println(key);
        lastDebounceTime = millis();
        lastReadKey = key;

        if (key != -1)
        {
          digit[digitIndex] = key;
          // setLEDUntill(ceil((NUM_LEDS / 9) * key), .25);
          playSingleBassNote(key);
          digitIndex++;
        }
      }
    }

    if (digit[MAX_STEP - 1] != -1)
    {
      Serial.println("got all the steps!");
      delay(500);
      startSong();
      parseDigit();
    }
  }
}