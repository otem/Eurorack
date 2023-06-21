#include <Arduino.h>
#include <Audio.h>
#include <TeensyVariablePlayback.h>
#include "flashloader.h"
#include <ResponsiveAnalogRead.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Bounce.h>
#include <Encoder.h>
#include <MIDI.h>
#include "effect_platervbstereo.h"

// GUItool: begin automatically generated code
AudioPlayArrayResmp          playMem3;       //xy=269,205
AudioPlayArrayResmp          playMem2;       //xy=270,159
AudioPlayArrayResmp          playMem4;       //xy=274,259
AudioPlayArrayResmp          playMem1;       //xy=279,122
AudioPlayArrayResmp          playMem6;       //xy=284,563
AudioPlayArrayResmp          playMem7;       //xy=284,614
AudioPlayArrayResmp          playMem5;       //xy=293,520
AudioPlayArrayResmp          playMem8;       //xy=295,661
AudioSynthWaveformDc     dc1;            //xy=338,388
AudioEffectMultiply      multiply7;      //xy=544,532
AudioEffectMultiply      multiply6;      //xy=545,486
AudioEffectMultiply      multiply5;      //xy=548,447
AudioEffectMultiply      multiply8;      //xy=548,578
AudioEffectMultiply      multiply3;      //xy=555,266
AudioEffectMultiply      multiply2;      //xy=556,220
AudioEffectMultiply      multiply1;      //xy=559,181
AudioEffectMultiply      multiply4;      //xy=559,312
AudioEffectEnvelope      envelope1;      //xy=755,236
AudioEffectEnvelope      envelope2;      //xy=758,281
AudioEffectEnvelope      envelope3;      //xy=761,327
AudioEffectEnvelope      envelope5;      //xy=766,428
AudioEffectEnvelope      envelope4;      //xy=768,370
AudioEffectEnvelope      envelope6;      //xy=774,474
AudioEffectEnvelope      envelope7;      //xy=778,522
AudioEffectEnvelope      envelope8;      //xy=781,565
AudioMixer4              mixer2;         //xy=947,489
AudioMixer4              mixer1;         //xy=951,307
AudioEffectPlateReverb       verb1;       //xy=1155,565
AudioMixer4              verbMixer;         //xy=1175,437
AudioOutputI2S           i2s1;           //xy=1365,411
AudioConnection          patchCord1(playMem3, 0, multiply3, 1);
AudioConnection          patchCord2(playMem2, 0, multiply2, 1);
AudioConnection          patchCord3(playMem4, 0, multiply4, 1);
AudioConnection          patchCord4(playMem1, 0, multiply1, 1);
AudioConnection          patchCord5(playMem6, 0, multiply6, 1);
AudioConnection          patchCord6(playMem7, 0, multiply7, 1);
AudioConnection          patchCord7(playMem5, 0, multiply5, 1);
AudioConnection          patchCord8(playMem8, 0, multiply8, 1);
AudioConnection          patchCord9(dc1, 0, multiply1, 0);
AudioConnection          patchCord10(dc1, 0, multiply2, 0);
AudioConnection          patchCord11(dc1, 0, multiply3, 0);
AudioConnection          patchCord12(dc1, 0, multiply4, 0);
AudioConnection          patchCord13(dc1, 0, multiply5, 0);
AudioConnection          patchCord14(dc1, 0, multiply6, 0);
AudioConnection          patchCord15(dc1, 0, multiply7, 0);
AudioConnection          patchCord16(dc1, 0, multiply8, 0);
AudioConnection          patchCord17(multiply7, envelope7);
AudioConnection          patchCord18(multiply6, envelope6);
AudioConnection          patchCord19(multiply5, envelope5);
AudioConnection          patchCord20(multiply8, envelope8);
AudioConnection          patchCord21(multiply3, envelope3);
AudioConnection          patchCord22(multiply2, envelope2);
AudioConnection          patchCord23(multiply1, envelope1);
AudioConnection          patchCord24(multiply4, envelope4);
AudioConnection          patchCord25(envelope1, 0, mixer1, 0);
AudioConnection          patchCord26(envelope2, 0, mixer1, 1);
AudioConnection          patchCord27(envelope3, 0, mixer1, 2);
AudioConnection          patchCord28(envelope5, 0, mixer2, 0);
AudioConnection          patchCord29(envelope4, 0, mixer1, 3);
AudioConnection          patchCord30(envelope6, 0, mixer2, 1);
AudioConnection          patchCord31(envelope7, 0, mixer2, 2);
AudioConnection          patchCord32(envelope8, 0, mixer2, 3);
AudioConnection          patchCord33(mixer2, 0, verbMixer, 1);
AudioConnection          patchCord34(mixer2, 0, verb1, 1);
AudioConnection          patchCord35(mixer1, 0, verbMixer, 0);
AudioConnection          patchCord36(mixer1, 0, verb1, 0);
AudioConnection          patchCord37(verb1, 0, verbMixer, 2);
AudioConnection          patchCord38(verb1, 1, verbMixer, 3);
AudioConnection          patchCord39(verbMixer, 0, i2s1, 0);
AudioConnection          patchCord40(verbMixer, 0, i2s1, 1);
// GUItool: end automatically generated code

