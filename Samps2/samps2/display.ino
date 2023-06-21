void displayDirs(){
  display.clearDisplay();

  display.setTextSize(1);
  display.fillRect(0,16,128,48,SSD1306_BLACK);
  display.drawRect(0,16,128,14,SSD1306_WHITE);


  for (size_t i = 0; i < dirCount; i++) {
    display.setCursor(4,i*16+(dirIndex*-16)+20);
    display.print(dirNames[i]);
    if (i==loadedFile) {
      Serial.println("circle?");
      display.fillCircle(120, i*16+(dirIndex*-16)+22,3, SSD1306_WHITE);
    }else{
      display.fillCircle(120, i*16+(dirIndex*-16)+22,3, SSD1306_BLACK);
    }
  }
  displayMode(false);
  displayDirection();
}

void displayDirection(){
  display.fillRect(60,0,68,16,SSD1306_BLACK);
  if (forwardPlay) {
    display.fillRect(80, 6, 6, 3, SSD1306_WHITE);
    display.fillTriangle(86, 12, 86, 2, 91, 7, SSD1306_WHITE);
    display.drawRect(69, 6, 6, 3, SSD1306_WHITE);
    display.drawTriangle(69, 12, 69, 2, 64, 7, SSD1306_WHITE);
    display.drawLine(66,7,70,7,SSD1306_BLACK);
  }else{
    display.drawRect(80, 6, 6, 3, SSD1306_WHITE);
    display.drawTriangle(86, 12, 86, 2, 91, 7, SSD1306_WHITE);
    display.fillRect(69, 6, 6, 3, SSD1306_WHITE);
    display.fillTriangle(69, 12, 69, 2, 64, 7, SSD1306_WHITE);
    display.drawLine(82,7,87,7,SSD1306_BLACK);
  }
  display.display();
}
void displayMode(bool showDisplay){
  display.fillRect(0,0,60,16,SSD1306_BLACK);
  display.setCursor(2,4);
  display.print(playMode == true ? "Poly": "Drum");
  if (showDisplay) {
    display.display();
  }
}
