#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>
#include <Bounce.h>
#include "Adafruit_MCP23017.h"
#include <Bounce2mcp.h>
#include <MIDI.h>
#include <ResponsiveAnalogRead.h>
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI1);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, MIDI2);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI3);

//mcp
Adafruit_MCP23017 mcp;
BounceMcp * mcpBtns = new BounceMcp[6];

ResponsiveAnalogRead analogs[3] = {
  ResponsiveAnalogRead (A0, true),//thresh
  ResponsiveAnalogRead (A2, true),//swing
  ResponsiveAnalogRead (A3, true),//repeats
};

//encoder
Encoder myEnc(3, 4);
volatile int newPos;
int oldPos;

int bankPin = 5,
    partPin = 6,
    shiftPin = 11,
    recLedPin = 13,
    recPin = 12,
    encPin = 2,
    repeatPin = 7; //on mcp

Bounce btnBounces[3] = {
  Bounce(bankPin,10),
  Bounce(partPin,10),
  Bounce(recPin,10),
};
elapsedMillis recHold;

bool bankDown,partDown,shiftDown,encoderDown,repeatDown;


//Screen
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



int seqStep;
// [bank][part][step]
int steps[3][6][32];
int lastStep[3][6];
int stepIndex[3][6];
bool mutes[3][6];
int bankIndex, partIndex;

int noteArray[3][6] = {
  {47,48,49,50,51,52},
  {60,62,64,65,67,69},//volca
  {47,48,49,50,51,52},
};
int noteOffsets[3];
String noteOffsetLetters[10] = {
  "a","b","c","d","e",
  "f","g","h","i","j"
};

int clockDiv[3][6];
int clockDivVals[5] = {48,24,12,6,3};
int clockDivIndex = 3;
int clockQuantVals[5] = {50,40,30,20,10};
int clockCnt;
bool clock;
bool clockChange;

int yStart, xStart;
int sWidth = 12;
int sHeight = 8;


bool recording;
int velocity;
bool deleting;
bool recBlink;
bool earlyStep[3][6];

int currentStep;
elapsedMillis stepChange;
elapsedMillis displayMillis;
elapsedMillis hitBlinks[6];


int swingAmt;
bool evenPulse[3][6];
elapsedMillis swingTimer[3][6];
bool swingSent[3][6];
int shuffledNotes[3][6];


int buffStepIndex[3][6];
int repeatIndex = 2;


int swingPin = A2;
const int analogPin = A1;
int thresholdMin = 100;  // minimum reading, avoid noise and false starts
const int peakTrackMillis = 5;
const int aftershockMillis = 20; // aftershocks & vibration reject

bool testData;

elapsedMillis i2CTimer;

void setup() {
  testData = false;
  Serial.begin(115200);
  // while(!Serial){}
  MIDI1.begin();
  MIDI2.begin();
  MIDI3.begin();
  MIDI1.setHandleStart(MIDIclockStart);
  MIDI1.setHandleClock(MIDIclockContinue);
  MIDI1.setHandleStop(MIDIclockStop);


  //pots
  for (size_t i = 0; i < 3; i++) {
    // analogs[i].setAnalogResolution(4096);
    analogs[i].setActivityThreshold(24);
    analogs[i].enableEdgeSnap();
  }

  //Btn MCP
  // Wire.setClock(1700000);
  mcp.begin();
  for (int i = 0; i < 6; i++) {
    mcp.pinMode(i, INPUT);
    mcp.pullUp(i, HIGH);
    mcpBtns[i].attach(mcp, i, 5);
    mcp.pinMode(i+8, OUTPUT);
    mcp.digitalWrite(i+8, HIGH);
    delay(100);
  }
  mcp.pinMode(repeatPin, INPUT);
  mcp.pullUp(repeatPin, HIGH);


  //rec led
  pinMode(recLedPin,OUTPUT);
  //btns
  pinMode(bankPin,INPUT_PULLUP);
  pinMode(partPin,INPUT_PULLUP);
  pinMode(shiftPin,INPUT_PULLUP);
  pinMode(recPin,INPUT_PULLUP);
  pinMode(encPin,INPUT_PULLUP);
  //screen
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_BLACK);
  display.setTextSize(1);
  //set last step to 31 for all banks/parts
  for (size_t b = 0; b < 3; b++) {
    for (size_t p = 0; p < 6; p++) {
      lastStep[b][p] = 31;
      clockDiv[b][p] = 6;
      mutes[b][p] = false;
    }
  }
  drawBank();

  //build grid animation
  for (size_t i = 0; i < 32; i++) {
    drawGrid(i+1);
    display.display();
  }

  // usbMIDI.setHandleRealTimeSystem(RealTimeSystem);


  //test data
  if (testData) {
    steps[0][0][0] = 127;
    lastStep[0][0] = 15;
    clockDiv[0][0] = 6;
    steps[1][0][0] = 127;
    lastStep[1][0] = 15;
    clockDiv[1][0] = 6;
    steps[2][0][0] = 127;
    lastStep[2][0] = 15;
    clockDiv[2][0] = 6;

    for (size_t i = 0; i < 16; i++) {
      // if(i%2 == 0) steps[0][1][i] = 63;
      steps[0][1][i] = 63;
      steps[1][1][i] = 63;
      steps[2][1][i] = 63;
    }
    lastStep[0][1] = 15;
    clockDiv[0][1] = 6;
    lastStep[1][1] = 15;
    clockDiv[1][1] = 6;
    lastStep[2][1] = 15;
    clockDiv[2][1] = 6;

    steps[0][2][8] = 127;
    lastStep[0][2] = 15;
    clockDiv[0][2] = 6;
    steps[1][2][8] = 127;
    lastStep[1][2] = 15;
    clockDiv[1][2] = 6;
    steps[2][2][8] = 127;
    lastStep[2][2] = 15;
    clockDiv[2][2] = 6;
  }

}

void loop() {
  MIDI1.read();
  //pots
  for (size_t i = 0; i < 3; i++) {
    analogs[i].update();
    if(analogs[i].hasChanged()){
      if (i==0) {
        thresholdMin = float(analogs[i].getValue()) / 3;
        // Serial.println("thresholdMin: "+String(thresholdMin));
      }else if(i==1){
        swingAmt = float(analogs[i].getValue()) / 8;
        // Serial.println("swing: "+String(swingAmt));
      }else if(i==2){
        repeatIndex = float(analogs[i].getValue()) / 255;
        // Serial.println("repeats: "+String(repeatIndex));
      }
    }
  }

  // thresholdMin = analogRead(A0) / 3;//trimpot
  // repeatIndex = analogRead(A3) / 255;
  // swingAmt = analogRead(A2) / 8;
  int piezo = analogRead(analogPin);

  peakDetect(piezo);
  processEncoder();
  processSeq();
  if (i2CTimer > 10) {
    /* code */
    processButtons();
    processLEDS();
    i2CTimer = 0;
  }

}
