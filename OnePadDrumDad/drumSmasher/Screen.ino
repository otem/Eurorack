void calcPos(int index){
  xStart = (index*16) - 128*(index/8);
  yStart = 16+((index/8)*12);
}

void drawBank(){
  display.setCursor(1, 4);
  display.fillRect(0,0,128,16,SSD1306_WHITE);
  int divPretty = 48/clockDiv[bankIndex][partIndex];
  display.print("MIDI:"+String(bankIndex+1)+String(noteOffsetLetters[noteOffsets[bankIndex]])+" Prt:"+String(partIndex+1)+" X "+String(divPretty));
}

void drawGrid(int lastStep){
  display.fillRect(0,16,128,48,SSD1306_BLACK); //clearGrid

  for (int i = 0; i < lastStep; i++) {
    calcPos(i);//get position on box
    display.drawRect(xStart,yStart,16,12,SSD1306_WHITE);//draw box

    if (steps[bankIndex][partIndex][i] > 0) {
      display.fillCircle(xStart+7, yStart+5, 2, SSD1306_WHITE);
    }
  }
  selectStep(stepIndex[bankIndex][partIndex],false);
}

void selectStep(int index, bool del){

  calcPos(index);
  if (index <= lastStep[bankIndex][partIndex]) {

    display.fillRect(xStart+2, yStart+2, sWidth,sHeight,SSD1306_BLACK); //clear step
    if (!del) {
      // Serial.println("drawStep");
      display.fillRect(xStart+2,yStart+2,sWidth,sHeight,SSD1306_WHITE); //highlight step
    }else{
      // Serial.println("del");
    }

    if (steps[bankIndex][partIndex][index]) { //add dot if hit white/black
      display.fillCircle(xStart+7, yStart+5, 2, del ? SSD1306_WHITE : SSD1306_BLACK);
    }
  }
}
