#include "FS.h"
#include "SD.h"
#include "SPI.h"

const char* MyFont_CSV_Readfile = "/font/MyFont_ver3.0.csv"; //読み込む CSV ファイル名
const char* MyFont_Binary_Writefile = "/font/MyFont_ver3.0.fnt"; //書き込むバイナリファイル名

const uint8_t CS_SD = 4; //M5stack SDcard CSpin

void setup() {
  Serial.begin(115200);

  SD.begin(CS_SD, SPI, 10000000, "/sd");

  File fr = SD.open(MyFont_CSV_Readfile, FILE_READ);
  File fw = SD.open(MyFont_Binary_Writefile, FILE_WRITE);
  
  uint8_t c, cH, cL, b;
 
  if(fr){
    while(1){
      if(fr.available()){
        c = fr.read();
  
        if(c == '\0'){
          return;
        }else if((c == '\n') || (c == '\r')){
          Serial.println();
        }else if(c == ','){
          Serial.print(',');
        }else{
          if(c > 0x40){
            cH = (uint8_t)((c - 0x41) + 10);
          }else{
            cH = (uint8_t)(c - 0x30);
          }
          
          c = fr.read();
          if( c == '\0') return;
          
          if(c > 0x40){
            cL = (uint8_t)((c - 0x41) + 10);
          }else{
            cL = (uint8_t)(c - 0x30);
          }
          b = cH*16 + cL;
          fw.write(b);
          Serial.print(b, HEX);
        }
      }else{
        return;
      }
      yield();
    }
  }else{
    Serial.println(F(" File has not been uploaded to the flash in SD file system"));
    delay(30000);
  }
  fr.close();
  delay(10);
  fw.close();
  delay(10);

}

void loop() {

}
