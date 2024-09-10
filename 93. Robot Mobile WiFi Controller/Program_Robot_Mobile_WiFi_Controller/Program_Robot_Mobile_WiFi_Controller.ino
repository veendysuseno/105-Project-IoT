
/***************************************
 * Project Kontrol Robot Mobile dg WiFi
 * Board  : NodeMCU ESP8266 V3
 * Input  : Blynk
 * Output : Gerakan motor pada robot
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "-htbXm6E3Lizwp915_No7P516Ywa7nrj";//token
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi";  // Nama Hotspot/WiFi
char pass[] = "12345678";      //  Password

const int L1 = D1;//2;
const int L2 = D2;//3;
const int R1 = D3;//4;
const int R2 = D4;//7;

BLYNK_WRITE(V0){
  int buttonState = param.asInt();
  if(buttonState==HIGH){
    kiri();
  }
  else stop();
}
BLYNK_WRITE(V1){
  int buttonState = param.asInt();
  if(buttonState==HIGH){
    kanan();
  }
  else stop();
}
BLYNK_WRITE(V2){
  int buttonState = param.asInt();
  if(buttonState==HIGH){
    mundur();
  }
  else stop();
}
BLYNK_WRITE(V3){
  int buttonState = param.asInt();
  if(buttonState==HIGH){
    maju();
  }
  else stop();
}

void maju(){
  digitalWrite(L1, HIGH);  
  digitalWrite(L2, LOW);  
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
} 

void mundur(){
  digitalWrite(L1, LOW);  
  digitalWrite(L2, HIGH);  
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
} 

void kiri(){
  digitalWrite(L1, LOW);  
  digitalWrite(L2, LOW);  
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
} 

void kanan(){
  digitalWrite(L1, HIGH);  
  digitalWrite(L2, LOW);  
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
} 
void stop(){
  digitalWrite(L1, LOW);  
  digitalWrite(L2, LOW);  
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
} 
//==============================  
void setup()
{
  Serial.begin(115200);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);      
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);  
  
  digitalWrite(L1, LOW);  
  digitalWrite(L2, LOW);  
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  
  Blynk.begin(auth, ssid, pass);   
}
//=================================
void loop(){    
  Blynk.run();  
 }
