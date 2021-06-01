//Teensy 4.0 + audio adapter (Rev D) + W25Q128FV Serial Flash
//You will need to grab the audio expander serial flash code from:
//https://forum.pjrc.com/threads/53213-Audio-Expander-for-Teensy?p=186358&viewfull=1#post186358

//PINS
//Teensy  External Component

// 0      PC900 Pin 4 or 6N138 Pin 6

// 1      EncSwitch
// 2      EncRight
// 3      EncLeft

//OLED
// 8      D/C
// 9      RST
// 11     D1/SDI
// 12     D2/SDO
// 13     D0/SCK
// 14     CS

//Pots
// 15/A1     LFO AMT
// 16/A2     LFO FREQ
// 17/A3     pitch

//Push Button
// 22     FuncBtn



#include <MIDI.h>
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);



#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Audio_expander_serialflash_raw.h>
#include <SFE_MicroOLED.h>
#include <Bounce.h>

#include <Encoder.h>
#include <ResponsiveAnalogRead.h>

#define PIN_RESET 9  // Connect RST to pin 9
#define PIN_DC    8  // Connect DC to pin 8
#define PIN_CS    14 // Connect CS to pin 14
#define DC_JUMPER 0 // Set to either 0 (SPI, default) or 1 (I2C) based on jumper, matching the value of the DC Jumper

#define voices 4

Audio_expander_serialflash_raw  voice[voices];

// GUItool: begin automatically generated code
AudioSynthWaveform       lfo;            //xy=1718.4168090820312,1866.5835642814636
AudioMixer4              mixer1;         //xy=1766.6666564941406,1590.6667022705078
AudioAnalyzePeak         peak1;          //xy=1864.4168968200684,1866.9168982505798
AudioEffectDelay         delay1;         //xy=2027.5000305175781,1757.5000267028809
AudioMixer4              delayMixer;         //xy=2035.0000305175781,1603.7500228881836
AudioFilterStateVariable filter1;        //xy=2263.0832862854004,1597.1667728424072
AudioOutputI2S           audio_out;      //xy=2471.0002822875977,1552.916771888733
AudioEffectFreeverb      freeverb1;      //xy=2313.7500343322754,1481.250020980835
AudioMixer4              verbMixer;         //xy=2396.2500381469727,1543.7500228881836
AudioFilterStateVariable delayFilter;        //xy=2120.0000343322754,1643.7500267028809
AudioAmplifier           amp1;           //xy=1938.7500305175781,1452.500020980835


AudioConnection          patchCord1(voice[0], 0, mixer1, 0);
AudioConnection          patchCord2(voice[1], 0, mixer1, 1);
AudioConnection          patchCord3(voice[2], 0, mixer1, 2);
AudioConnection          patchCord4(voice[3], 0, mixer1, 3);


AudioConnection          patchCord5(lfo, peak1);
AudioConnection          patchCord6(mixer1, amp1);
AudioConnection          patchCord7(amp1, 0, delayMixer, 0);
AudioConnection          patchCord8(delayMixer, delay1);
AudioConnection          patchCord9(delayMixer, freeverb1);
AudioConnection          patchCord10(delayMixer, 0, verbMixer, 1);
AudioConnection          patchCord11(delay1, 0, delayFilter, 0);
AudioConnection          patchCord12(delayFilter, 0, delayMixer, 3);
AudioConnection          patchCord13(freeverb1, 0, verbMixer, 0);
AudioConnection          patchCord14(verbMixer, 0, filter1, 0);
AudioConnection          patchCord15(filter1, 0, audio_out, 0);
AudioConnection          patchCord16(filter1, 0, audio_out, 1);
AudioControlSGTL5000     board;          //xy=2182.25,1919
// GUItool: end automatically generated code











MicroOLED oled(PIN_RESET, PIN_DC, PIN_CS);

const int SDchipSelect = 10;    // Audio Shield has SD card CS on pin 10
const int FlashChipSelect = 6; // digital pin for flash chip CS pin

