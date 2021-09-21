void peakDetect(int voltage) {
  // "static" variables keep their numbers between each run of this function
  static int state;  // 0=idle, 1=looking for peak, 2=ignore aftershocks
  static int peak;   // remember the highest reading
  static elapsedMillis msec; // timer to end states 1 and 2

  switch (state) {
    // IDLE state: wait for any reading is above threshold.  Do not set
    // the threshold too low.  You don't want to be too sensitive to slight
    // vibration.
    case 0:
      if (voltage > thresholdMin) {
        //Serial.print("begin peak track ");
        //Serial.println(voltage);
        peak = voltage;
        msec = 0;
        state = 1;
      }
      return;

    // Peak Tracking state: capture largest reading
    case 1:
      if (voltage > peak) {
        peak = voltage;
      }
      if (msec >= peakTrackMillis) {
        velocity = map(peak, thresholdMin, 1023, 1, 127);
        Serial.println("velocity: "+String(velocity));
        // usbMIDI.sendNoteOn(noteArray[bankIndex][partIndex]+(6*noteOffsets[bankIndex]), velocity, bankIndex+1);
        if (bankIndex == 0) {
          MIDI1.sendNoteOn(noteArray[bankIndex][partIndex]+(6*noteOffsets[bankIndex]), velocity, bankIndex+9);
        }else if(bankIndex == 1){
          MIDI2.sendNoteOn(noteArray[bankIndex][partIndex]+(6*noteOffsets[bankIndex]), velocity, bankIndex+9);
        }else if(bankIndex == 2){
          MIDI3.sendNoteOn(noteArray[bankIndex][partIndex]+(6*noteOffsets[bankIndex]), velocity, bankIndex+9);
        }
        // Serial.println(noteArray[bankIndex][partIndex]+(6*noteOffsets[bankIndex]));
        // Serial.println("StepChange: "+String(stepChange)+" | Step:"+String(currentStep));
        // Serial.println("hit: "+String(velocity));
        hitBlinks[partIndex] = 0;

        if (recording && clock) {
          if (stepChange < clockQuantVals[clockDivIndex]) { //quantize is variable based on the speed of that part
            steps[bankIndex][partIndex][currentStep] = velocity; //a bit late, 50,40,30,20,10 baed on clock quant
          }else{
            if (currentStep+1 > lastStep[bankIndex][partIndex]) {
              steps[bankIndex][partIndex][0] = velocity; //early but seq about to wrap around so set to step 0
            }else{
              steps[bankIndex][partIndex][currentStep+1] = velocity; //to early so assume next step
            }
            earlyStep[bankIndex][partIndex] = true;
            Serial.println("earlyKick:"+String(earlyStep[0][0]));

          }
        }else if (recording){ //step seq
          selectStep(stepIndex[bankIndex][partIndex],true);
          steps[bankIndex][partIndex][stepIndex[bankIndex][partIndex]] = velocity;
          selectStep(stepIndex[bankIndex][partIndex],false);
        }

        msec = 0;
        state = 2;
      }
      return;

    // Ignore Aftershock state: wait for things to be quiet again.
    default:
      if (voltage > thresholdMin) {
        msec = 0; // keep resetting timer if above threshold
      } else if (msec > aftershockMillis) {
        // usbMIDI.sendNoteOff(partIndex+47, 0, bankIndex+1);
        state = 0; // go back to idle when
      }
  }
}
