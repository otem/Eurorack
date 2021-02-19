#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSineModulated HHSineMod1;     //xy=182.85719299316406,302.00002670288086
AudioSynthWaveformSineModulated HHSineMod2;     //xy=206.85719299316406,354.00002670288086
AudioSynthWaveformSineModulated snareFM1;       //xy=253.28572845458984,696.8571624755859
AudioSynthNoiseWhite     snareNoise;     //xy=282.8571472167969,848.1428852081299
AudioEffectEnvelope      HHModEnv;       //xy=360.85719299316406,352.00002670288086
AudioSynthWaveformSineModulated snareFM2;       //xy=386.28572845458984,758.8571624755859
AudioSynthWaveformDc     kickDCClick;    //xy=407.0000686645508,135.57143545150757
AudioSynthWaveformDc     kickDCSwoop;    //xy=433.0000686645508,84.57143545150757
AudioSynthNoiseWhite     HHNoise;        //xy=435.85719299316406,462.00002670288086
AudioEffectEnvelope      snareNoiseEnv;  //xy=511.8571472167969,837.1428852081299
AudioSynthWaveformSineModulated HHSineCarrier;  //xy=519.8571929931641,352.00002670288086
AudioEffectEnvelope      snareFMEnv;     //xy=537.2857284545898,775.8571624755859
AudioEffectEnvelope      kickClickEnv;   //xy=567.0000686645508,135.57143545150757
AudioEffectEnvelope      HHModAMpEnv;    //xy=568.8571929931641,400.00002670288086
AudioEffectEnvelope      HHnoiseEnv;     //xy=579.8571929931641,462.00002670288086
AudioEffectEnvelope      kickSwoopEnv;   //xy=593.0000686645508,84.57143545150757
AudioSynthWaveformSineModulated snareClickCarrier; //xy=593.2857284545898,684.8571624755859
AudioEffectEnvelope      snareClickEnv;  //xy=626.2857284545898,638.8571624755859
AudioFilterStateVariable snareNoiseHPF;  //xy=695.8571472167969,838.1428852081299
AudioSynthWaveformSineModulated snareBody;      //xy=698.2857284545898,774.8571624755859
AudioMixer4              HHMixer;        //xy=745.8571929931641,473.00002670288086
AudioMixer4              kickModMixer;   //xy=767.0000686645508,107.57143545150757
AudioFilterStateVariable snareClickFilter; //xy=808.0000228881836,661.0000057220459
AudioMixer4              snareMixer;     //xy=894.2857284545898,783.8571624755859
AudioFilterStateVariable HHfilter;       //xy=911.8571929931641,422.00002670288086
AudioSynthWaveformSineModulated kickSine;       //xy=917.2857971191406,108.85714721679688
AudioFilterStateVariable finalSnareFilter; //xy=1068.8572235107422,672.0000286102295
AudioEffectEnvelope      snareAmpEnv;    //xy=1068.8572235107422,784.0000286102295
AudioAnalyzePeak         snarePeak;      //xy=1124.8572235107422,734.0000286102295
AudioEffectEnvelope      kickAmpEnv;     //xy=1147.0000343322754,190.28571891784668
AudioEffectEnvelope      HHAmpEnv;       //xy=1164.8571472167969,454.42857360839844
AudioAnalyzePeak         HHPeak;         //xy=1209.8571472167969,398.42857360839844
AudioAnalyzePeak         kickPeak;       //xy=1305.0000343322754,154.28571891784668
AudioPlayMemory          playMemHH;       //xy=1304.2858505249023,859.9999523162842
AudioPlayMemory          playMemKick;       //xy=1305.7143363952637,818.571455001831
AudioPlayMemory          playMemSnare;       //xy=1311.4285507202148,904.2857131958008
AudioMixer4              sampleMixer;         //xy=1488.5714378356934,854.2856903076172
AudioMixer4              drumVoiceMixer; //xy=1534.8571701049805,686.2856941223145
AudioEffectWaveshaper    waveshaper;     //xy=1693.1428833007812,536.2857313156128
AudioMixer4              driveMixer;     //xy=1823.1428451538086,631.4285945892334
AudioOutputAnalog        dac1;           //xy=1977.7142715454102,640.7142925262451
AudioConnection          patchCord1(HHSineMod1, HHSineMod2);
AudioConnection          patchCord2(HHSineMod2, HHModEnv);
AudioConnection          patchCord3(snareFM1, snareFM2);
AudioConnection          patchCord4(snareNoise, snareNoiseEnv);
AudioConnection          patchCord5(HHModEnv, HHSineCarrier);
AudioConnection          patchCord6(snareFM2, snareFMEnv);
AudioConnection          patchCord7(kickDCClick, kickClickEnv);
AudioConnection          patchCord8(kickDCSwoop, kickSwoopEnv);
AudioConnection          patchCord9(HHNoise, HHnoiseEnv);
AudioConnection          patchCord10(snareNoiseEnv, 0, snareNoiseHPF, 0);
AudioConnection          patchCord11(HHSineCarrier, HHModAMpEnv);
AudioConnection          patchCord12(snareFMEnv, snareBody);
AudioConnection          patchCord13(kickClickEnv, 0, kickModMixer, 1);
AudioConnection          patchCord14(HHModAMpEnv, 0, HHMixer, 0);
AudioConnection          patchCord15(HHModAMpEnv, 0, HHfilter, 1);
AudioConnection          patchCord16(HHnoiseEnv, 0, HHMixer, 1);
AudioConnection          patchCord17(kickSwoopEnv, 0, kickModMixer, 0);
AudioConnection          patchCord18(snareClickCarrier, snareClickEnv);
AudioConnection          patchCord19(snareClickEnv, snareClickCarrier);
AudioConnection          patchCord20(snareClickEnv, 0, snareClickFilter, 0);
AudioConnection          patchCord21(snareNoiseHPF, 2, snareMixer, 2);
AudioConnection          patchCord22(snareBody, 0, snareMixer, 1);
AudioConnection          patchCord23(HHMixer, 0, HHfilter, 0);
AudioConnection          patchCord24(kickModMixer, kickSine);
AudioConnection          patchCord25(snareClickFilter, 1, snareMixer, 0);
AudioConnection          patchCord26(snareMixer, snareAmpEnv);
AudioConnection          patchCord27(HHfilter, 2, HHAmpEnv, 0);
AudioConnection          patchCord28(kickSine, kickAmpEnv);
AudioConnection          patchCord29(finalSnareFilter, 2, drumVoiceMixer, 2);
AudioConnection          patchCord30(snareAmpEnv, snarePeak);
AudioConnection          patchCord31(snareAmpEnv, 0, finalSnareFilter, 0);
AudioConnection          patchCord32(kickAmpEnv, 0, drumVoiceMixer, 0);
AudioConnection          patchCord33(kickAmpEnv, kickPeak);
AudioConnection          patchCord34(HHAmpEnv, HHPeak);
AudioConnection          patchCord35(HHAmpEnv, 0, drumVoiceMixer, 1);
AudioConnection          patchCord36(playMemHH, 0, sampleMixer, 1);
AudioConnection          patchCord37(playMemKick, 0, sampleMixer, 0);
AudioConnection          patchCord38(playMemSnare, 0, sampleMixer, 2);
AudioConnection          patchCord39(sampleMixer, 0, drumVoiceMixer, 3);
AudioConnection          patchCord40(drumVoiceMixer, waveshaper);
AudioConnection          patchCord41(drumVoiceMixer, 0, driveMixer, 1);
AudioConnection          patchCord42(waveshaper, 0, driveMixer, 0);
AudioConnection          patchCord43(driveMixer, dac1);
// GUItool: end automatically generated code



