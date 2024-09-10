
#include<Wire.h> 
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN D4  
#define RST_PIN D3 

//String page = ""; 
char input[12]; 
int count = 0; 

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;
String ID_TAG;

//==========================
void readRFID(byte *buffer, byte bufferSize)
{
  ID_TAG="";
  for(byte i = 0;i<bufferSize; i++)
  {
    ID_TAG=ID_TAG+String(buffer[i], HEX);
  }
}
//==============================
void setup() {    
  Serial.begin(9600);  
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522  
  Wire.begin(D2, D1);   
  Serial.println("Tempelkan RFID TAG"); 
}
//======================================
void loop(){   
  if(!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()){
    return;    
   } 
  readRFID(mfrc522.uid.uidByte, mfrc522.uid.size);  
  Serial.print("RFID=");
  Serial.println(ID_TAG);  
  Serial.println();
  delay(2000);
  }
