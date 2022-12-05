
#include <uClock.h>
#include <MIDI.h>
#include <Arduino.h>

#include "AudioSampleKick.h"          // http://www.freesound.org/people/DWSD/sounds/171104/
#include "AudioSampleSnare.h"         // http://www.freesound.org/people/KEVOY/sounds/82583/
#include "AudioSampleTomtom.h"        // http://www.freesound.org/people/zgump/sounds/86334/
#include "AudioSampleHihat.h"         // http://www.freesound.org/people/mhc/sounds/102790/
#include "AudioSampleGong.h"          // http://www.freesound.org/people/juskiddink/sounds/86773/
#include "AudioSampleCashregister.h"  // http://www.freesound.org/people/kiddpark/sounds/201159/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform padOsc2;            //xy=648.5555381774902,1107.7777938842773
AudioSynthWaveform padOsc3;            //xy=648.5555877685547,1172.22217130661
AudioSynthWaveform padOsc4;            //xy=665.5555572509766,1243.111083984375
AudioSynthWaveform padOsc1;            //xy=668.5556335449219,1048.333339691162
AudioSynthWaveform leadOsc1;           //xy=758,1555.5556640625
AudioSynthWaveform leadOsc2;           //xy=761.5555419921875,1600.5556640625
AudioSynthWaveform bassOsc1;           //xy=819,808.333251953125
AudioSynthWaveform bassOsc2;           //xy=821,865.333251953125
AudioMixer4 padOscMix;                 //xy=860.3333435058594,1124.6666259765625
AudioSynthWaveformSine padLFO2;        //xy=863,1329
AudioSynthWaveformSine padLFO1;        //xy=866,1244
AudioSynthWaveformDc dc2;              //xy=921,1681
AudioMixer4 leadMixer;                 //xy=937,1595
AudioMixer4 bassOscMix;                //xy=1005.5,837
AudioSynthWaveformDc dc1;              //xy=1007.5,955
AudioEffectDigitalCombine padCombine;  //xy=1050,1276
AudioEffectEnvelope leadFilterEnv;     //xy=1117,1680
AudioEffectEnvelope leadEnv;           //xy=1119.5555419921875,1591.4444580078125
AudioEffectEnvelope bassEnv;           //xy=1170.6666259765625,853.6666259765625
AudioEffectEnvelope bassFilterEnv;     //xy=1189.5,951
AudioPlayMemory soundKick;             //xy=1222,1374
AudioPlayMemory soundHH;               //xy=1224,1474
AudioPlayMemory soundSnare;            //xy=1225,1413
AudioPlayMemory soundClap;             //xy=1231,1524
AudioFilterStateVariable padFilter;    //xy=1256.5556640625,1181.333251953125
AudioFilterStateVariable filter3;      //xy=1302,1591
AudioFilterStateVariable bassFilter;   //xy=1337,865
AudioEffectEnvelope padEnv;            //xy=1442,1181
AudioMixer4 drumMixer;                 //xy=1481,1425
AudioAmplifier leadAmp;                //xy=1494.7777099609375,1588
AudioAmplifier bassAmp;                //xy=1564.6666259765625,851.6666259765625
AudioMixer4 mainMixer;                 //xy=1860.8890380859375,1195.22216796875
AudioOutputUSB usb1;                   //xy=1876,1268
AudioOutputI2SQuad i2s_quad1;          //xy=2144.66650390625,1173.6666259765625
AudioConnection patchCord1(padOsc2, 0, padOscMix, 1);
AudioConnection patchCord2(padOsc3, 0, padOscMix, 2);
AudioConnection patchCord3(padOsc4, 0, padOscMix, 3);
AudioConnection patchCord4(padOsc1, 0, padOscMix, 0);
AudioConnection patchCord5(leadOsc1, 0, leadMixer, 0);
AudioConnection patchCord6(leadOsc2, 0, leadMixer, 1);
AudioConnection patchCord7(bassOsc1, 0, bassOscMix, 0);
AudioConnection patchCord8(bassOsc2, 0, bassOscMix, 1);
AudioConnection patchCord9(padOscMix, 0, padFilter, 0);
AudioConnection patchCord10(padLFO2, 0, padCombine, 1);
AudioConnection patchCord11(padLFO1, 0, padCombine, 0);
AudioConnection patchCord12(dc2, leadFilterEnv);
AudioConnection patchCord13(leadMixer, leadEnv);
AudioConnection patchCord14(bassOscMix, bassEnv);
AudioConnection patchCord15(dc1, bassFilterEnv);
AudioConnection patchCord16(padCombine, 0, padFilter, 1);
AudioConnection patchCord17(leadFilterEnv, 0, filter3, 1);
AudioConnection patchCord18(leadEnv, 0, filter3, 0);
AudioConnection patchCord19(bassEnv, 0, bassFilter, 0);
AudioConnection patchCord20(bassFilterEnv, 0, bassFilter, 1);
AudioConnection patchCord21(soundKick, 0, drumMixer, 0);
AudioConnection patchCord22(soundHH, 0, drumMixer, 2);
AudioConnection patchCord23(soundSnare, 0, drumMixer, 1);
AudioConnection patchCord24(soundClap, 0, drumMixer, 3);
AudioConnection patchCord25(padFilter, 0, padEnv, 0);
AudioConnection patchCord26(filter3, 0, leadAmp, 0);
AudioConnection patchCord27(bassFilter, 0, bassAmp, 0);
AudioConnection patchCord28(padEnv, 0, mainMixer, 1);
AudioConnection patchCord29(drumMixer, 0, mainMixer, 2);
AudioConnection patchCord30(leadAmp, 0, mainMixer, 3);
AudioConnection patchCord31(leadAmp, 0, usb1, 1);
AudioConnection patchCord32(bassAmp, 0, mainMixer, 0);
AudioConnection patchCord33(bassAmp, 0, usb1, 0);
AudioConnection patchCord34(mainMixer, 0, i2s_quad1, 1);
AudioConnection patchCord35(mainMixer, 0, i2s_quad1, 3);
AudioConnection patchCord36(mainMixer, 0, i2s_quad1, 0);
AudioConnection patchCord37(mainMixer, 0, i2s_quad1, 2);
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
  int sixtienth;
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
#define AUDIO_MEM 40
#define DEBUG_PRINT_STEP false
#define BASS_ROOT 33
#define PAD_ROOT 57
#define LEAD_ROOT 81
#define COL_MIN 0
#define COL_MAX 1
#define MAX_STEP 8
#define MAX_BAR 4
#define MAX_PHRASE 2
#define MAX_SEQUENCE_TYPES 40
#define MIDI_CHANNEL_SENT 1
#define MIDI_CHANNEL_RECEIVE 2

