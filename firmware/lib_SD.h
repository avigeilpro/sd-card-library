#ifndef libSD
#define libSD

#include "sd-card-library-photon-compat.h"

File myFile;

int WriteFile(char *Folder, char *FName, String Text, int Final, int OverWrite = 0)
    {
    
    char FullAddr[40];
    FullAddr[0]=0;
    if (!((Folder[0] == 0)||((Folder[0] == '/')&(Folder[1]==0)))){
        if (!SD.exists(Folder)) {
            SD.mkdir(Folder);
        }
        sprintf(FullAddr,"%s/%s",Folder,FName);
    } else {
        strcat(FullAddr,FName);
    }
    
      // open the file. note that only one file can be open at a time,
      // so you have to close this one before opening another.
      if (OverWrite){
          myFile = SD.open(FullAddr, FILE_WRITE | O_TRUNC);
      }else{
          myFile = SD.open(FullAddr, FILE_WRITE);
      }

    // if the file opened okay, write to it:
      if (myFile) {
        if (Final){
            myFile.println(Text);
        } else {
            myFile.print(Text);
        }
      // close the file:
        myFile.close();
        return 1;
      } else {
        return 0;
      }
     
}

//char *ReadFile(char *Folder, char *FName) {
void ReadFile(char *Folder, char *FName, char *result) {
    
    char FullAddr[40];
    //char result[600];
    result[0]=0;
    char tmp[2];
    
    sprintf(FullAddr,"%s/%s",Folder,FName);
    
    myFile = SD.open(FullAddr);
    if (myFile) {
        Serial.println(FullAddr);
        
        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          sprintf(tmp,"%c",myFile.read());
          strcat(result,tmp);
        }
        // close the file:
        myFile.close();
    }
    sprintf(result,"%s",result);
  //return result;
}

#endif
