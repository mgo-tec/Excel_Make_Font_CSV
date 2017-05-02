#include "FS.h"
#include "SD.h"
#include "SPI.h"

const char* MyFont_CSV_Readfile = "/font/MyFont.csv"; //読み込む CSV ファイル名
const char* MyFont_Binary_Writefile = "/font/MyFont.fnt"; //書き込むバイナリファイル名

void setup() {
  Serial.begin(115200);

  SD.begin(5, SPI, 10000000, "/sd"); //SD CS = GPIO #5

  File fr = SD.open(MyFont_CSV_Readfile, FILE_READ);
  File fw = SD.open(MyFont_Binary_Writefile, FILE_WRITE);
  
  int16_t i = 0, j = 0, k = 0;
  uint8_t c[4];
  uint8_t cH, cL;
  uint8_t b[10][2][16];

  for(i=0; i<4; i++){
    c[i] = 0;
  }
  
  if(fr){
    for(i = 0; i < 10; i++){
      Serial.println();
      Serial.println("------------------");
      for(j = 0; j < 2; j++){
        Serial.println();
        Serial.print("###################");
        Serial.println(j);
        for(k = 0; k < 16; k++){
          Serial.print("(");Serial.print(k); Serial.print(")  : ");

          fr.read( c , 4 );

          if( c[0] == '\0' || c[1] == '\0' || c[2] == '\0' || c[3] == '\0') break;

          if((c[0] != '\n') && (c[0] != '\r') && (c[1] != '\n') && (c[1] != '\r')){
            if(c[0] > 0x40){
              cH = (uint8_t)((c[0] - 0x41) + 10);
            }else{
              cH = (uint8_t)(c[0] - 0x30);
            }
            if(c[1] > 0x40){
              cL = (uint8_t)((c[1] - 0x41) + 10);
            }else{
              cL = (uint8_t)(c[1] - 0x30);
            }
            b[i][j][k] = cH*16 + cL;
            
            Serial.print(b[i][j][k], HEX);
          }
          
          if(c[2] == '\n'){
            Serial.println("￥ｎ");
          }
          if(c[2] == '\r'){
            Serial.print("  ￥ｒ");
          }
          if(c[3] == '\n'){
            Serial.println("￥ｎ");
          }
          if(c[3] == '\r'){
            Serial.print("  ￥ｒ");
          }
          yield();
        }
        if( c[0] == '\0' || c[1] == '\0' || c[2] == '\0' || c[3] == '\0') break;
      }
      if( c[0] == '\0' || c[1] == '\0' || c[2] == '\0' || c[3] == '\0') break;
    }
  }else{
    Serial.println(F(" File has not been uploaded to the flash in SD file system"));
    delay(30000);
  }
  fr.close();

  if(fw){
    for(i = 0; i < 10; i++){
      for(j = 0; j < 2; j++){
        for(k = 0; k < 16; k++){
          fw.write(b[i][j][k]);
        }
      }
    }
  }else{
    Serial.println(F(" File has not been uploaded to the flash in SD file system"));
    delay(30000);
  }
  fw.close();
}

void loop() {

}