AudioPlayArrayResmp *sampPlayers[8] = {
  &playMem1,&playMem2,&playMem3,&playMem4,
  &playMem5,&playMem6,&playMem7,&playMem8,
};
AudioEffectEnvelope *envs[8] = {
  &envelope1,&envelope2,&envelope3,&envelope4,
  &envelope5,&envelope6,&envelope7,&envelope8,
};

ResponsiveAnalogRead analogs[4] = {
  ResponsiveAnalogRead (A10, true),
  ResponsiveAnalogRead (A11, true),
  ResponsiveAnalogRead (A12, true),
  ResponsiveAnalogRead (A13, true),
};


float pitchVal = 1;
float fmCV = 1;
float fmAmt = 0;
float fmAmtEXP;
float vca = 0.5;
float verbMix;
float verbSize;


newdigate::audiosample *samps[8];

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

int voiceIndex;
float voiceFreqs[8];
float voiceVeloc[8];
float masterVelocity = 1;
int voiceNotes[8];
elapsedMillis noteTimes[8];
String fileNames[8] = {
  "1.wav","2.wav","3.wav","4.wav",
  "5.wav","6.wav","7.wav","8.wav",
};



#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int dirCount;
int fileCount;
String dirNames[32];
int dirIndex;


Bounce bouncers[4] = {
  Bounce( 2,5 ),
  Bounce( 32,10 ),
  Bounce( 30,5 ),
  Bounce( 31,5 ),


};
Encoder myEncoder(4,3);
volatile int encPos;
int prevEncPos;

bool forwardPlay = true;
bool playMode = true;
int loadedFile = -1;
bool loading;


elapsedMillis printTime;




void setup(){
  // Serial.begin(9600);
  //  while (!Serial) {
  //   delay(10);
  // }
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  while (!SD.begin(10)) { //10 || BUILTIN_SDCARD
    Serial.println("No SD Card");
    display.clearDisplay();
    display.display();
    delay(500);
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextColor(SSD1306_WHITE);
    display.print("No SD Card");
    display.display();
    delay(500);

  }


  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.print("SAMPS 2");
  display.display();
  delay(1000);


  AudioMemory(94);

  newdigate::flashloader loader;
  for (size_t i = 0; i < 8; i++) {
    if (i<4) {
      mixer1.gain(i,0.5);
      mixer2.gain(i,0.5);
      analogs[i].setActivityThreshold(5);
      analogs[i].enableEdgeSnap();
    }

    envs[i]->attack(10);
    envs[i]->hold(0);
    envs[i]->decay(0);
    envs[i]->sustain(1);
    envs[i]->release(1000);
    sampPlayers[i]->enableInterpolation(true);
  }

  verb1.size(1);     // max reverb length
  verb1.lowpass(1);  // sets the reverb master lowpass filter
  verb1.lodamp(0.1);   // amount of low end loss in the reverb tail
  verb1.hidamp(0.1);   // amount of treble loss in the reverb tail
  verb1.diffusion(1);  // 1.0 is the detault setting, lower it to create more "echoey" reverb
  verbMixer.gain(0,1);
  verbMixer.gain(1,1);
  verbMixer.gain(2,0);
  verbMixer.gain(3,0);


  pinMode(2,INPUT_PULLUP);//encoder
  pinMode(30,INPUT_PULLUP);//sw1
  pinMode(31,INPUT_PULLUP);//sw2
  pinMode(32,INPUT);//trig input
  MIDI.begin(2);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleControlChange(myControlChange);


  usbMIDI.setHandleNoteOn(handleNoteOn);
  usbMIDI.setHandleNoteOff(handleNoteOff);
  usbMIDI.setHandleControlChange(myControlChange);


  File root = SD.open("samples");
  getDirectories(root, 0);

  display.clearDisplay();
  display.setTextSize(2);
  displayDirs();
}

