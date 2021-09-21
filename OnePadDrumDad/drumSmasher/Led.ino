void processLEDS(){
  if (displayMillis > 50) {

    display.display();
    displayMillis = 0;
    if (deleting) {
      recBlink = !recBlink;
      digitalWrite(recLedPin,recBlink);
    }else if(recording){
      digitalWrite(recLedPin,HIGH);
    }else if (!recording){
      digitalWrite(recLedPin,LOW);
    }
  }
  for (size_t i = 0; i < 6; i++) {
    if (repeatDown) {
      mcp.digitalWrite(i+8, LOW);
      mcp.digitalWrite(repeatIndex+8, HIGH);
    }else if (bankDown) {
      mcp.digitalWrite(i+8, LOW);
      mcp.digitalWrite(bankIndex+8, HIGH);
    }else if (partDown) {
      mcp.digitalWrite(i+8, LOW);
      mcp.digitalWrite(partIndex+8, HIGH);
    }else if (hitBlinks[i] < 50) {
      mcp.digitalWrite(i+8, LOW);
    }else{
      mcp.digitalWrite(i+8, !mutes[bankIndex][i]);
    }
  }
}
