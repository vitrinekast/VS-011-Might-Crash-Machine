#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav playSdWav1;     //xy=535,525
AudioSynthWaveform waveform2;  //xy=538,348
AudioSynthWaveform waveform1;  //xy=539,305
AudioSynthWaveform waveform3;  //xy=544,389
AudioSynthWaveform waveform4;  //xy=545,433
AudioOutputI2SQuad i2s_quad2;  //xy=853,339
AudioConnection patchCord1(playSdWav1, 0, i2s_quad2, 1);
AudioConnection patchCord2(playSdWav1, 1, i2s_quad2, 3);
AudioConnection patchCord3(waveform1, 0, i2s_quad2, 0);
AudioConnection patchCord4(waveform3, 0, i2s_quad2, 2);
AudioControlSGTL5000 sgtl5000_1;  //xy=893,614
AudioControlSGTL5000 sgtl5000_2;  //xy=893,684
// GUItool: end automatically generated code

Sd2Card card;
SdVolume volume;
SdFile root;

void setup() {
  AudioMemory(12);
  Serial.begin(9600);
  // Enable the first audio shield, select input, and enable output
  sgtl5000_1.setAddress(LOW);
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.volume(0.5);

  // Enable the second audio shield, select input, and enable output
  sgtl5000_2.setAddress(HIGH);
  sgtl5000_2.enable();
  sgtl5000_2.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_2.volume(0.5);
  waveform1.begin(.1, 440, WAVEFORM_SINE);
  waveform2.begin(.1, 440, WAVEFORM_SQUARE);
  waveform3.begin(.1, 440, WAVEFORM_TRIANGLE);
  waveform4.begin(.1, 440, WAVEFORM_SAWTOOTH);
  

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("oi");
  Serial.print(BUILTIN_SDCARD);

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
   playSdWav1.play("song.wav");
  }

}

// the loop function runs over and over again forever
void loop() {


    if(playSdWav1.isPlaying()) {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else {
      digitalWrite(LED_BUILTIN, LOW);
    }
}