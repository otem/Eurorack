void processButtons(){
	bankDown = !digitalRead(bankPin);
	partDown = !digitalRead(partPin);
	shiftDown = !digitalRead(shiftPin);
	encoderDown = !digitalRead(encPin);
	repeatDown = !mcp.digitalRead(repeatPin);

	for (size_t i = 0; i < 3; i++) {
		btnBounces[i].update();
		if (btnBounces[i].fallingEdge()) {
			if (i==0) {
				// bankIndex > 1 ? bankIndex = 0 : bankIndex++;
				// drawBank();
			}else if(i==1){
				partIndex > 4 ? partIndex = 0 : partIndex++;
				drawBank();
				drawGrid(lastStep[bankIndex][partIndex]+1);
			}else{
				recHold = 0;
				if (deleting) {
					deleting = false;
				}else{
					recording = !recording;
				}
			}
		}
	}
	//hold rec for 1s to enter deleting mode
	if (recHold > 1000 && digitalRead(recPin) == LOW) {
		recording = false;
		deleting = true;
		steps[bankIndex][partIndex][stepIndex[bankIndex][partIndex]] = 0;
		recHold = 0;
	}

	//Mute Btns
	for (int i = 0; i < 6; i++) {
		mcpBtns[i].update();
		if ( mcpBtns[i].fell() ) {
			// Serial.println("btn?");
			if (repeatDown) {
				if (i<5) {
					repeatIndex = i;
				}
			}else if (deleting && !bankDown && !shiftDown) {
				int tempPartIndex = partIndex;
				partIndex = i;
				for (size_t i = 0; i < lastStep[bankIndex][partIndex]+1; i++) {
					steps[bankIndex][partIndex][i] = 0;
				}
				partIndex = tempPartIndex;
				drawGrid(lastStep[bankIndex][partIndex]+1);
			}else if (bankDown) {
				if (i < 3){
					bankIndex = i;
					drawBank();
					drawGrid(lastStep[bankIndex][partIndex]+1);
				}
			}else if (partDown){
				partIndex = i;
				drawBank();
				drawGrid(lastStep[bankIndex][partIndex]+1);
			}else if (shiftDown){
				//still open

			}else{
				mutes[bankIndex][i] = !mutes[bankIndex][i];
			}
		}
	}
}
