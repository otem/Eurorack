#include <Arduino.h>
#include <Audio.h>
#include <TeensyVariablePlayback.h>
#include <MIDI.h>
#include "flashloader.h"
#include <ResponsiveAnalogRead.h>
#include "effect_platervbstereo.h"

// GUItool: begin automatically generated code
AudioSynthWaveformDc     dc1;            //xy=190.77771949768066,175.77776718139648
AudioSynthWaveformDc     dc2; //xy=191.66666221618652,262.3333110809326
AudioSynthWaveformDc     dc5; //xy=192.66666221618652,531.3333110809326
AudioSynthWaveformDc     dc6; //xy=193.55560493469238,617.8888549804688
AudioSynthWaveformDc     dc3; //xy=194.66666221618652,342.3333110809326
AudioSynthWaveformDc     dc4; //xy=195.55560493469238,428.88885498046875
AudioPlayArrayResmp          playMem1;       //xy=198.11105728149414,213.44445610046387
AudioSynthWaveformDc     dc7; //xy=196.55560493469238,697.8888549804688
AudioPlayArrayResmp          playMem2; //xy=199,300
AudioSynthWaveformDc     dc8; //xy=197.44454765319824,784.4443988800049
AudioPlayArrayResmp          playMem5; //xy=200,569
AudioPlayArrayResmp          playMem6;  //xy=200.88894271850586,655.5555438995361
AudioPlayArrayResmp          playMem3; //xy=202,380
AudioPlayArrayResmp          playMem4; //xy=202.88894271850586,466.55554389953613
AudioPlayArrayResmp          playMem7; //xy=203.88894271850586,735.5555438995361
AudioPlayArrayResmp          playMem8; //xy=204.77788543701172,822.1110877990723
AudioEffectMultiply      multiply1;      //xy=443.1110534667969,200.44444274902344
AudioEffectMultiply      multiply2; //xy=443.99999618530273,286.99998664855957
AudioEffectMultiply      multiply5; //xy=444.99999618530273,555.9999866485596
AudioEffectMultiply      multiply6; //xy=445.8889389038086,642.5555305480957
AudioEffectMultiply      multiply3; //xy=446.99999618530273,366.99998664855957
AudioEffectMultiply      multiply4; //xy=447.8889389038086,453.5555305480957
AudioEffectMultiply      multiply7; //xy=448.8889389038086,722.5555305480957
AudioEffectMultiply      multiply8; //xy=449.77788162231445,809.1110744476318
AudioMixer4              mixer2;         //xy=772.5555419921875,594.5555419921875
AudioMixer4              mixer1;         //xy=776,343
AudioSynthWaveformDc     filterDC;            //xy=945.9999961853027,547.9999942779541
AudioMixer4              mixer3;         //xy=950.9999961853027,471.9999942779541
AudioFilterLadder        ladder1;        //xy=1097.9999961853027,538.9999942779541
AudioEffectPlateReverb       verb1;       //xy=1198.9999961853027,681.9999942779541
AudioMixer4              verbMixer;         //xy=1333.9999961853027,557.9999942779541
AudioOutputI2S           i2s1;           //xy=1537.9999961853027,538.9999942779541
AudioConnection          patchCord1(dc1, 0, multiply1, 0);
AudioConnection          patchCord2(dc2, 0, multiply2, 0);
AudioConnection          patchCord3(dc5, 0, multiply5, 0);
AudioConnection          patchCord4(dc6, 0, multiply6, 0);
AudioConnection          patchCord5(dc3, 0, multiply3, 0);
AudioConnection          patchCord6(dc4, 0, multiply4, 0);
AudioConnection          patchCord7(playMem1, 0, multiply1, 1);
AudioConnection          patchCord8(dc7, 0, multiply7, 0);
AudioConnection          patchCord9(playMem2, 0, multiply2, 1);
AudioConnection          patchCord10(dc8, 0, multiply8, 0);
AudioConnection          patchCord11(playMem5, 0, multiply5, 1);
AudioConnection          patchCord12(playMem6, 0, multiply6, 1);
AudioConnection          patchCord13(playMem3, 0, multiply3, 1);
AudioConnection          patchCord14(playMem4, 0, multiply4, 1);
AudioConnection          patchCord15(playMem7, 0, multiply7, 1);
AudioConnection          patchCord16(playMem8, 0, multiply8, 1);
AudioConnection          patchCord17(multiply1, 0, mixer1, 0);
AudioConnection          patchCord18(multiply2, 0, mixer1, 1);
AudioConnection          patchCord19(multiply5, 0, mixer2, 0);
AudioConnection          patchCord20(multiply6, 0, mixer2, 1);
AudioConnection          patchCord21(multiply3, 0, mixer1, 2);
AudioConnection          patchCord22(multiply4, 0, mixer1, 3);
AudioConnection          patchCord23(multiply7, 0, mixer2, 2);
AudioConnection          patchCord24(multiply8, 0, mixer2, 3);
AudioConnection          patchCord25(mixer2, 0, mixer3, 1);
AudioConnection          patchCord26(mixer1, 0, mixer3, 0);
AudioConnection          patchCord27(filterDC, 0, ladder1, 1);
AudioConnection          patchCord28(mixer3, 0, ladder1, 0);
AudioConnection          patchCord29(ladder1, 0, verbMixer, 0);
AudioConnection          patchCord30(ladder1, 0, verb1, 0);
AudioConnection          patchCord31(ladder1, 0, verb1, 1);
AudioConnection          patchCord32(verb1, 0, verbMixer, 1);
AudioConnection          patchCord33(verb1, 1, verbMixer, 2);
AudioConnection          patchCord34(verbMixer, 0, i2s1, 0);
// GUItool: end automatically generated code

