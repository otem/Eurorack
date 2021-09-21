void processSeq(){

  if (clockChange) {
    for (int b = 0; b < 3; b++) {
      for (int p = 0; p < 6; p++) {

        if (clockCnt%clockDiv[b][p] == 0) {

          if (b==bankIndex && p==partIndex){
            selectStep(stepIndex[b][p],true);
          }

          (stepIndex[b][p])+1 > lastStep[b][p] ? stepIndex[b][p] = 0 : stepIndex[b][p]++;
          if (!repeatDown) {
            buffStepIndex[b][p] = stepIndex[b][p];
          }
          evenPulse[b][p] = !evenPulse[b][p];
          stepChange = 0;

          if (deleting && b==bankIndex && p==partIndex) {
            steps[b][p][stepIndex[b][p]] = 0;
          }

          if (steps[b][p][stepIndex[b][p]] && !mutes[b][p]) {
            if (!earlyStep[b][p]) {
              if (!evenPulse[b][p]){
                swingTimer[b][p] = 0;
                swingSent[b][p] = true;
                shuffledNotes[b][p] = steps[b][p][stepIndex[b][p]];
              }else{
                if (!repeatDown) {
                  // usbMIDI.sendNoteOn(noteArray[b][p]+(6*noteOffsets[b]), steps[b][p][stepIndex[b][p]], b+9);
                  if (b == 0) {
                    MIDI1.sendNoteOn(noteArray[b][p]+(6*noteOffsets[b]), steps[b][p][stepIndex[b][p]], b+9);
                  }else if(b == 1){
                    MIDI2.sendNoteOn(noteArray[b][p]+(6*noteOffsets[b]), steps[b][p][stepIndex[b][p]], b+9);
                  }else if(b == 2){
                    MIDI3.sendNoteOn(noteArray[b][p]+(6*noteOffsets[b]), steps[b][p][stepIndex[b][p]], b+9);
                  }
                  // usbMIDI.sendNoteOff(47+p, steps[b][p][stepIndex[b][p]], b+9);
                  // MIDI1.sendNoteOff(47+p, steps[b][p][stepIndex[b][p]], b+9);
                  // MIDI2.sendNoteOff(47+p, steps[b][p][stepIndex[b][p]], b+9);
                  // MIDI3.sendNoteOff(47+p, steps[b][p][stepIndex[b][p]], b+9);

                }
              }
            }
            earlyStep[b][p] = false;
            hitBlinks[p] = 0;
          }

          if (b==bankIndex && p==partIndex){
            currentStep = stepIndex[b][p];
            selectStep(stepIndex[b][p],false);
          }
        }

        if (clockCnt%clockDivVals[repeatIndex] == 0 && repeatDown) {
          // usbMIDI.sendNoteOn(noteArray[b][p], steps[b][p][buffStepIndex[b][p]], b+9);
          // usbMIDI.sendNoteOff(47+p, steps[b][p][buffStepIndex[b][p]], b+9);
          if (b == 0) {
            MIDI1.sendNoteOn(noteArray[b][p]+(6*noteOffsets[b]), steps[b][p][buffStepIndex[b][p]], b+9);
          }else if(b == 1){
            MIDI2.sendNoteOn(noteArray[b][p]+(6*noteOffsets[b]), steps[b][p][buffStepIndex[b][p]], b+9);
          }else if(b == 2){
            MIDI3.sendNoteOn(noteArray[b][p]+(6*noteOffsets[b]), steps[b][p][buffStepIndex[b][p]], b+9);
          }
        }

      }
    }
    clockChange = false;
  }

  for (size_t b = 0; b < 3; b++) {
    for (size_t p = 0; p < 6; p++) {
      if ((swingTimer[b][p] > swingAmt) && swingSent[b][p]) {
        if (!repeatDown) {
          // usbMIDI.sendNoteOn(noteArray[b][p]+(6*noteOffsets[b]), shuffledNotes[b][p], b+9);
          if (b == 0) {
            MIDI1.sendNoteOn(noteArray[b][p]+(6*noteOffsets[b]), shuffledNotes[b][p], b+9);
          }else if(b == 1){
            MIDI2.sendNoteOn(noteArray[b][p]+(6*noteOffsets[b]), shuffledNotes[b][p], b+9);
          }else if(b == 2){
            MIDI3.sendNoteOn(noteArray[b][p]+(6*noteOffsets[b]), shuffledNotes[b][p], b+9);
          }
          // usbMIDI.sendNoteOff(47+p, shuffledNotes[b][p], b+9);
        }

        swingSent[b][p] = false;
      }
    }
  }
}
