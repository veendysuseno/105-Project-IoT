/***************************************
 * Project Kontrol Robot Tank
 * Board  : NodeMCU ESP8266 V3
 * Input  : Blynk
 * Output : Motor DC (Robot Tank)
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
char ssid[] = "ArdutechWiFi";   // Nama Hotspot/WiFi
char pass[] = "12345678";       //  Password

int dirEn = D5;   //Pin 7
int dirLatch = D8;//Pin 12
int dirClk = D2;  //Pin 4
int dirSer = D6;  //Pin 8

int pwm2a = D7; //Pin 11 en M1
int pwm2b = D1; //Pin 3  en M2

byte dirMotor = 0;    // Variable arah motor


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
  dirMotor = 0b00000110; // arah maju
  arahMotor();
  digitalWrite(pwm2b, HIGH); //en M2
  digitalWrite(pwm2a, HIGH); //en M1
} 

void mundur(){
  dirMotor = 0b00011000; // arahmundur
  arahMotor();
  digitalWrite(pwm2b, HIGH); //en M2
  digitalWrite(pwm2a, HIGH); //en M1
}  

void kiri(){
  dirMotor = 0b00000010; // belok kiri
  arahMotor();
  digitalWrite(pwm2b, HIGH); //en M2
} 

void kanan(){
  dirMotor = 0b00000100; // belok kanan
  arahMotor();
  digitalWrite(pwm2a, HIGH); //en M1
} 
void stop(){
  digitalWrite(dirEn, HIGH);
} 
//================================
void setup() 
{
  pinMode(dirLatch, OUTPUT);
  pinMode(dirSer, OUTPUT);  
  pinMode(dirClk, OUTPUT);
  pinMode(dirEn, OUTPUT);
  pinMode(pwm2a, OUTPUT);
  pinMode(pwm2b, OUTPUT);
  //--------------semua motor OFF
  digitalWrite(pwm2a, LOW);
  digitalWrite(pwm2b, LOW);  
  digitalWrite(dirEn, HIGH);//stop  
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);  
}
//=================================
void loop() 
{ 
  Blynk.run(); 
}

void arahMotor(){
   digitalWrite(dirEn, LOW);
   digitalWrite(dirLatch, LOW);
   shiftOut(dirSer, dirClk, MSBFIRST, dirMotor);
   digitalWrite(dirLatch, HIGH);
}