// configData references
#define row_tempo 0
#define row_sine_1_freq 1
#define row_sine_1_amp 2
#define row_bass_attack 3
#define row_bass_decay 4
#define row_bass_sustain 5
#define row_bass_release 6
#define row_bass_hold 7
#define row_pad_attack 8
#define row_pad_decay 9
#define row_pad_sustain 10
#define row_pad_release 11
#define row_pad_hold 12
#define row_lead_attack 13
#define row_lead_decay 14
#define row_lead_sustain 15
#define row_lead_release 16
#define row_lead_hold 17
#define row_bass_filter_resonance 18
#define row_bass_filter_frequency 19
#define row_pad_filter_resonance 20
#define row_pad_filter_frequency 21
#define row_padOsc1Shape 22
#define row_padOsc2Shape 23
#define row_padOsc3Shape 24
#define row_padOsc4Shape 25
#define row_leadOsc1Shape 26
#define row_leadOsc2Shape 27
#define row_bassOsc1Shape 28
#define row_bassOsc2Shape 29

int SCALE_FULL[12] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
int SCALE_MINOR[7] = { 0, 2, 3, 5, 7, 8, 10 };
int ARP_MINOR[4] = { 0, 3, 7, 10 };
int SCALE_MAJOR[8] = { 0, 2, 4, 5, 7, 9, 11 };
float ROOT_NOTES[12] = { 130.8127827, 138.5913155, 146.832384, 155.5634919, 164.8137785, 174.6141157, 184.9972114, 195.997718, 207.6523488, 220, 233.0818808, 246.9416506 };

