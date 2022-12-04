#include <uClock.h>
#include <MIDI.h>
#include "AudioSampleKick.h"  // http://www.freesound.org/people/DWSD/sounds/171104/
#include "AudioSampleSnare.h"        // http://www.freesound.org/people/KEVOY/sounds/82583/
#include "AudioSampleTomtom.h"       // http://www.freesound.org/people/zgump/sounds/86334/
#include "AudioSampleHihat.h"        // http://www.freesound.org/people/mhc/sounds/102790/
#include "AudioSampleGong.h"         // http://www.freesound.org/people/juskiddink/sounds/86773/
#include "AudioSampleCashregister.h" // http://www.freesound.org/people/kiddpark/sounds/201159/
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


// GUItool: begin automatically generated code
AudioSynthWaveform       padOsc2;      //xy=255.55553817749023,987.7777938842773
AudioSynthWaveform       padOsc3;      //xy=255.5555877685547,1052.22217130661
AudioSynthWaveform       padOsc4;      //xy=272.55555725097656,1123.111083984375
AudioSynthWaveform       padOsc1;      //xy=275.5556335449219,928.3333396911621
AudioSynthNoisePink      padNoise;          //xy=335.00012969970703,1213.333339691162
AudioSynthWaveform       leadOsc2;      //xy=415.555547926161,1563.5556051466199
AudioSynthWaveform       leadOsc1;      //xy=429.99999237060547,1483.5556051466199
AudioMixer4              padOscMix;         //xy=463.3333549499512,1061.6666870117188
AudioSynthWaveform       bassOsc1;       //xy=524.9999847412109,808.3332672119141
AudioSynthWaveform       bassOsc2;       //xy=531.9999847412109,862.3332672119141
AudioSynthWavetable      wavetable1;     //xy=629,946
AudioMixer4              padNoiseMix;         //xy=642,1102
AudioSynthWaveformSine   sine3;          //xy=643,1348
AudioSynthWaveformSine   padFilterLFO;          //xy=646,1263
AudioEffectMultiply      leadMultiply;      //xy=677.2222518920898,1619.1111946105957
AudioEffectMultiply      bassMultiply;      //xy=762.3332824707031,852.3332862854004
AudioEffectDigitalCombine combine1;       //xy=820,1274
AudioEffectEnvelope      leadEnv;      //xy=905.5555305480957,1552.4444971084595
AudioEffectEnvelope      bassEnv;        //xy=946.6666259765625,872.6666259765625
AudioSynthWaveformSine   bassLFO;          //xy=949.3332557678223,944.9999408721924
AudioFilterStateVariable padFilter;        //xy=1004.5556640625,1175.333251953125
AudioPlayMemory          sound0;         //xy=1018,1745
AudioPlayMemory          sound1;         //xy=1110,1803
AudioPlayMemory          sound2;         //xy=1110,1803
AudioPlayMemory          sound3;         //xy=1110,1803
AudioFilterStateVariable bassFilter;        //xy=1117,884
AudioSynthWaveform       sine1; //xy=1129,1698
AudioEffectEnvelope      padEnv;      //xy=1178,1195
AudioAmplifier           leadAmp;           //xy=1257.7777099609375,1508
AudioAmplifier           bassAmp;           //xy=1271.6666259765625,883.6666259765625
AudioEffectFreeverb      freeverb1;      //xy=1361,1163
AudioMixer4              mixer4;         //xy=1472,1752
AudioMixer4              mixer1;         //xy=1541.8890380859375,1205.22216796875
AudioOutputI2SQuad       i2s_quad1;      //xy=1637.6666259765625,961.6666259765625
AudioConnection          patchCord1(padOsc2, 0, padOscMix, 1);
AudioConnection          patchCord2(padOsc3, 0, padOscMix, 2);
AudioConnection          patchCord3(padOsc4, 0, padOscMix, 3);
AudioConnection          patchCord4(padOsc1, 0, padOscMix, 0);
AudioConnection          patchCord5(padNoise, 0, padNoiseMix, 1);
AudioConnection          patchCord6(leadOsc2, 0, leadMultiply, 1);
AudioConnection          patchCord7(leadOsc1, 0, leadMultiply, 0);
AudioConnection          patchCord8(padOscMix, 0, padNoiseMix, 0);
AudioConnection          patchCord9(bassOsc1, 0, bassMultiply, 0);
AudioConnection          patchCord10(bassOsc2, 0, bassMultiply, 1);
AudioConnection          patchCord11(padNoiseMix, 0, padFilter, 0);
AudioConnection          patchCord12(sine3, 0, combine1, 1);
AudioConnection          patchCord13(padFilterLFO, 0, combine1, 0);
AudioConnection          patchCord14(leadMultiply, leadEnv);
AudioConnection          patchCord15(bassMultiply, bassEnv);
AudioConnection          patchCord16(combine1, 0, padFilter, 1);
AudioConnection          patchCord17(leadEnv, leadAmp);
AudioConnection          patchCord18(bassEnv, 0, bassFilter, 0);
AudioConnection          patchCord19(bassLFO, 0, bassFilter, 1);
AudioConnection          patchCord20(padFilter, 0, padEnv, 0);
AudioConnection          patchCord32(sound0, 0, mixer4, 0);
AudioConnection          patchCord33(sound1, 0, mixer4, 1);
AudioConnection          patchCord34(sound2, 0, mixer4, 2);
AudioConnection          patchCord35(sound3, 0, mixer4, 3);

