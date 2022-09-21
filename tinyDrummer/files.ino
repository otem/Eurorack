void getDirectories(File dir, int numSpaces) {
   while(true) {
     File entry = dir.openNextFile();
     if (! entry) {
       // Serial.println("** no more files **");
       break;
     }

     const char *filename = entry.name();

     if (entry.isDirectory()) {
       dirName = entry.name();
       Serial.println(String(entry.name())+"/");
       getDirectories(entry, 0);
       dirCount++;
     } else {
       if (isFileNameValid(filename)) {
         fileCount++;
         loadFiles(dirName);
       }
     }

     entry.close();
   }
}

void loadFiles(String folderName){
  String dirPath = "samples/"+folderName;
  String fileName;

  fileName = String(fileCount%8 == 0 ? 8 :fileCount%8)+".wav";

  String filePath = dirPath+"/"+fileName;
  Serial.println("loading: "+String(fileCount-1)+" :"+String(filePath));


  samps[fileCount-1] = loader.loadSample((char*) filePath.c_str());

}

bool isFileNameValid( const char * fileName ){
  char c;
  while ( (c = *fileName++) )
    if ( c != '.' && !isalnum(c))
      return false;
  return true;
}