// Place these from the spreadsheet https://docs.google.com/spreadsheets/d/1liqxYe1Ht9p84bwuuuADFOiAZGA8TLUPVn47AF2BULI/edit#gid=1079230721
#define SONG_LENGTH 29
double configData[30][6] = { { 50, 200, 120, 122, 124, 126 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 2, 500, 0, 0.2, 0.4, 0.6 }, { 0, 1000, 300, 80, 80, 80 }, { 0, 1, 0, 0, 0, 0 }, { 1, 500, 433, 1, 1, 1 }, { 0, 500, 1, 1, 1, 1 }, { 2, 5000, 1000, 1002, 1004, 1006 }, { 0, 1000, 600, 80, 80, 80 }, { 0, 1, 0.8, 0, 0, 0 }, { 1, 5000, 1800, 1, 1, 1 }, { 0, 500, 0, 1, 1, 1 }, { 2, 500, 300, 302, 304, 306 }, { 0, 1000, 400, 80, 80, 80 }, { 0, 1, 1, 0, 0, 0 }, { 1, 500, 120, 1, 1, 1 }, { 0, 500, 120, 1, 1, 1 }, { 0.7, 5, 5, 4, 4, 4 }, { 0, 10000, 400, 3000, 3000, 3000 }, { 0.7, 5, 0.7, 4, 4, 4 }, { 0, 5000, 1001, 3000, 3000, 3000 }, { 0, 7, 0, 0, 0, 0 }, { 0, 7, 0, 0, 0, 0 }, { 0, 7, 0, 0, 0, 0 }, { 0, 7, 0, 0, 0, 0 }, { 0, 7, 0, 0, 0, 0 }, { 0, 7, 0, 0, 0, 0 }, { 0, 7, 0, 0, 0, 0 }, { 0, 7, 0, 0, 0, 0 } };
int singleSongData[29][5] = { { 33, 0, 3 }, { 33, 0, 3 }, { 34, 0, 3 }, { 33, 0, 3 }, { 33, 29, 13 }, { 33, 29, 3 }, { 34, 29, 3 }, { 33, 29, 3 }, { 33, 29, 13 }, { 33, 29, 3 }, { 34, 29, 3 }, { 33, 29, 3 }, { 33, 29, 13 }, { 33, 29, 3 }, { 34, 29, 3 }, { 33, 29, 3 } };

SEQUENCER_STEP_DATA all_sequences[MAX_SEQUENCE_TYPES][MAX_STEP];
SEQUENCER_STEP_DATA base_sequence[MAX_STEP];
SEQUENCER_DRUM_DATA all_sequences_drum[MAX_SEQUENCE_TYPES][MAX_STEP];
bool generated_sequences[MAX_SEQUENCE_TYPES];

// State machine
int current_style = 2;
int digit[8] = { 1, 1, 5, 1, 1, 6, 1, 2 };
bool digitIsParsed = false;
int _current_bass_seq_type;
int _current_pad_seq_type;
int _current_drum_seq_type;
int _current_lead_seq_type;
bool bass_is_setup = false;
bool pad_is_setup = false;
bool drum_is_setup = false;
bool lead_is_setup = false;

int lead_modulo = 6;
double current_freq = 0;
int target_freq = 5000;

int target_time = 0;
double target_steps = 0;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

void setup() {
  Serial.begin(9600);

  Serial.print("Setup!");
  AudioMemory(92);

  // Inits the clock
  uClock.init();

  uClock.setClock16PPQNOutput(onStep16);
  uClock.setTempo(90);
  makeSoundDesign(current_style);

  sgtl5000_1.enable();
  sgtl5000_1.volume(.5);

  sgtl5000_2.enable();
  sgtl5000_2.volume(.5);

  sgtl5000_1.setAddress(LOW);
  sgtl5000_2.setAddress(HIGH);

  setupBass();
  // setupPad();
  setupLead();
  // setupDrum();

  uClock.start();
  usbMIDI.sendRealTime(usbMIDI.Start);

  usbMIDI.setHandleControlChange(myControlChange);
  usbMIDI.setHandleProgramChange(myProgramChange);

  mainMixer.gain(0, .3);
  mainMixer.gain(1, .3);
  mainMixer.gain(2, .3);
  mainMixer.gain(3, .3);
}


void loop() {
  // init the sequencer when everything is ready
  usbMIDI.read(MIDI_CHANNEL_RECEIVE);
  // bassFilter.frequency(current_freq);
  // current_freq += 0.01;
  // Serial.println(current_freq);
}
