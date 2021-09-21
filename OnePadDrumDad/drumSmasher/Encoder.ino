void processEncoder(){
  newPos = myEnc.read();
  newPos /= 4;
  if (newPos != oldPos) {
    if (bankDown) {
      if (oldPos < newPos) {
        noteOffsets[bankIndex] > 8 ? noteOffsets[bankIndex] = 9 : noteOffsets[bankIndex]++;
      }else{
        noteOffsets[bankIndex] < 1 ? noteOffsets[bankIndex] = 0 : noteOffsets[bankIndex]--;
      }
      drawBank();
    }else if (shiftDown) {
      //select clock div for part
      if (oldPos < newPos) {
        clockDivIndex > 3 ? clockDivIndex = 4 : clockDivIndex++;
      }else{
        clockDivIndex < 1 ? clockDivIndex = 0 : clockDivIndex--;
      }
      clockDiv[bankIndex][partIndex] = clockDivVals[clockDivIndex];
      drawBank();
    }else{
      if (encoderDown) {
        //Set last steps
        if (oldPos < newPos) {
          lastStep[bankIndex][partIndex] > 30 ? lastStep[bankIndex][partIndex] = 31 : lastStep[bankIndex][partIndex]++;
        }else{
          lastStep[bankIndex][partIndex] < 1 ? lastStep[bankIndex][partIndex] = 0 : lastStep[bankIndex][partIndex]--;
        }
        drawGrid(lastStep[bankIndex][partIndex]+1);
        // if (oldPos < newPos) {
        //   repeatIndex > 4 ? repeatIndex = 5 : repeatIndex++;
        // }else{
        //   repeatIndex < 1 ? repeatIndex = 0 : repeatIndex--;
        // }
      }else{
        //step select | delete
        if (deleting) {
          steps[bankIndex][partIndex][stepIndex[bankIndex][partIndex]] = 0;
        }
        selectStep(stepIndex[bankIndex][partIndex],true);
        if (oldPos < newPos) {
          if (stepIndex[bankIndex][partIndex] > lastStep[bankIndex][partIndex]-1) {
            stepIndex[bankIndex][partIndex] = lastStep[bankIndex][partIndex];
          }else{
            stepIndex[bankIndex][partIndex]++;
          }
        }else{
          stepIndex[bankIndex][partIndex] < 1 ? stepIndex[bankIndex][partIndex] = 0 : stepIndex[bankIndex][partIndex]--;
        }
        selectStep(stepIndex[bankIndex][partIndex],false);
      }
    }

    oldPos = newPos;

  }
}