AudioPlayArrayResmp *sampPlayers[8] = {
  &playMem1,&playMem2,&playMem3,&playMem4,
  &playMem5,&playMem6,&playMem7,&playMem8,
};
AudioSynthWaveformDc *envs[8] = {
  &dc1,&dc2,&dc3,&dc4,
  &dc5,&dc6,&dc7,&dc8,
};

ResponsiveAnalogRead analogs[4] = {
  ResponsiveAnalogRead (A10, true),
  ResponsiveAnalogRead (A11, true),
  ResponsiveAnalogRead (A12, true),
  ResponsiveAnalogRead (A13, true),
};

ResponsiveAnalogRead setCV(A2, true);

int cvPins[3] = {A0,A1,A3};


newdigate::audiosample *samps[128];

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

int dirCount;
int fileCount;
String dirName;
// int dirItter[16] = {
//   0,8,16,24,32,40,48,56,
//   64,72,80,88,96,104,112,120,
// };

int setIndex;
int setIndexCV;
int setIndexCC;
int voiceIndex;
float globalSamplePitch = 1;
unsigned int globalDecayTime = 500;
float filterFreq;
float filterFreqCC;
float verbMixCC;
float pitchCV;
float decayCV;
float filterCV;

int folderTotal;

float voiceDecayTime[8];
float voiceSamplepitch[8];

elapsedMillis printTime;

newdigate::flashloader loader;

