#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   lfo;            //xy=146.91668701171875,383.83331298828125
AudioSynthWaveformModulated saw3;           //xy=441.25001525878906,173.66663599014282
AudioSynthWaveformModulated saw7; //xy=440.4999694824219,390.5000214576721
AudioSynthWaveformModulated saw4;           //xy=441.25001525878906,207.66663599014282
AudioSynthWaveformModulated saw8; //xy=440.4999694824219,424.5000214576721
AudioSynthWaveformModulated saw11; //xy=440,562
AudioSynthWaveformModulated saw12; //xy=440,596
AudioSynthWaveformModulated saw5; //xy=441.4999694824219,320.5000305175781
AudioSynthWaveformModulated saw2;           //xy=442.25001525878906,139.66663599014282
AudioSynthWaveformModulated saw6; //xy=441.4999694824219,356.5000214576721
AudioSynthWaveformModulated saw9; //xy=441,492.000009059906
AudioSynthWaveformModulated saw10; //xy=441,528
AudioSynthWaveformModulated saw1;           //xy=444.25001525878906,104.66663599014282
AudioMixer4              mixer1;         //xy=576.2500457763672,154.33330154418945
AudioMixer4              mixer2; //xy=575.5,371.16668701171875
AudioMixer4              mixer3; //xy=575.0000305175781,542.6666655540466
AudioMixer4              finalMixer;         //xy=758,380
AudioFilterStateVariable filter1;        //xy=924,390
AudioOutputAnalog        dac;            //xy=1069.08349609375,387.8332824707031
AudioConnection          patchCord1(saw3, 0, mixer1, 2);
AudioConnection          patchCord2(saw7, 0, mixer2, 2);
AudioConnection          patchCord3(saw4, 0, mixer1, 3);
AudioConnection          patchCord4(saw8, 0, mixer2, 3);
AudioConnection          patchCord5(saw11, 0, mixer3, 2);
AudioConnection          patchCord6(saw12, 0, mixer3, 3);
AudioConnection          patchCord7(saw5, 0, mixer2, 0);
AudioConnection          patchCord8(saw2, 0, mixer1, 1);
AudioConnection          patchCord9(saw6, 0, mixer2, 1);
AudioConnection          patchCord10(saw9, 0, mixer3, 0);
AudioConnection          patchCord11(saw10, 0, mixer3, 1);
AudioConnection          patchCord12(saw1, 0, mixer1, 0);
AudioConnection          patchCord13(mixer1, 0, finalMixer, 0);
AudioConnection          patchCord14(mixer2, 0, finalMixer, 1);
AudioConnection          patchCord15(mixer3, 0, finalMixer, 2);
AudioConnection          patchCord16(finalMixer, 0, filter1, 0);
AudioConnection          patchCord17(filter1, 0, dac, 0);
// GUItool: end automatically generated code







//Teensy 3.2
#include <Bounce.h>
#include <ResponsiveAnalogRead.h>
#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
int midiChannel = 5;
bool voiceUsed[3];
int voiceNum;


AudioSynthWaveformModulated *sawsA[4] = {
	&saw1,&saw2,&saw3,&saw4
};
AudioSynthWaveformModulated *sawsB[4] = {
	&saw5,&saw6,&saw7,&saw8
};
AudioSynthWaveformModulated *sawsC[4] = {
	&saw9,&saw10,&saw11,&saw12
};

ResponsiveAnalogRead analogPots[4] = {
	ResponsiveAnalogRead (A2, true),
	ResponsiveAnalogRead (A1, true),
	ResponsiveAnalogRead (A0, true),
	ResponsiveAnalogRead (A3, true),
};
int btnPin = 12;
Bounce btn(btnPin,50);

float nominal_frequency = 220;
float nominal_freq[3] = {220,220,220};
float pitchMod;
int pitchCVPins[3] = {A5,A4,A7};
float pitchCV[3];
float octaves[3];
float frequency[3];
int cvPin = A6;
float filterCV;
float filterFreq;
float res;
float totalFilterFreq;

