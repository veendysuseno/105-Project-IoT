/***************************************
 * Project Kontrol Robot 4WD
 * Board  : NodeMCU ESP8266 V3
 * Input  : Blynk
 * Output : Motor DC (Robot 4WD)
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
char pass[] = "12345678";   //  Password

int dirEn = D5;   //Pin 7
int dirLatch = D8;//Pin 12
int dirClk = D2;  //Pin 4
int dirSer = D6;  //Pin 8

int pwm0a = D4; //Pin 6  en M3 
int pwm0b = D3; //Pin 5  en M4
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
  dirMotor = 0b00100111; // arah maju
  arahMotor();
  digitalWrite(pwm0a, HIGH); //en M3
  digitalWrite(pwm2b, HIGH); //en M2
  digitalWrite(pwm0b, HIGH); //en M4
  digitalWrite(pwm2a, HIGH); //en M1
} 

void mundur(){
  dirMotor = 0b11011000; // arahmundur
  arahMotor();
  digitalWrite(pwm0a, HIGH); //en M3
  digitalWrite(pwm2b, HIGH); //en M2
  digitalWrite(pwm0b, HIGH); //en M4
  digitalWrite(pwm2a, HIGH); //en M1
}  

void kiri(){
  dirMotor = 0b00100010; // belok kiri
  arahMotor();
  digitalWrite(pwm0a, HIGH); //en M3
  digitalWrite(pwm2b, HIGH); //en M2
} 

void kanan(){
  dirMotor = 0b00000101; // belok kanan
  arahMotor();
  digitalWrite(pwm0b, HIGH); //en M4
  digitalWrite(pwm2a, HIGH); //en M1
} 
void stop(){
  digitalWrite(dirEn, HIGH);
} 
//==============================
void setup() 
{
  pinMode(dirLatch, OUTPUT);
  pinMode(dirSer, OUTPUT);  
  pinMode(dirClk, OUTPUT);
  pinMode(dirEn, OUTPUT);
  pinMode(pwm0a, OUTPUT);
  pinMode(pwm0b, OUTPUT);
  pinMode(pwm2a, OUTPUT);
  pinMode(pwm2b, OUTPUT);
  //--------------semua motor OFF
  digitalWrite(pwm0a, LOW);
  digitalWrite(pwm0b, LOW);
  digitalWrite(pwm2a, LOW);
  digitalWrite(pwm2b, LOW);
  
  digitalWrite(dirEn, HIGH);//stop
  
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);  
}
//===========================
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
