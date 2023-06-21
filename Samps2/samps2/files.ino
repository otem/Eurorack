void getDirectories(File dir, int numSpaces) {
   while(true) {
     File entry = dir.openNextFile();
     if (! entry) {
       // Serial.println("** no more files **");
       break;
     }

     const char *filename = entry.name();

     if (isFileNameValid(filename)) {
       if (entry.isDirectory()) {
         dirNames[dirCount] = entry.name();
         Serial.println(String(dirCount)+": "+String(entry.name()));
         dirCount++;
         getDirectories(entry, 0);
       } else {
         // Serial.println("File: "+String(entry.name()));
         // // files have sizes, directories do not
         // unsigned int n = log10(entry.size());
         // if (n > 10) n = 10;
         // printSpaces(50 - numSpaces - strlen(entry.name()) - n);
         // Serial.print("  ");
         // Serial.print(entry.size(), DEC);
         // DateTimeFields datetime;
         // if (entry.getModifyTime(datetime)) {
         //   printSpaces(4);
         // }
         // Serial.println();
       }
     }

     entry.close();
   }
}

void loadFiles(){
  loading = true;
  dc1.amplitude(0,1);
  for (size_t i = 0; i < 8; i++) {
    envs[i]->noteOff();
  }  

  display.clearDisplay();
  display.setCursor(2,4);
  display.print("Loading");
  String dirPath = "samples/"+dirNames[dirIndex];
  newdigate::flashloader loader;
  for (size_t i = 0; i < 8; i++) {

    String filePath = dirPath+"/"+fileNames[i];
    samps[i] = loader.loadSample((char*) filePath.c_str());
    Serial.println("loading: "+String(i)+" :"+String(filePath));
    display.print(".");
    display.display();
  }
  loadedFile = dirIndex;
  displayDirs();
  loading = false;
  dc1.amplitude(vca,5);
}

void printSpaces(int num) {
  for (int i=0; i < num; i++) {
    Serial.print(" ");
  }
}

bool isFileNameValid( const char * fileName ){
  char c;
  while ( (c = *fileName++) )
    if ( c != '.' && !isalnum(c))
      return false;
  return true;
}