int waveIndex;
int waveIndexHold;
short waveShapes[4] = {
	WAVEFORM_SAWTOOTH,
	WAVEFORM_SQUARE,
	WAVEFORM_TRIANGLE,
	WAVEFORM_SINE,
};

float detune = 1;
float tuneThird;
float tuneThirdDown;
float tuneFifth;
float tuneSeventh;

float lfoFreq;
float lfoAmp;

elapsedMillis pTime;

bool firstRun = true;



void setup() {
	Serial.begin(9600);
	// while(!Serial){}
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
	pinMode(btnPin,INPUT_PULLUP);

	MIDI.begin(midiChannel);
	MIDI.setHandleNoteOn(OnNoteOn);
	MIDI.setHandleNoteOff(OnNoteOff);
	//Pots
	for(int i=0; i<4; i++){
		analogPots[i].setAnalogResolution(1023);
		analogPots[i].setActivityThreshold(1);
		analogPots[i].enableEdgeSnap();
	}

	AudioMemory(12);
	dac.analogReference(EXTERNAL);
	for(int i=0; i<4; i++){
		sawsA[i]->begin(0.083,0,WAVEFORM_SAWTOOTH);
		sawsA[i]->frequencyModulation(0.2);
		sawsB[i]->begin(0.083,0,WAVEFORM_SAWTOOTH);
		sawsB[i]->frequencyModulation(0.2);
		sawsC[i]->begin(0.083,0,WAVEFORM_SAWTOOTH);
		sawsC[i]->frequencyModulation(0.2);
	}
	Serial.println("Super Saw Begin");

	// finalMixer.gain(0,0);
	// finalMixer.gain(1,0);
	// finalMixer.gain(2,1);

}