#include "AudioSampleKick.h"
#include "AudioSampleHh.h"
#include "AudioSampleSnare.h"






elapsedMillis printTime;

#include <MIDI.h>
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
int midiChannel = 5;

#include <ResponsiveAnalogRead.h>
ResponsiveAnalogRead pots[7] = {
  //pots
  ResponsiveAnalogRead (A0, true),
  ResponsiveAnalogRead (A1, true),
  ResponsiveAnalogRead (A2, true),
  ResponsiveAnalogRead (A3, true),
  ResponsiveAnalogRead (A4, true),
  ResponsiveAnalogRead (A5, true),
  ResponsiveAnalogRead (A6, true),
};

//test cv responsive?
ResponsiveAnalogRead pitchCV(A9, true);
float pitchVal;

int cvInputs[7] = {
  A7,A8,A9,A17,A18,A19,A20
};
float rawCvVals[7];
float scaledCvVals[7];

#include <Bounce.h>
Bounce gateIn[3] = {
  Bounce(2,5),
  Bounce(3,5),
  Bounce(4,5),
};
bool btnDown;

int kickPitch = 50;
int kickDecay = 300;
int kickPitchCV;
int kickDecayCV;
int kickPitchSum;
int kickDecaySum;

int HHPitch = 100;
int HHDecay = 50;
int HHPitchCV;
int HHDecayCV;
int HHPitchSum;
int HHDecaySum;