void setup(){
  // Serial.begin(9600);
  //  while (!Serial) {
  //   delay(10);
  // }

  while (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("No SD Card");
    delay(500);
  }

  AudioMemory(94);
  dc1.amplitude(1);

  for (size_t i = 0; i < 8; i++) {
    if (i<4) {
      mixer1.gain(i,0.5);
      mixer2.gain(i,0.5);
      analogs[i].setActivityThreshold(5);
      analogs[i].enableEdgeSnap();
    }
    sampPlayers[i]->enableInterpolation(true);
  }

  ladder1.resonance(0);
  ladder1.octaveControl(7);
  ladder1.inputDrive(1);
  filterDC.amplitude(1);
  verb1.size(1);     // max reverb length
  verb1.lowpass(1);  // sets the reverb master lowpass filter
  verb1.lodamp(0.1);   // amount of low end loss in the reverb tail
  verb1.hidamp(0.1);   // amount of treble loss in the reverb tail
  verb1.diffusion(1);  // 1.0 is the detault setting, lower it to create more "echoey" reverb


  verbMixer.gain(0,1);
  verbMixer.gain(1,0);
  verbMixer.gain(2,0);


  usbMIDI.setHandleNoteOn(handleNoteOn);
  usbMIDI.setHandleControlChange(myControlChange);
  MIDI.begin(11);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleControlChange(myControlChange);



  File root = SD.open("samples");
  getDirectories(root, 0);

  folderTotal = dirCount-1;

  setCV.enableEdgeSnap();
  setCV.setActivityThreshold(600/dirCount);


}
void loop(){
  usbMIDI.read();
  MIDI.read(11);
  for (size_t i = 0; i < 4; i++) {
    analogs[i].update();
    if(analogs[i].hasChanged()) {
      // Serial.println("Analog "+String(i)+": "+String(analogs[i].getValue()));
      if(i==0){
        setIndex = map(analogs[i].getValue(), 0,1023,0,folderTotal);
        // Serial.println("Set: "+String(setIndex));
      }else if(i==1){
        globalSamplePitch = map(float(analogs[i].getValue()),0,1023,-2,2);
        // Serial.println("pitch: "+String(globalSamplePitch));
      }else if(i==2){
        // volume = map(float(analogs[i].getValue()),0,1023,0,1);
        filterFreq = map(float(analogs[i].getValue()),0,1023,-1,1);

        // Serial.println("Volume: "+String(volume));
      }else if(i==3){
        globalDecayTime = float(analogs[i].getValue());
        // Serial.println("globalDecayTime: "+String(globalDecayTime));
      }
    }
  }

  for (size_t i = 0; i < 8; i++) {
    sampPlayers[i]->setPlaybackRate(globalSamplePitch+pitchCV+voiceSamplepitch[i]);
  }


  //cv
  for (size_t i = 0; i < 4; i++) {
    if (i==0) {
      pitchCV = map(float(analogRead(cvPins[i])),20,1000,2,-2);
    }else if(i==1){
      decayCV = map(float(analogRead(cvPins[i])),20,1000,512,-512);
    }else if(i==2){
      filterCV = map(float(analogRead(cvPins[i])),20,1000,1,-1);
    }
  }
  setCV.update();
  if (setCV.hasChanged()) {
    setIndexCV = map(setCV.getValue(),215,820,0,folderTotal);
    if (setIndexCV > -1 && setIndexCV <= folderTotal) {
      // Serial.println("SetCV: "+String(setIndexCV));
      setIndex = setIndexCV;
    }
  }
  for (size_t i = 0; i < 8; i++) {
    envs[i]->amplitude(0,globalDecayTime+decayCV+voiceDecayTime[i]);
  }
  filterDC.amplitude(filterFreq+filterCV+filterFreqCC);

  if (printTime > 100) {
    // Serial.println("set raw cv: "+String(analogRead(A2)));
    printTime = 0;
  }



}

void handleNoteOn(uint8_t channel, uint8_t pitch, uint8_t velocity){
  if (pitch < 68 && pitch > 59){
    voiceIndex =  pitch-60;

    if(voiceIndex < 4){
      mixer1.gain(voiceIndex, float(velocity)/127);
    }else{
      mixer2.gain(voiceIndex-4, float(velocity)/127);
    }
    envs[voiceIndex]->amplitude(1);

    int sampleSelect = setIndex*8;

    if (samps[voiceIndex+sampleSelect]) {
      // Serial.println("voice: "+String(voiceIndex)+" | sample: "+String(voiceIndex+sampleSelect));
      sampPlayers[voiceIndex]->playWav(samps[voiceIndex+sampleSelect]->sampledata);
    }
  }
}

void myControlChange(byte channel, byte control, byte value){
  if (control > 0 && control < 9 ) {
    voiceSamplepitch[control-1] = map(float(value),0,127,-2,2);
  }
  if (control > 8 && control < 17 ) {
    voiceDecayTime[control-9] = map(value,0,127,-512,512);
  }

  if (control==17) {
    filterFreqCC = float(value)/63 - 1;
  }

  if (control==18){
    verbMixCC = float(value)/127;
    verbMixer.gain(0,1-verbMixCC);
    verbMixer.gain(1,verbMixCC);
    verbMixer.gain(2,verbMixCC);
  }
  if (control==19) {
    float verbSize = float(value)/127;
    verb1.size(verbSize);
  }
  if (control==20) {
    setIndexCC = map(int(value),0,127,0,folderTotal);
    if (setIndexCC > -1 && setIndexCC <= folderTotal) {
      setIndex = setIndexCC;
      // Serial.println("set index cc: "+String(setIndexCC));
    }
  }
  if (control==50) {
    if (value > 60) {
      filterFreqCC = 0;
      verbMixer.gain(0,1);
      verbMixer.gain(1,0);
      verbMixer.gain(2,0);
      verb1.size(1);
      for (size_t i = 0; i < 8; i++) {
        voiceSamplepitch[i] = 0;
        voiceDecayTime[i] = 0;
      }
    }
  }

}
