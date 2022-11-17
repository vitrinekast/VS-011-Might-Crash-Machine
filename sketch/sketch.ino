// Acid StepSequencer, a Roland TB303 step sequencer engine clone
// author: midilab contact@midilab.co
// under MIT license
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <uClock.h>


// GUItool: begin automatically generated code
AudioSynthWaveform waveform2;      //xy=183,612
AudioSynthWaveform waveform1;      //xy=192,504
AudioMixer4 mixer1;                //xy=405,611
AudioFilterStateVariable filter1;  //xy=441,537
AudioOutputAnalog dac1;            //xy=705,459
AudioConnection patchCord1(waveform2, 0, mixer1, 1);
AudioConnection patchCord2(waveform1, 0, mixer1, 0);
AudioConnection patchCord3(mixer1, 0, filter1, 0);
AudioConnection patchCord4(filter1, 0, dac1, 0);
// GUItool: end automatically generated code


// Sequencer config
#define STEP_MAX_SIZE 8
#define SYNTH_BASS 0

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
  uint8_t note;
  int8_t length;
} STACK_NOTE_DATA;


// main sequencer data
SEQUENCER_STEP_DATA _sequencer_bass[12];

uint16_t _step_length = STEP_MAX_SIZE;

int size = 0;
int currentStep = 0;
int currentBar = 0;
int currentPhrase = 0;
int maxStep = 4;
int maxBar = 2;
int maxPhrase = 2;



void onClock16PPQN(uint32_t tick) {
  playStep(tick);
  makeStep(tick);
  Serial.println(tick);
}

SEQUENCER_STEP_DATA getASequence(int phrase = 0, int bar = 0, int step = 0, int type = 0) {
  Serial.println("generate a step");
  Serial.print(phrase);
  SEQUENCER_STEP_DATA newStep;
  newStep.note = 5;
  newStep.accent = false;
  newStep.glide = false;
  newStep.rest = false;
  return newStep;
}

void playStep(uint32_t tick) {
}
void makeStep(uint32_t tick) {
  currentStep++;
  Serial.print("SEQ: step. tick: ");
  Serial.print(tick);
  Serial.print(" step: ");
  Serial.print(tick % maxStep);
  Serial.print(" bar: ");
  Serial.println(tick % (maxStep * maxBar));

  if (tick % maxStep == 0) {
    Serial.println("SEQ: Finish bar");
  }

  if (tick % (maxStep * maxBar) == 0) {
    Serial.println("SEQ: Finish phrase");
  }

  if (tick % (maxStep * maxBar * maxPhrase) == 0) {
    Serial.println("SEQ: Finish song");
  }
}


void generateBassSequences(int digit) {
  Serial.print("generate bass: ");
  Serial.println(digit);

  // phrase
  // bar
  // beat
  int totalLength = maxPhrase * maxBar * maxStep;
  Serial.println("Expected steps: ");
  Serial.print(totalLength);

  for (int i = 0; i < totalLength; i++) {
    _sequencer_bass[i] = getASequence(i, i, i, SYNTH_BASS);
  }

  Serial.println("Full bass sequence: ");
  // Serial.print(_sequencer_bass[0]);
}



void generateSequencerData(int digit) {
  Serial.println("generateSequencerData");
  generateBassSequences(digit);
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.clear();
  Serial.println("Hi there!");
  AudioMemory(200);
  waveform1.begin(0.3, 440, WAVEFORM_SINE);
  waveform2.begin(0.3, 440, WAVEFORM_SAWTOOTH);


  uClock.init();
  // Set the callback function for the step sequencer on 16ppqn;
  uClock.setClock16PPQNOutput(onClock16PPQN);
  uClock.setTempo(86);

  // this would be via the number input
  generateSequencerData(1234567);
  // uClock.start();
}

void loop() {


  // // put your main code here, to run repeatedly:
  // // Serial.println(analogRead(0));
  // Serial.print("Pot 1: Freq: ");
  // Serial.print(analogRead(1));
  // Serial.print("Pot 2: Q: ");
  // Serial.print(analogRead(2));

  // Serial.print("CV/oct:  ");
  // Serial.print(analogRead(0));


  // int q = map(analogRead(2), 0, 1024, 0.3, 5);
  // int freq = analogRead(1);
  // filter1.frequency(freq);
  // filter1.resonance(q);


  // Serial.println("");
  // waveform1.frequency(analogRead(0) / 2);
  // waveform2.frequency(analogRead(0));
  // delay(10);
}