int snarePitch = 100;
int snareDecay = 50;
int snarePitchCV;
int snareDecayCV;
int snarePitchSum;
int snareDecaySum;

float velocities[3] = {1,1,1};
float sampVelocities[3] = {0,0,0};

float punchVal[3] = {1,1,1};

float driveMix;
float driveMixMod;

bool firstRun = true;;

float WaveShapeArray[17] = {
  -0.588,
  -0.579,
  -0.549,
  -0.320,
  -0.488,
  -0.228,
  -0.122,
  -0.396,
  0,
  0.122,
  0.320,
  0.396,
  0.228,
  0.549,
  0.488,
  0.588,
  0.579,
};


void setup() {

  MIDI.begin(midiChannel);

  analogWriteResolution(12);

  dac1.analogReference(EXTERNAL);

  AudioMemory(48);
  //kick////////////////////////////////////
  kickSine.frequency(10);
  kickSine.mod_index(16383.75);

  kickAmpEnv.attack(1);
  kickAmpEnv.sustain(0);
  kickAmpEnv.decay(250);
  kickAmpEnv.release(1);

  kickClickEnv.attack(1);
  kickClickEnv.sustain(0);
  kickClickEnv.decay(10);
  kickClickEnv.release(1);

  kickSwoopEnv.attack(1);
  kickSwoopEnv.sustain(0);
  kickSwoopEnv.decay(150);
  kickSwoopEnv.release(1);

  kickDCClick.amplitude(0.04);
  kickDCSwoop.amplitude(0.01);

  //snare////////////////////////////////////
  snareAmpEnv.attack(1);
  snareAmpEnv.sustain(0);
  snareAmpEnv.decay(100);
  snareAmpEnv.release(1);

  snareNoiseEnv.delay(10);
  snareNoiseEnv.attack(150);
  snareNoiseEnv.sustain(1);
  snareNoiseEnv.release(1);



  snareBody.mod_index(65535);
  snareBody.frequency(50);
  snareNoise.amplitude(1);

  snareNoiseHPF.frequency(1000);;

  snareClickCarrier.mod_index(65535);
  snareClickCarrier.frequency(1500);
  snareClickEnv.attack(0);
  snareClickEnv.sustain(0);
  snareClickEnv.decay(500);
  snareClickEnv.release(1);
  snareClickFilter.frequency(1500);
  snareClickFilter.resonance(5);

  snareFM1.mod_index(65535);
  snareFM1.frequency(1500);
  snareFM2.mod_index(65535);
  snareFM2.frequency(400);

  snareFMEnv.attack(0);
  snareFMEnv.sustain(0);
  snareFMEnv.decay(50);
  snareFMEnv.release(1);

  finalSnareFilter.frequency(100);
  finalSnareFilter.resonance(1);
  finalSnareFilter.octaveControl(7);

  snareMixer.gain(0,0.5);
  snareMixer.gain(1,0.5);
  snareMixer.gain(2,0.3);


  //HiHat////////////////////////////////////
  HHModAMpEnv.attack(1);
  HHModAMpEnv.decay(50);
  HHModAMpEnv.sustain(0);
  HHModAMpEnv.release(10);

  HHSineCarrier.amplitude(0.75);
  HHSineCarrier.mod_index(65535);
  HHSineCarrier.frequency(4000);

  HHSineMod1.frequency(2500);
  HHSineMod2.mod_index(65535);
  HHSineMod2.frequency(1250);

  HHModEnv.attack(0);
  HHModEnv.decay(50);
  HHModEnv.sustain(0);
  HHModEnv.release(10);

  HHfilter.frequency(2000);
  HHNoise.amplitude(0.5);

  HHnoiseEnv.attack(2);
  HHnoiseEnv.decay(250);
  HHnoiseEnv.sustain(0);
  HHnoiseEnv.release(10);

  HHMixer.gain(0,0.3);
  HHMixer.gain(1,0.5);

  HHAmpEnv.attack(1);
  HHAmpEnv.decay(300);
  HHAmpEnv.sustain(0);
  HHAmpEnv.release(10);


  //VoiceMix////////////////////////////////////
  // drumVoiceMixer.gain(0,1);
  // drumVoiceMixer.gain(1,1);
  // drumVoiceMixer.gain(2,0.5);
  //

  //SampleMixer
  sampleMixer.gain(0,0);
  sampleMixer.gain(1,0);
  sampleMixer.gain(2,0);
  waveshaper.shape(WaveShapeArray, 17);

  //gate in pins
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  //btn in
  pinMode(8,INPUT_PULLUP);

  analogReadResolution(12);
  for (size_t i = 0; i < 7; i++) {
    pots[i].setAnalogResolution(4096);
    pots[i].setActivityThreshold(50);
    pots[i].enableEdgeSnap();
  }
}

