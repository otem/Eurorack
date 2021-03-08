#include <MIDI.h>
#include <ResponsiveAnalogRead.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI1);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI2);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, MIDI3);

int analogPin = A0;
ResponsiveAnalogRead analogPot(analogPin, true);
int offsetIndex;
int offsetValues[4] = {0,16,32,48};

void setup() {
  MIDI1.begin();
  MIDI2.begin();
  MIDI3.begin();
  MIDI1.setHandleNoteOn(OnNoteOn);
  MIDI1.setHandleNoteOff(OnNoteOff);

  analogReadResolution(12);
  analogPot.setAnalogResolution(4096);
  analogPot.setActivityThreshold(50);
  analogPot.enableEdgeSnap();
}

void loop() {
  MIDI1.read(5);
  analogPot.update();
  if(analogPot.hasChanged()) {
    offsetIndex = analogPot.getValue() / 1024;
  }
}

//MIDI1 == STD
//MIDI2 == VOLCA notes = 60,62,64,65,67,69
//MIDI3 == 404
void OnNoteOn(byte channel, byte note, byte velocity){
  // MIDI1.sendNoteOn(note, velocity, 5);
  //STD midi 1 seems to be shorted to the input?
  switch (note) { //volca
    case 47:
      MIDI2.sendNoteOn(60, velocity, 5);
      break;
    case 48:
      MIDI2.sendNoteOn(62, velocity, 5);
      break;
    case 49:
      MIDI2.sendNoteOn(64, velocity, 5);
      break;
    case 50:
      MIDI2.sendNoteOn(65, velocity, 5);
      break;
    case 51:
      MIDI2.sendNoteOn(67, velocity, 5);
      break;
    case 52:
      MIDI2.sendNoteOn(69, velocity, 5);
      break;
  }
  int offsetNote = note+offsetValues[offsetIndex];
  MIDI3.sendNoteOn(offsetNote, velocity, 5); //404

  Serial.println("ON: Note: "+String(note)+" Vel: "+String(velocity)+" Ch: "+String(channel));
}

void OnNoteOff(byte channel, byte note, byte velocity){
  // MIDI1.sendNoteOff(note, velocity, 5);
  //STD midi 1 seems to be shorted to the input?
   switch (note) { //volca
    case 47:
      MIDI2.sendNoteOff(60, velocity, 5);
      break;
    case 48:
      MIDI2.sendNoteOff(62, velocity, 5);
      break;
    case 49:
      MIDI2.sendNoteOff(64, velocity, 5);
      break;
    case 50:
      MIDI2.sendNoteOff(65, velocity, 5);
      break;
    case 51:
      MIDI2.sendNoteOff(67, velocity, 5);
      break;
    case 52:
      MIDI2.sendNoteOff(69, velocity, 5);
      break;
  }
  int offsetNote = note+offsetValues[offsetIndex];
  MIDI3.sendNoteOff(offsetNote, velocity, 5); //404

  Serial.println("OFF: Note: "+String(note)+" Vel: "+String(velocity)+" Ch: "+String(channel));
}
