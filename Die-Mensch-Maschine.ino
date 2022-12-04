#include <uClock.h>
#include <MIDI.h>
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
AudioSynthWaveform padOsc2;            //xy=428.55553817749023,1126.7777938842773
AudioSynthWaveform padOsc3;            //xy=428.5555877685547,1191.22217130661
AudioSynthWaveform padOsc4;            //xy=445.55555725097656,1262.111083984375
AudioSynthWaveform padOsc1;            //xy=448.5556335449219,1067.333339691162
AudioSynthWaveform leadOsc2;           //xy=503.5555419921875,1664.5556640625
AudioSynthWaveform leadOsc1;           //xy=520,1577.5556640625
AudioSynthWaveform bassOsc1;           //xy=599,827.333251953125
AudioSynthWaveform bassOsc2;           //xy=601,884.333251953125
AudioMixer4 padOscMix;                 //xy=640.3333435058594,1143.6666259765625
AudioSynthWaveformSine padLFO2;        //xy=643,1348
AudioSynthWaveformSine padLFO1;        //xy=646,1263
AudioEffectMultiply leadMultiply;      //xy=677.2222518920898,1619.1111946105957
AudioMixer4 bassOscMix;                //xy=785.5,856
AudioSynthWaveformDc dc1;              //xy=787.5,974
AudioEffectDigitalCombine padCombine;  //xy=820,1274
AudioEffectEnvelope leadEnv;           //xy=886.5555419921875,1611.4444580078125
AudioEffectEnvelope bassEnv;           //xy=950.6666259765625,872.6666259765625
AudioEffectEnvelope bassFilterEnv;     //xy=969.5,970
AudioPlayMemory soundKick;             //xy=1002,1393
AudioPlayMemory soundHH;               //xy=1004,1493
AudioPlayMemory soundSnare;            //xy=1005,1432
AudioPlayMemory soundClap;             //xy=1011,1543
AudioFilterStateVariable padFilter;    //xy=1036.5556640625,1200.333251953125
AudioFilterStateVariable bassFilter;   //xy=1117,884
AudioEffectEnvelope padEnv;            //xy=1222,1200
AudioMixer4 drumMixer;                 //xy=1261,1444
AudioAmplifier leadAmp;                //xy=1274.7777099609375,1607
AudioAmplifier bassAmp;                //xy=1344.6666259765625,870.6666259765625
AudioEffectFreeverb padReverb;         //xy=1384,1202
AudioMixer4 mainMixer;                 //xy=1640.8890380859375,1214.22216796875
AudioOutputI2SQuad i2s_quad1;          //xy=1864.6666259765625,1214.6666259765625
AudioConnection patchCord1(padOsc2, 0, padOscMix, 1);
AudioConnection patchCord2(padOsc3, 0, padOscMix, 2);
AudioConnection patchCord3(padOsc4, 0, padOscMix, 3);
AudioConnection patchCord4(padOsc1, 0, padOscMix, 0);
AudioConnection patchCord5(leadOsc2, 0, leadMultiply, 1);
AudioConnection patchCord6(leadOsc1, 0, leadMultiply, 0);
AudioConnection patchCord7(bassOsc1, 0, bassOscMix, 0);
AudioConnection patchCord8(bassOsc2, 0, bassOscMix, 1);
AudioConnection patchCord9(padOscMix, 0, padFilter, 0);
AudioConnection patchCord10(padLFO2, 0, padCombine, 1);
AudioConnection patchCord11(padLFO1, 0, padCombine, 0);
AudioConnection patchCord12(leadMultiply, leadEnv);
AudioConnection patchCord13(bassOscMix, bassEnv);
AudioConnection patchCord14(dc1, bassFilterEnv);
AudioConnection patchCord15(padCombine, 0, padFilter, 1);
AudioConnection patchCord16(leadEnv, leadAmp);
AudioConnection patchCord17(bassEnv, 0, bassFilter, 0);
AudioConnection patchCord18(bassFilterEnv, 0, bassFilter, 1);
AudioConnection patchCord19(soundKick, 0, drumMixer, 0);
AudioConnection patchCord20(soundHH, 0, drumMixer, 2);
AudioConnection patchCord21(soundSnare, 0, drumMixer, 1);
AudioConnection patchCord22(soundClap, 0, drumMixer, 3);
AudioConnection patchCord23(padFilter, 0, padEnv, 0);
AudioConnection patchCord24(bassFilter, 0, bassAmp, 0);
AudioConnection patchCord25(padEnv, padReverb);
AudioConnection patchCord26(drumMixer, 0, mainMixer, 2);
AudioConnection patchCord27(leadAmp, 0, mainMixer, 3);
AudioConnection patchCord28(bassAmp, 0, mainMixer, 0);
AudioConnection patchCord29(padReverb, 0, mainMixer, 1);
AudioConnection patchCord30(mainMixer, 0, i2s_quad1, 1);
AudioConnection patchCord31(mainMixer, 0, i2s_quad1, 3);
AudioConnection patchCord32(mainMixer, 0, i2s_quad1, 0);
AudioConnection patchCord33(mainMixer, 0, i2s_quad1, 2);

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
#define AUDIO_MEM 40
#define DEBUG_PRINT_STEP false
#define BASS_ROOT 33
#define PAD_ROOT 57
#define LEAD_ROOT 45
#define COL_MIN 0
#define COL_MAX 1
#define MAX_STEP 8
#define MAX_BAR 4
#define MAX_PHRASE 2
#define MAX_SEQUENCE_TYPES 30
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
double configData[30][6] = { { 50,200,120,122,124,126 },{ 0,0,0,0,0,0 },{ 0,0,0,0,0,0 },{ 2,500,0,0.2,0.4,0.6 },{ 0,1000,300,80,80,80 },{ 0,1,0,0,0,0 },{ 1,500,433,1,1,1 },{ 0,500,1,1,1,1 },{ 2,5000,1000,1002,1004,1006 },{ 0,1000,600,80,80,80 },{ 0,1,0.8,0,0,0 },{ 1,5000,1800,1,1,1 },{ 0,500,0,1,1,1 },{ 2,500,300,302,304,306 },{ 0,1000,400,80,80,80 },{ 0,1,1,0,0,0 },{ 1,500,120,1,1,1 },{ 0,500,120,1,1,1 },{ 0.7,5,5,4,4,4 },{ 0,10000,400,3000,3000,3000 },{ 0.7,5,0.7,4,4,4 },{ 0,5000,1001,3000,3000,3000 },{ 0,7,0,0,0,0 },{ 0,7,0,0,0,0 },{ 0,7,0,0,0,0 },{ 0,7,0,0,0,0 },{ 0,7,0,0,0,0 },{ 0,7,0,0,0,0 },{ 0,7,0,0,0,0 },{ 0,7,0,0,0,0 } };
int singleSongData[56][5] = { { 1, 4, 3, 24 }, { 1, 4, 3, 24 }, { 1, 4, 3, 25 }, { 1, 5, 3, 25 }, { 1, 5, 19, 24 }, { 1, 5, 20, 24 }, { 1, 5, 20, 24 }, { 1, 5, 21, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 25 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 12, 8, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 14, 4 }, { 14, 4 }, { 14, 4 }, { 14, 4 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 } };

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

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

void setup() {
  Serial.begin(9600);

  Serial.print("Setup!");
  AudioMemory(48);

  // Inits the clock
  uClock.init();

  uClock.setClock16PPQNOutput(onStep16);
  uClock.setTempo(120);
  makeSoundDesign(current_style);

  sgtl5000_1.enable();
  sgtl5000_1.volume(.5);
  sgtl5000_2.enable();

  sgtl5000_2.volume(.5);
  sgtl5000_1.setAddress(LOW);
  sgtl5000_2.setAddress(HIGH);

  setupBass();
  setupPad();
  setupLead();
  setupDrum();

  uClock.start();
  usbMIDI.sendRealTime(usbMIDI.Start);

  usbMIDI.setHandleControlChange(myControlChange);
  usbMIDI.setHandleProgramChange(myProgramChange);

  mainMixer.gain(0, .1);
  mainMixer.gain(1, .1);
  mainMixer.gain(2, .1);
  mainMixer.gain(3, .1);
}

void loop() {
  // init the sequencer when everything is ready
  usbMIDI.read(MIDI_CHANNEL_RECEIVE);
}