AudioConnection          patchCord23(bassFilter, 0, bassAmp, 0);
AudioConnection          patchCord24(padEnv, freeverb1);
AudioConnection          patchCord25(leadAmp, 0, mixer1, 3);
AudioConnection          patchCord26(bassAmp, 0, i2s_quad1, 2);
AudioConnection          patchCord27(bassAmp, 0, i2s_quad1, 0);
AudioConnection          patchCord28(freeverb1, 0, mixer1, 0);
AudioConnection          patchCord29(mixer4, 0, mixer1, 1);
AudioConnection          patchCord30(mixer1, 0, i2s_quad1, 1);
AudioConnection          patchCord31(mixer1, 0, i2s_quad1, 3);
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

#define AUDIO_MEM 40

int SCALE_FULL[12] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
int SCALE_MINOR[7] = { 0, 2, 3, 5, 7, 8, 10 };
int ARP_MINOR[4] = { 0, 3, 7, 10 };
int SCALE_MAJOR[8] = { 0, 2, 4, 5, 7, 9, 11 };
float ROOT_NOTES[12] = { 130.8127827, 138.5913155, 146.832384, 155.5634919, 164.8137785, 174.6141157, 184.9972114, 195.997718, 207.6523488, 220, 233.0818808, 246.9416506 };
int ROOT_NOTE = 9;
// TODO fix this.
int BASS_ROOT = 33;
int PAD_ROOT = 57;
int LEAD_ROOT = 45;

#define DEBUG_PRINT_STEP true

// Place these from the spreadsheet https://docs.google.com/spreadsheets/d/1liqxYe1Ht9p84bwuuuADFOiAZGA8TLUPVn47AF2BULI/edit#gid=1079230721
double configData[30][6] = { { 50, 200, 120, 122, 124, 126 }, { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 }, { 2, 500, 2, 4, 6, 8 }, { 0, 1000, 80, 80, 80, 80 }, { 0, 1, 0, 0, 0, 0 }, { 1, 500, 1, 1, 1, 1 }, { 0, 500, 1, 1, 1, 1 }, { 2, 5000, 1000, 1002, 1004, 1006 }, { 0, 1000, 600, 80, 80, 80 }, { 0, 1, 0.8, 0, 0, 0 }, { 1, 5000, 1200, 1, 1, 1 }, { 0, 500, 0, 1, 1, 1 }, { 2, 500, 300, 302, 304, 306 }, { 0, 1000, 400, 80, 80, 80 }, { 0, 1, 1, 0, 0, 0 }, { 1, 500, 120, 1, 1, 1 }, { 0, 500, 120, 1, 1, 1 }, { 0.7, 5, 4, 4, 4, 4 }, { 0, 10000, 3000, 3000, 3000, 3000 }, { 0.7, 5, 0.7, 4, 4, 4 }, { 0, 5000, 1001, 3000, 3000, 3000 }, { 0, 7, 0, 0, 0, 0 }, { 0, 7, 0, 0, 0, 0 }, { 0, 7, 0, 0, 0, 0 }, { 0, 7, 0, 0, 0, 0 }, { 0, 7, 0, 0, 0, 0 }, { 0, 7, 0, 0, 0, 0 }, { 0, 7, 0, 0, 0, 0 }, { 0, 7, 0, 0, 0, 0 } };
int col_min = 0;
int col_max = 1;
int current_style = 2;