//Encoder
int encSwPin = 1;
int funcPin = 22;
elapsedMillis funcTm;
Bounce encSw = Bounce(encSwPin,20);
Bounce funcSw = Bounce(funcPin,20);
Encoder myEnc(2, 3);
volatile int newPos;
int oldPos;
int tempPos;
int totalFiles;

bool menuOpen;
int paramCount;
String paramTitles[6] = {
  "Vol/Track","Envelope","LFO","Delay","Reverb","Filter"
};

ResponsiveAnalogRead analogs[3] = {
  ResponsiveAnalogRead (A1, true),
  ResponsiveAnalogRead (A2, true),
  ResponsiveAnalogRead (A3, true),
};

float note_number_to_pitch[128];
int i;
int ii;
bool voiceDots[4];
unsigned long voice_timer[voices];
int key_played_by[voices];
float gain_0 = 1.0 / voices;
float attack_time, decay_time, sustain_value, release_time;
float peakVal;

char *filenames[80];
int fIndex;
int file=0;
unsigned long filesizes[80];
float totalFilesizes;


float detune = 1;
float lfoFreq;
float lfoAmp;
float tmpLfoAmp;
float delayTime;
float delayFeedback;
float filterFreq;
float filterRes;
float verbSize;
float verbMix;
float AmpAmt;
bool tracking;

unsigned long tstMillis;
unsigned long prevTstMillis;

String paramLabels[6][2] = {
  {"Volume","Tracking"},
  {"Attack","Release"},
  {"LFO Amt","LFO Freq"},
  {"Delay Time","Delay Feed"},
  {"Verb Size","Verb Mix"},
  {"Fltr Freq","Fltr Res"},
};




void setup() {
  Serial.begin(9600);
  analogReadResolution(12);
  for (size_t i = 0; i < 3; i++) {
    analogs[i].setAnalogResolution(4096);
    analogs[i].setActivityThreshold(50);
  }

  MIDI.begin(2);

  //ENCODER KNOB+SW
  pinMode(encSwPin, INPUT_PULLUP);
  pinMode(funcPin, INPUT_PULLUP);


  //uncomment these if using Teensy audio shield
  SPI.setSCK(13);  // Audio shield has SCK on pin 13(rev d)
  SPI.setMOSI(11);  // Audio shield has MOSI on pin 11(rev d)

  if (!SerialFlash.begin(FlashChipSelect)) {
    Serial.println("Unable to access SPI Flash chip");
  }

  //I don't know why I had this as an output
  //it completely borks everything
  // pinMode(SDchipSelect,OUTPUT);

  //oled
  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  delay(1000);     // Delay 1000 ms
  oled.clear(PAGE); // Clear the buffer.

  getFilesAndSizes();

  for (i = 0; i < voices; i++) {
    voice[i].set_ADSR(0, 0, .5, 0.2);
    voice_timer[i] = 0;
  }

  // conversion constants
  for (i = 0; i < 128; i++) {
    note_number_to_pitch[i] = pow(2.0, (i - 60.0) / 12.0); // vector for conversion from note number a pitch
  }

  attack_time = 0;
  decay_time = 0;
  sustain_value = 1;
  release_time = .5;


  // AUDIO
  AudioMemory(512);
  board.enable();
  board.volume(1);
  board.lineOutLevel(13);
  //board.adcHighPassFilterDisable();

  mixer1.gain(0, .5);
  mixer1.gain(1, .5);
  mixer1.gain(2, .5);
  mixer1.gain(3, .5);

  lfo.begin(.005,3,WAVEFORM_SINE);
  lfo.offset(-0.5);



  delay1.disable(1);
  delay1.disable(2);
  delay1.disable(3);
  delay1.disable(4);
  delay1.disable(5);
  delay1.disable(6);
  delay1.disable(7);
  delayMixer.gain(3,0);

  delayFilter.frequency(3000);

  filter1.frequency(10000);
  filter1.resonance(.7);

  freeverb1.roomsize(0);
  freeverb1.damping(.8);
  verbMixer.gain(0,0);
  verbMixer.gain(1,1);

  amp1.gain(.5);

  tracking = true;
  //USBMIDI
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);

  fIndex = 0;
  updateScreen(false,"",0);
}