void loop() {
	MIDI.read(midiChannel);
	//btn
	btn.update();
	if (btn.fallingEdge()) {
		waveIndexHold = waveIndex;
		waveIndex++;
		waveIndex = waveIndex > 3 ? 0 : waveIndex;
		for(int i=0; i<4; i++){
			sawsA[i]->begin(waveShapes[waveIndex]);
			sawsB[i]->begin(waveShapes[waveIndex]);
			sawsC[i]->begin(waveShapes[waveIndex]);
		}
		Serial.println(waveIndex);
	}
	//Pots
	for(int i=0; i<4; i++){
		analogPots[i].update();
		if(analogPots[i].hasChanged() || firstRun){
			if(i==0){
				pitchMod = ((float)analogPots[i].getValue() / 4092)+.0001;
				Serial.println(pitchMod);
			}else if(i==1){
				detune = (float)analogPots[i].getValue();
				tuneThird = map(detune, 0, 1023, 1, 1.25);
				tuneThirdDown = map(detune, 0, 1023, 1, 0.75);
				tuneFifth = map(detune, 0, 1023, 1, 1.5); //unused
				tuneSeventh = map(detune, 0, 1023, 1, 1.685); //unused
				//Serial.println("detune: "+String(detune)+" | Third: "+String(tuneThird)+" | ThirdDown: "+String(tuneThirdDown)+" | Fifth: "+String(tuneFifth));
			}else if(i==2){
				filterFreq = analogPots[i].getValue()*17;
				//Serial.println("CUT: "+String(filterFreq));
			}else{
				res = map((float)analogPots[i].getValue(),0,1023,0.85,5.0);
				float attenMix = map((float)analogPots[i].getValue(),0,1023,1,0.3);
				Serial.println(attenMix);
				finalMixer.gain(0,attenMix);
				finalMixer.gain(1,attenMix);
				finalMixer.gain(2,attenMix);


				//Serial.println("RES: "+String(res));
			}
		}
	}

	filterCV = map((float)analogRead(cvPin),17,970,8500,-8500);

	//Pitch CV
	for (size_t i = 0; i < 3; i++) {
		pitchCV[i] = 1023 - analogRead(pitchCVPins[i]);
		pitchCV[i] = constrain(pitchCV[i], 0, 1023);
		if (i==0) {
			octaves[i] = pitchCV[i] / 145;
		}else if(i==1){
			octaves[i] = pitchCV[i] / 147;
		}else if(i==2){
			octaves[i] = pitchCV[i] / 148;
		}
		// octaves[i] = pitchCV[i] / 145;
		frequency[i] = nominal_freq[i] * exp2f(octaves[i]);
	}


	AudioNoInterrupts();
	totalFilterFreq = filterFreq+filterCV;
	totalFilterFreq = totalFilterFreq > 17000 ? 17000 : totalFilterFreq;

	filter1.frequency(totalFilterFreq);
	filter1.resonance(res);

	for(int i=0; i<4; i++){
		//other options:
		// * tuneFifth
		// * tuneSeventh
		if(i==0){
			sawsA[i]->frequency(frequency[0]*tuneThirdDown*pitchMod);
			sawsB[i]->frequency(frequency[1]*tuneThirdDown*pitchMod);
			sawsC[i]->frequency(frequency[2]*tuneThirdDown*pitchMod);
		}else if(i==2){
			sawsA[i]->frequency(frequency[0]*tuneThird*pitchMod);
			sawsB[i]->frequency(frequency[1]*tuneThird*pitchMod);
			sawsC[i]->frequency(frequency[2]*tuneThird*pitchMod);
		}else{
			sawsA[i]->frequency(frequency[0]*pitchMod);
			sawsB[i]->frequency(frequency[1]*pitchMod);
			sawsC[i]->frequency(frequency[2]*pitchMod);
		}
	}
	AudioInterrupts();

	if(pTime > 2000){
		// Serial.println("CV: "+String(totalFilterFreq));
		//Serial.println("CV: "+String(filterCV));
		//Serial.println("PitchCV: "+String(pitchCV)+" | Nominal: "+String(nominal_frequency)+" | Freq: "+String(frequency));
		Serial.println("1 pitchCV: "+String(pitchCV[0])+" freq: "+String(frequency[0]));
		Serial.println("2 pitchCV: "+String(pitchCV[1])+" freq: "+String(frequency[1]));
		Serial.println("3 pitchCV: "+String(pitchCV[2])+" freq: "+String(frequency[2]));
		Serial.println();


		pTime = 0;
	}

	firstRun = false;
}

void OnNoteOn(byte channel, byte note, byte velocity){
	//Serial.println("Ch: "+String(channel)+" Note: "+String(note)+" Vel: "+String(velocity)+" Voice#: "+String(voiceNum));
	float freq = 440.0 * powf(2.0, (float)(note - 69) * 0.08333333);
	if (voiceNum == 0) { //set all three voices to freq
		nominal_freq[0] = freq;
		nominal_freq[1] = freq;
		nominal_freq[2] = freq;
	}else if(voiceNum == 1){ //set voice 2 & 3
		nominal_freq[1] = freq;
		nominal_freq[2] = freq;
	}else if(voiceNum == 2){//set voice 3
		nominal_freq[2] = freq;
	}
	voiceNum++;
	// Serial.println("1: "+String(frequency[0])+" Note: "+String(note)+" Voice#: "+String(voiceNum)+" pitchCV: "+String(pitchCV[0])+" freq: "+String(frequency[0]));
	// Serial.println("2: "+String(frequency[1])+" Note: "+String(note)+" Voice#: "+String(voiceNum)+" pitchCV: "+String(pitchCV[1])+" freq: "+String(frequency[1]));
	// Serial.println("3: "+String(frequency[2])+" Note: "+String(note)+" Voice#: "+String(voiceNum)+" pitchCV: "+String(pitchCV[2])+" freq: "+String(frequency[2]));

}
void OnNoteOff(byte channel, byte note, byte velocity){
	voiceNum--;
}
