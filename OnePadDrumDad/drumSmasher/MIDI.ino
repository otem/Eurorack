// void RealTimeSystem(byte realtimebyte) {
//   switch (realtimebyte) {
//     case 250:
//       // set last step of all banks/parts
//       for (size_t b = 0; b < 3; b++) {
//         for (size_t p = 0; p < 6; p++) {
//           stepIndex[b][p] = lastStep[b][p];
//           evenPulse[b][p] = false;
//         }
//       }
//       clock = true;
//       clockChange = true;
//       break;
//     case 248:
//       if (clock) {
//         clockCnt++;
//         clockChange = true;
//       }
//       break;
//     case 252:
//       clock = false;
//       clockCnt = 0;
//       break;
//   }
// }
// void processMIDI(){
//   if (MIDI1.read(1)) {                    // Is there a MIDI message incoming ?
//    byte type = MIDI1.getType();
//    // Serial.println(type);
//    switch (type) {
//       case 250:
//         MIDIclockStart();
//         break;
//       case 248:
//         MIDIclockContinue();
//         break;
//       case 252:
//         MIDIclockStop();
//         break;
//       default:
//         break;
//     }
//   }
// }
// void OnNoteOn(byte channel, byte note, byte velocity){
//   midiInUse = true;
// }
// void OnNoteOff(byte channel, byte note, byte velocity){
//   midiInUse = false;
// }

void MIDIclockStart(){
  for (size_t b = 0; b < 3; b++) {
    for (size_t p = 0; p < 6; p++) {
      stepIndex[b][p] = lastStep[b][p];
      evenPulse[b][p] = false;
    }
  }
  clock = true;
  clockChange = true;
}
void MIDIclockContinue(){
  if (clock) {
    clockCnt++;
    clockChange = true;
  }
}
void MIDIclockStop(){
  clock = false;
  clockCnt = 0;
}