void OnNoteOn(byte channel, byte note, byte velocity) {
  play_note(note, velocity);
}
void OnNoteOff(byte channel, byte note, byte velocity) {
  release_voice(note);
}



void loop() {
  tstMillis = millis();
  if (abs(tstMillis - prevTstMillis) > 3000){
    Serial.println(AudioMemoryUsageMax());
    prevTstMillis = tstMillis;
  }

  usbMIDI.read(2);

  int type, note, velocity, channel;
  if (MIDI.read()) {
    byte type = MIDI.getType();
    switch (type) {
      case midi::NoteOn:
        note = MIDI.getData1();
        velocity = MIDI.getData2();
        channel = MIDI.getChannel();
        if (velocity > 0) {
          play_note(note,velocity);
          Serial.println(String("Note On:  ch=") + channel + ", note=" + note + ", velocity=" + velocity);
        }
        break;
      case midi::NoteOff:
        note = MIDI.getData1();
        release_voice(note);
        break;
      // default:
      //   d1 = MIDI.getData1();
      //   d2 = MIDI.getData2();
        // //Serial.println(String("Message, type=") + type + ", data = " + d1 + " " + d2);
    }
  }




  //Knobs
  for(int i=0; i<3; i++){
    analogs[i].update();
    if(analogs[i].hasChanged()) {
      if (i==0) {
        switch (paramCount) {
          case 0:
            AmpAmt = analogs[i].getValue();
            AmpAmt /= 2047.5;
            amp1.gain(AmpAmt);
            updateScreen(true,paramLabels[paramCount][i],AmpAmt);
          break;

          case 1:
            attack_time = analogs[i].getValue();
            attack_time /= 1023;
            for (size_t i = 0; i < voices; i++) {
              voice[i].set_ADSR(attack_time, decay_time, sustain_value, release_time);
            }
            updateScreen(true,paramLabels[paramCount][i],attack_time);
          break;

          case 2:
            lfoAmp = analogs[i].getValue();
            lfoAmp /= 32736;
            lfo.amplitude(lfoAmp);
            updateScreen(true,paramLabels[paramCount][i],lfoAmp);
          break;

          case 3:
            delayTime = analogs[i].getValue();
            delayTime /= 3;
            delay1.delay(0,delayTime);
            updateScreen(true,paramLabels[paramCount][i],delayTime);
          break;

          case 4:
            verbSize = analogs[i].getValue();
            verbSize /= 4095;
            freeverb1.roomsize(verbSize);
            updateScreen(true,paramLabels[paramCount][i],verbSize);
          break;


          case 5:
            filterFreq = analogs[i].getValue();
            filterFreq *= 2.5;
            filter1.frequency(constrain(filterFreq,20,15000));
            updateScreen(true,paramLabels[paramCount][i],constrain(filterFreq,20,15000));
          break;
        }
      }else if(i==1){
        switch (paramCount) {
          case 0:
            int tmpInt;
            tmpInt = analogs[i].getValue();
            tracking = tmpInt < 2047;
            updateScreen(true,paramLabels[paramCount][i],tracking);
          break;

          case 1:
            release_time = analogs[i].getValue();
            release_time /= 1023;
            for (size_t i = 0; i < voices; i++) {
              voice[i].set_ADSR(attack_time, decay_time, sustain_value, release_time);
            }
            updateScreen(true,paramLabels[paramCount][i],release_time);
          break;

          case 2:
            lfoFreq = analogs[i].getValue();
            lfoFreq /= 512;
            lfo.frequency(lfoFreq);
            updateScreen(true,paramLabels[paramCount][i],lfoFreq);
          break;

          case 3:
            delayFeedback = analogs[i].getValue();
            delayFeedback /= 4095;
            delayMixer.gain(3,delayFeedback);
            updateScreen(true,paramLabels[paramCount][i],delayFeedback);
          break;

          case 4:
            verbMix = analogs[i].getValue();
            verbMix /= 4095;
            verbMixer.gain(0,verbMix);
            verbMixer.gain(1,1-verbMix);
            updateScreen(true,paramLabels[paramCount][i],verbMix);
          break;

          case 5:
            filterRes = analogs[i].getValue();
            filterRes /= 819;
            filterRes += .7;
            filter1.resonance(constrain(filterRes,.7,5));
            updateScreen(true,paramLabels[paramCount][i],constrain(filterRes,.7,5));
          break;
        }
      }else{
        detune = analogs[i].getValue();
        detune = (detune/4095)+1;
        updateScreen(true,"Tune",detune);
      }
    }
  }
  //LFO
  if(peak1.available()){
    peakVal = peak1.read();
  }
  for (i = 0; i < voices; i++){
    voice[i].set_pitch_bend(peakVal+1);
  }
  //func button
  if (funcSw.update() && digitalRead(funcPin) == LOW){
    funcTm  = 0;
    paramCount > 4 ? paramCount = 0 : paramCount++;
    updateScreen(true,paramTitles[paramCount],0);
  }

  //Encoder BTN
  if (encSw.update() && digitalRead(encSwPin) == LOW){
    if (!menuOpen) {
      displayMenu(0);
      menuOpen = true;
      tempPos = oldPos;
      myEnc.write(0);
    }else{
      switch (newPos) {
        case 0:
          copyFromSD();
          break;
        case 1:
          formatFlash();
          break;
        case 2:
          menuOpen = false;
          myEnc.write(tempPos*4);
          fIndex = tempPos;
          updateScreen(false,"",0);
          break;
      }
    }
  }
  //Encoder Rotate
  newPos = myEnc.read();
  newPos /= 4;
  if (menuOpen){
    if(newPos <= -1){
      myEnc.write(0);
    }
    if(newPos >= 3){
      myEnc.write(12);
    }
    newPos = constrain(newPos, 0, 2);
    if (newPos != oldPos) {
      displayMenu(newPos);
      oldPos = newPos;
    }
  }else{
    if(newPos <= -1){
      myEnc.write(0);
    }
    if(newPos >= 64){
      myEnc.write(252);
    }
    newPos = constrain(newPos, 0, 63);
    if (newPos != oldPos) {
      fIndex = newPos;
      updateScreen(false,"",0);
      oldPos = newPos;
    }
  }

}
//OLED
void displayMenu(int menu_option){
  oled.clear(PAGE);
  oled.setFontType(0);

  oled.setCursor(2,2);
  oled.print("SD > Flash");

  oled.setCursor(2,14);
  oled.print("X Flash");

  oled.setCursor(2,26);
  oled.print("Back");

  oled.rect(0, menu_option*12, 64, 12);

  oled.rect(0, 38, 64, 8);
  oled.rectFill(0, 38, (totalFilesizes/1000000)*4, 8);

  oled.display();

}
void updateScreen(bool param, String label, float val){
  if (!menuOpen) {
    //file
    String newName = filenames[fIndex];
    oled.clear(PAGE);
    oled.setCursor(0,0);
    oled.print(fIndex+1);
    oled.setCursor(0,12);
    oled.print(newName.replace(".RAW",""));
    //dots
    for(int i=0; i<4; i++){
      if(voiceDots[i]){
        oled.circleFill((7*i)+40, 4, 2);
      }else{
        oled.circle((7*i)+40, 4, 2);
      }
    }
    //param
    if (param) {
      oled.setCursor(0,24);
      oled.print(label);
      if (label == "Tracking") {
        oled.setCursor(0,36);
        oled.print(val == 0 ? "No" : "Yes");
      }else if (val > 0) {
        oled.setCursor(0,36);
        oled.print(val);
      }
    }
    oled.display();
  }
}