void loop(){
  if(!loading){
    usbMIDI.read();
    MIDI.read(2);
  }

  for (size_t i = 0; i < 4; i++) {
    analogs[i].update();
    if(analogs[i].hasChanged()) {
      // Serial.println("Analog "+String(i)+": "+String(analogs[i].getValue()));
      if (i==0) {
        int attackVal = analogs[i].getValue()*2;
        AudioNoInterrupts();
        for (size_t a = 0; a < 8; a++) {
          envs[a]->attack(attackVal);
        }
        AudioInterrupts();
      }
      if (i==1) {
        int decVal = analogs[i].getValue()*2;
        AudioNoInterrupts();
        for (size_t d = 0; d < 8; d++) {
          envs[d]->release(decVal);
        }
        AudioInterrupts();
      }
      if (i==3) {
        pitchVal = map(float(analogs[i].getValue()),0,1023,0.1,1);
      }
      if (i==2) {
        fmAmt = float(analogs[i].getValue())/1023;
        fmAmtEXP = pow(fmAmt,2);
        // Serial.println(fmAmtEXP,6);
        // int pot = (analogRead(potpin)2);

        // mappedpot=map(pot, 0, 255,0,1500);



      }
    }
  }

  fmCV = map(float(analogRead(A14)),0,1000,0.25,-0.25);
  vca = map(float(analogRead(A15)),0,1000,2,0);
  vca = constrain(vca,0,2);
  AudioNoInterrupts();
  dc1.amplitude(vca,5);
  AudioInterrupts();

  if (printTime > 500) {
    // Serial.println("VCA: "+String(vca));
    printTime = 0;
  }







  for (size_t i = 0; i < 4; i++) {
    bouncers[i].update();
    if (bouncers[i].fallingEdge()) {
      if (i==0) {
        loadFiles();
      }else if (i==1){ //trig input
        forwardPlay = true;
        displayDirection();
      }else if(i==2){
        playMode = !playMode;
        displayMode(true);
      }else if(i==3){
        forwardPlay = !forwardPlay;
        displayDirection();
      }
    }
    if (bouncers[i].risingEdge()) {
      if (i==1) {
        forwardPlay = false;
        displayDirection();
      }
    }
  }

  encPos = myEncoder.read();
  encPos /= 2;
  if (prevEncPos != encPos) {
    if (encPos < prevEncPos) {
      dirIndex < 1 ? dirIndex = 0 : dirIndex--;
    }else{
      dirIndex > dirCount-2 ? dirIndex = dirCount-2 : dirIndex++;
    }

    // Serial.println("Dir: "+String(dirIndex));
    // Serial.println("loadedFile: "+String(loadedFile));
    displayDirs();

    prevEncPos = encPos;
  }



  for (size_t i = 0; i < 8; i++) {
    sampPlayers[i]->setPlaybackRate(voiceFreqs[i]*pitchVal*(forwardPlay ? 1 : -1)+(fmCV*fmAmtEXP));
  }
}

float calcFrequency(uint8_t note) {
    float result = 440.0 * powf(2.0, (note-160) / 12.0);
    return result;
}
int findAvailableVoice(){
  for (size_t i = 0; i < 8; i++) {
    if (!envs[i]->isActive()) {
      return i;
    }
  }

  int maxIndex = 0;
  int max = noteTimes[maxIndex];
  for (int i=1; i<8; i++){
    if (max<noteTimes[i]){
      max = noteTimes[i];
      maxIndex = i;
    }
  }
  return maxIndex;

}
void handleNoteOn(uint8_t channel, uint8_t pitch, uint8_t velocity){
    if (playMode) {
      voiceIndex = findAvailableVoice();
    }else{
      voiceIndex = pitch%8;
    }

    // Serial.println(voiceIndex);
    voiceNotes[voiceIndex] = pitch;
    if (playMode) {
      voiceFreqs[voiceIndex] = calcFrequency(pitch);
    }else{
      voiceFreqs[voiceIndex] = 1;
    }
    voiceVeloc[voiceIndex] = float(velocity)/127;
    if (voiceIndex < 4) {
      mixer1.gain(voiceIndex, voiceVeloc[voiceIndex]*masterVelocity);
    }else{
      mixer2.gain(voiceIndex-4, voiceVeloc[voiceIndex]*masterVelocity);
    }

    envs[voiceIndex]->noteOn();
    if (samps[voiceIndex]) {
      sampPlayers[voiceIndex]->playWav(samps[voiceIndex]->sampledata);
    }
    noteTimes[voiceIndex] = 0;

}
void handleNoteOff(uint8_t channel, uint8_t pitch, uint8_t velocity){
    for (size_t i = 0; i < 8; i++) {
      if (voiceNotes[i] == pitch) {
        envs[i]->noteOff();
      }
    }
}

void myControlChange(byte channel, byte control, byte value){
  if (control == 1) {
    if (value > 63) {
      forwardPlay = true;
      displayDirection();
    }else{
      forwardPlay = false;
      displayDirection();;
    }
  }
  if (control == 2) {
    masterVelocity = map(float(value), 0,127, 0, 2);
    Serial.println("masterVelocity: "+String(masterVelocity));
  }
  if (control == 3) {
    verbMix = float(value)/127;
    verbMixer.gain(0,1 - verbMix);
    verbMixer.gain(1,1 - verbMix);
    verbMixer.gain(2,verbMix);
    verbMixer.gain(3,verbMix);
    // Serial.println("verbMix: "+String(verbMix));
  }
  if (control == 4) {
    verbSize = float(value)/127;
    verb1.size(verbSize);
    // Serial.println("verbSize: "+String(verbSize));
  }

}