void loop() {

  int type, note, velocity;
  if (MIDI.read()) {
    type = MIDI.getType();
    switch (type) {
      case midi::NoteOn:
        note = MIDI.getData1();
        velocity = MIDI.getData2();

        triggerDrum(note%3);
        velocities[note%3] = float(velocity)/127;
        // Serial.println("Engine: "+String(note%3)+" velocity: "+String(velocities[note%3]));
        break;
      case 176:
        //MIDI Mod
        if(MIDI.getData1() == 1) {
          driveMix = float(MIDI.getData2())/127;
          Serial.println(driveMix);
        }
        break;
    }
  }

  //leds pins 9,10,25 PWM
  if (kickPeak.available()) {
    analogWrite(9,255*kickPeak.read());
  }
  if (HHPeak.available()) {
    analogWrite(10,255*HHPeak.read());
  }
  if (snarePeak.available()) {
    analogWrite(25,255*snarePeak.read());
  }

  btnDown = !digitalRead(8);



  for (size_t i = 0; i < 3; i++) {
    gateIn[i].update();
    if (gateIn[i].fallingEdge()) {
      triggerDrum(i);
    }
  }

  for (size_t i = 0; i < 7; i++) {
    pots[i].update();
    if(pots[i].hasChanged() || firstRun) {
      if (i<7) {
        switch (i) {
          case 0:
            driveMix = pots[i].getValue();
            driveMix /= 4095;
            break;
          case 1:
            if(btnDown){
              velocities[2] = (float)pots[i].getValue() / 4095;
            }else{
              snarePitch = pots[i].getValue()/10;
            }
            break;
          case 2:
            if(btnDown){
              velocities[1] = (float)pots[i].getValue() / 4095;
            }else{
              HHPitch = pots[i].getValue();
            }
            break;
          case 3:
            if(btnDown){
              velocities[0] = (float)pots[i].getValue() / 4095;
            }else{
              kickPitch = pots[i].getValue()/15;
            }
            break;
          case 4:
            if(btnDown){
              sampVelocities[2] = (float)pots[i].getValue()/4095;
            }else{
              snareDecay = pots[i].getValue()/4;
            }
            break;
          case 5:
            if(btnDown){
              sampVelocities[1] = (float)pots[i].getValue()/4095;
            }else{
              HHDecay = pots[i].getValue()/3;
            }
            break;
          case 6:
            if(btnDown){
              sampVelocities[0] = (float)pots[i].getValue()/4095;
            }else{
              kickDecay = pots[i].getValue()/3;
            }
            break;
        }
      }
    }
  }

  for (size_t i = 0; i < 7; i++) {
    rawCvVals[i] = analogRead(cvInputs[i]);
    switch (i) {
      case 2:
        kickPitchCV = map(rawCvVals[i],1250,3670,118,-118);
        break;
      case 3:
        kickDecayCV = map(rawCvVals[i],1250,3670,682,-682);
        break;
      case 4:
        HHPitchCV = map(rawCvVals[i],1250,3670,2047,-2047);
        break;
      case 1:
        HHDecayCV = map(rawCvVals[i],1250,3670,682,-682);
        break;
      case 0:
        snarePitchCV = map(rawCvVals[i],1250,3670,204,-204);
        break;
      case 5:
        snareDecayCV =  map(rawCvVals[i],1250,3670,511,-511);
        break;
      case 6:
        float tmpMix;
        tmpMix = mapfloat(rawCvVals[i],1250,3670,0.75,-0.75);
        driveMixMod = tmpMix; //overdirve
        break;
    }
  }



  AudioNoInterrupts();
  //KICK
  kickPitchSum = kickPitch + kickPitchCV;
  kickPitchSum = constrain(kickPitchSum,0,546);

  kickDecaySum = kickDecay + kickDecayCV;
  kickDecaySum = constrain(kickDecaySum,0,2730);

  kickSine.frequency(kickPitchSum);
  kickAmpEnv.decay(kickDecaySum);
  kickSwoopEnv.decay(kickDecaySum/4);
  kickDCClick.amplitude(0.05);

  //============================================================================

  //HH
  HHPitchSum = HHPitch + HHPitchCV;
  HHPitchSum = constrain(HHPitchSum,0,8190);

  HHDecaySum = HHDecay + HHDecayCV;
  HHDecaySum = constrain(HHDecaySum,0,2730);

  HHAmpEnv.decay( HHDecaySum );
  HHnoiseEnv.decay( HHDecaySum );
  HHModEnv.decay( HHDecaySum / 2);
  HHModAMpEnv.decay(HHDecaySum);

  HHSineCarrier.frequency( HHPitchSum/2 );
  HHSineMod1.frequency( HHPitchSum * 2 );
  HHSineMod2.frequency( HHPitchSum );

  //============================================================================

  //snare
  snarePitchSum = snarePitch + snarePitchCV;
  snarePitchSum = constrain(snarePitchSum,0,800);

  snareDecaySum = snareDecay + snareDecayCV;
  snareDecaySum = constrain(snareDecaySum,0, 2046);

  snareAmpEnv.decay( snareDecaySum );
  snareFMEnv.decay( snareDecaySum / 12 );

  snareBody.frequency( snarePitchSum );
  snareFM1.frequency( snarePitchSum*5 );
  snareFM2.frequency( snarePitchSum*15 );

  snareNoiseHPF.frequency( snarePitchSum*1.5 );

  //============================================================================

  //drive
  float driveMixFinal = driveMix+driveMixMod;
  driveMixFinal = constrain(driveMixFinal,0,1);

  driveMixer.gain(0,driveMixFinal);
  driveMixer.gain(1,1-(driveMixFinal));

  //============================================================================

  //final mix
  drumVoiceMixer.gain(0,velocities[0]);
  drumVoiceMixer.gain(1,velocities[1]);
  drumVoiceMixer.gain(2,velocities[2]);

  sampleMixer.gain(0,sampVelocities[0]);
  sampleMixer.gain(1,sampVelocities[1]);
  sampleMixer.gain(2,sampVelocities[2]);

  AudioInterrupts();

  firstRun = false;
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void triggerDrum(int drumVoice){

  switch (drumVoice) {
    case 0:
      if (kickAmpEnv.isActive()) {
        kickClickEnv.noteOff();
        kickSwoopEnv.noteOff();
        kickAmpEnv.noteOff();
        delay(5);
      }
      // Serial.println("kick Pitch: "+String(kickPitch)+" | kick Pitch CV: "+String(kickPitchCV)+" | Total: "+String(kickPitchSum));
      // Serial.println("kick Decay: "+String(kickDecay)+" | kick Decay CV: "+String(kickDecayCV)+" | Total: "+String(kickDecaySum));
      kickSine.phase(0);
      kickClickEnv.noteOn();
      kickSwoopEnv.noteOn();
      kickAmpEnv.noteOn();
      playMemKick.play(AudioSampleKick);
      break;
    case 1:
      // Serial.println("HH Pitch: "+String(HHPitch)+" | HH Pitch CV: "+String(HHPitchCV)+" | Total: "+String(HHPitchSum));
      // Serial.println("HH Decay: "+String(HHDecay)+" | HH Decay CV: "+String(HHDecayCV)+" | Total: "+String(HHDecaySum));
      HHnoiseEnv.noteOn();
      HHAmpEnv.noteOn();
      HHModAMpEnv.noteOn();
      HHModEnv.noteOn();
      playMemHH.play(AudioSampleHh);
      break;
    case 2:
      // Serial.println("snare Pitch: "+String(snarePitch)+" | snare Pitch CV: "+String(snarePitchCV)+" | Total: "+String(snarePitchSum));
      // Serial.println("snare Decay: "+String(snareDecay)+" | snare Decay CV: "+String(snareDecayCV)+" | Total: "+String(snareDecaySum));
      snareBody.phase(0);
      snareFM1.phase(180);
      snareFM2.phase(180);
      snareFMEnv.noteOn();
      snareClickEnv.noteOn();
      snareNoiseEnv.noteOn();
      snareAmpEnv.noteOn();
      playMemSnare.play(AudioSampleSnare);
    break;
  }
}