int singleSongData[56][5] = { { 1, 4, 3, 24 }, { 1, 4, 3, 24 }, { 1, 4, 3, 25 }, { 1, 5, 3, 25 }, { 1, 5, 19, 24 }, { 1, 5, 20, 24 }, { 1, 5, 20, 24 }, { 1, 5, 21, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 24 }, { 1, 6, 22, 25 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 12, 8, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 1, 7, 22, 26 }, { 14, 4 }, { 14, 4 }, { 14, 4 }, { 14, 4 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 }, { 1, 9, 23, 27 } };
// [bar, instrument]


// [allbarlength][allinstrumentlength]
// https://docs.google.com/spreadsheets/d/1liqxYe1Ht9p84bwuuuADFOiAZGA8TLUPVn47AF2BULI/edit#gid=169379860
// Also get these defined values from sheet
#define MAX_STEP 8
#define MAX_BAR 4
#define MAX_PHRASE 2
#define MAX_SEQUENCE_TYPES 30
#define MIDI_CHANNEL_SENT 1
#define MIDI_CHANNEL_RECEIVE 2

int digit[8] = { 1, 1, 5, 1, 1, 6, 1, 2 };
// int digit[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
bool digitIsParsed = false;

// SEQUENCER_DRUM_DATA _sequencer_drum[MAX_STEP];
SEQUENCER_STEP_DATA all_sequences[MAX_SEQUENCE_TYPES][MAX_STEP];
SEQUENCER_STEP_DATA base_sequence[MAX_STEP];
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
int row_pad_attack = 8;
int row_pad_decay = 9;
int row_pad_sustain = 10;
int row_pad_release = 11;
int row_pad_hold = 12;
int row_lead_attack = 13;
int row_lead_decay = 14;
int row_lead_sustain = 15;
int row_lead_release = 16;
int row_lead_hold = 17;
int row_bass_filter_resonance = 18;
int row_bass_filter_frequency = 19;
int row_pad_filter_resonance = 20;
int row_pad_filter_frequency = 21;
int row_padOsc1Shape = 22;
int row_padOsc2Shape = 23;
int row_padOsc3Shape = 24;
int row_padOsc4Shape = 25;
int row_leadOsc1Shape = 26;
int row_leadOsc2Shape = 27;
int row_bassOsc1Shape = 28;
int row_bassOsc2Shape = 29;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

void setup() {
  Serial.begin(9600);

  Serial.print("Setup!");
  AudioMemory(AUDIO_MEM);

  // Inits the clock
  Serial.println("Setup: Setup the uClock");
  uClock.init();

  uClock.setClock16PPQNOutput(onStep16);

  uClock.setTempo(120);
  Serial.println("Setup: Should call makeSoundDesign after the digit input, but do it rightaway now");
  makeSoundDesign(current_style);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  sgtl5000_2.enable();
  sgtl5000_2.volume(1);
  sgtl5000_1.setAddress(LOW);
  sgtl5000_2.setAddress(HIGH);

  setupBass();
  setupPad();
  // setupLead();
  setupDrum();

  uClock.start();
  usbMIDI.sendRealTime(usbMIDI.Start);

  // Init listening for the keypad
  // sendAllMidiValues();
  usbMIDI.setHandleControlChange(myControlChange);
  usbMIDI.setHandleProgramChange(myProgramChange);
}

void loop() {
  // init the sequencer when everything is ready
  usbMIDI.read(MIDI_CHANNEL_RECEIVE);



  // get any pot changes
  // get any button state changes

  // apply any effect changes to audio channels
  // call monitor function with AudioProcessorUsage(); (if debugging);
}