bool isFileNameValid( const char * fileName )
{
  char c;
  while ( (c = *fileName++) )
    if ( c != '.' && !isalnum(c) )
      return false;
  return true;
}
bool compareFiles(File &file, SerialFlashFile &ffile) {
  file.seek(0);
  ffile.seek(0);
  unsigned long count = file.size();
  while (count > 0) {
    char buf1[128], buf2[128];
    unsigned long n = count;
    if (n > 128) n = 128;
    file.read(buf1, n);
    ffile.read(buf2, n);
    if (memcmp(buf1, buf2, n) != 0) return false; // differ
    count = count - n;
  }
  return true;  // all data identical
}
float eraseBytesPerSecond(const unsigned char *id) {
  if (id[0] == 0x20) return 152000.0; // Micron
  if (id[0] == 0x01) return 500000.0; // Spansion
  if (id[0] == 0xEF) return 419430.0; // Winbond
  if (id[0] == 0xC2) return 279620.0; // Macronix
  return 320000.0; // guess?
}

// play note
void play_note(int note_number, float velocity) {
  //Serial.println(note_number_to_pitch[note_number]);
  unsigned long minimum_time = voice_timer[0];
  int i;
  int ii = -1;

  for (i = 0; i < voices; i++) { // first test: if the same key is played we use the same voice
    if (key_played_by[i] == note_number) {
      ii = i;
      break;
    }
  }

  if (ii == -1) // second test choice: look for a voice not busy
  {
    for (i = 0; i < voices; i++)
    {
      if (voice[i].is_playing() == false) {
        ii = i;
        break;
      }
    }
  }

  if (ii == -1) // last test: choose the voice playing for the longest time
  {
    ii = 0;
    for (i = 0; i < voices; i++)
    {
      if (voice_timer[i] < minimum_time ) { // final test choice: look for the voice playing for the longest time
        minimum_time = voice_timer[i];
        ii = i;
      }
    }
  }

  voiceDots[ii] = true;
  key_played_by[ii] = note_number;
  if (filenames[fIndex]){
    if (tracking) {
      voice[ii].play(filenames[fIndex], note_number_to_pitch[note_number]*detune, velocity/127);
    }else{
      fIndex = note_number%totalFiles;
      myEnc.write(fIndex*4);
      voice[ii].play(filenames[fIndex], 1*detune, velocity/127);
    }
  }
  voice_timer[ii] = millis();
  if (funcTm > 2000) {
    updateScreen(false,"",0);
  }
}
// stop note
void release_voice(int note_number) {
  int i;
  for (i = 0; i < 4; i++) {
    if (key_played_by[i] == note_number) {
      voice[i].release_note();
      voiceDots[i] = false;
      if (funcTm > 2000) {
        updateScreen(false,"",0);
      }
      break;
    }
  }
}

void getFilesAndSizes()
{
  oled.clear(PAGE);
  oled.setCursor(0,0);
  oled.print("Get Files");
  oled.display();
  delay(2000);
  SerialFlash.opendir();
  while (1) {
    char filename[64];
    unsigned long filesize;
    if (SerialFlash.readdir(filename, sizeof(filename), filesize)) {
      if(isFileNameValid(filename)){
        filenames[fIndex] = malloc(1 + strlen(filename));
        strcpy(filenames[fIndex], filename);
        filesizes[fIndex] = filesize;
        fIndex++;
        oled.print(".");
        oled.display();
      }
    } else {
      break; // no more files
    }
  }
  totalFiles = fIndex;
  //Serial.println(totalFiles);
  for (int i = 0; i < 64; ++i){
    totalFilesizes += filesizes[i];
  }
  //Serial.println(totalFilesizes);

}

void copyFromSD(){
  if(SD.begin(SDchipSelect)){
    oled.clear(PAGE);
    oled.setCursor(0,0);
    oled.print("Loading");
    oled.display();
    delay(2000);

    File rootdir = SD.open("/");
    while (1) {
      // open a file from the SD card
      Serial.println();
      File f = rootdir.openNextFile();
      if (!f) break;
      const char *filename = f.name();
      Serial.print(filename);
      Serial.print("    ");
      unsigned long length = f.size();
      Serial.println(length);

      if(isFileNameValid(filename)){
        // filenames[fIndex] = malloc(1 + strlen(filename));
        // strcpy(filenames[fIndex], filename);
        // filesizes[fIndex] = length;
        // fIndex++;
        oled.print(".");
        oled.display();

        // check if this file is already on the Flash chip
        if (SerialFlash.exists(filename)) {
          Serial.println("  already exists on the Flash chip");
          SerialFlashFile ff = SerialFlash.open(filename);
          if (ff && ff.size() == f.size()) {
            Serial.println("  size is the same, comparing data...");
            if (compareFiles(f, ff) == true) {
              Serial.println("  files are identical :)");
              f.close();
              ff.close();
              continue;  // advance to next file
            } else {
              Serial.println("  files are different");
            }
          } else {
            Serial.print("  size is different, ");
            Serial.print(ff.size());
            Serial.println(" bytes");
          }
          // delete the copy on the Flash chip, if different
          Serial.println("  delete file from Flash chip");
          SerialFlash.remove(filename);
        }

        // create the file on the Flash chip and copy data
        if (SerialFlash.create(filename, length)) {
          SerialFlashFile ff = SerialFlash.open(filename);
          if (ff) {
            Serial.print("  copying");
            // copy data loop
            unsigned long count = 0;
            unsigned char dotcount = 9;
            while (count < length) {
              char buf[256];
              unsigned int n;
              n = f.read(buf, 256);
              ff.write(buf, n);
              count = count + n;
              Serial.print(".");
              if (++dotcount > 100) {
                 Serial.println();
                 dotcount = 0;
              }
            }
            ff.close();
            if (dotcount > 0) Serial.println();
          } else {
            Serial.println("  error opening freshly created file!");
          }
        } else {
          Serial.println("  unable to create file");
        }
      }

      f.close();
    }
    rootdir.close();
    delay(100);
    Serial.println("Finished All Files");
  }else{
    oled.clear(PAGE);
    oled.setCursor(0,0);
    oled.print("SD Error");
    oled.display();
    Serial.println("SD Error");
    delay(2000);
  }
  fIndex = 0;
  totalFilesizes = 0;
  getFilesAndSizes();
  menuOpen = false;
  myEnc.write(tempPos*4);
  fIndex = tempPos;
  updateScreen(false,"",0);
}
void formatFlash(){
  unsigned long startMillis = millis();
  if (digitalRead(encSwPin) == LOW){
    oled.clear(PAGE);
    oled.setCursor(0,0);
    oled.print("Clearing");
    oled.display();
    delay(2000);
    unsigned char id[5];
    SerialFlash.readID(id);
    unsigned long size = SerialFlash.capacity(id);
    if (size > 0) {
      Serial.print("Flash Memory has ");
      Serial.print(size);
      Serial.println(" bytes.");
      Serial.println("Erasing ALL Flash Memory:");
      Serial.print("  estimated wait: ");
      // int seconds = (float)size / eraseBytesPerSecond(id) + 0.5;
      // Serial.print(seconds);
      Serial.println(" seconds.");
      Serial.println("  Yes, full chip erase is SLOW!");
      SerialFlash.eraseAll();
      unsigned long dotMillis = millis();
      unsigned char dotcount = 0;
      while (SerialFlash.ready() == false) {
        if (millis() - dotMillis > 1000) {
          dotMillis = dotMillis + 1000;
          Serial.print(".");
          oled.print(".");
          oled.display();
          dotcount = dotcount + 1;
          if (dotcount >= 60) {
            Serial.println();
            dotcount = 0;
          }
        }
      }
      if (dotcount > 0) Serial.println();
      Serial.println("Erase completed");
      unsigned long elapsed = millis() - startMillis;
      Serial.print("  actual wait: ");
      Serial.print(elapsed / 1000ul);
      Serial.println(" seconds.");
    }
  }
  for(int i=0; i<64; i++){
    filenames[i] = "";
  }
  totalFilesizes = 0;
  menuOpen = false;
  myEnc.write(tempPos*4);
  fIndex = tempPos;
  updateScreen(false,"",0);
}
