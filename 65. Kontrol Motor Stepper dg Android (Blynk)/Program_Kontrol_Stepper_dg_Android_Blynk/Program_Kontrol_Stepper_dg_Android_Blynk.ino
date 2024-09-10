/***************************************
 * Project Kontrol Motor Stepper dg Android (Blynk)
 * Board  : NodeMCU ESP8266 V3
 * Input  : Blynk
 * Output : Stepper Motor
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
 
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
uint8_t IN1 = D5;
uint8_t IN2 = D6;
uint8_t IN3 = D7;
uint8_t IN4 = D8;

const uint16_t _delay = 5;
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "CbS0l3x8agGfefffJ9GJ6b3G5kKE5Q4S";
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi"; // Nama Hotspot/WiFi
char pass[] = "12345678";     //  Password
//====================
void sequence(bool a, bool b, bool c, bool d){  /* four step sequence to stepper motor */
  digitalWrite(IN1, a);
  digitalWrite(IN2, b);
  digitalWrite(IN3, c);
  digitalWrite(IN4, d);
  delay(_delay);
}
//========================
void CW(){
    sequence(HIGH, LOW, LOW, LOW);
    sequence(HIGH, HIGH, LOW, LOW);
    sequence(LOW, HIGH, LOW, LOW);
    sequence(LOW, HIGH, HIGH, LOW);
    sequence(LOW, LOW, HIGH, LOW);
    sequence(LOW, LOW, HIGH, HIGH);
    sequence(LOW, LOW, LOW, HIGH);
    sequence(HIGH, LOW, LOW, HIGH);
}
void CCW(){
    sequence(LOW, LOW, LOW, HIGH);
    sequence(LOW, LOW, HIGH, HIGH);
    sequence(LOW, LOW, HIGH, LOW);
    sequence(LOW, HIGH, HIGH, LOW);
    sequence(LOW, HIGH, LOW, LOW);
    sequence(HIGH, HIGH, LOW, LOW);
    sequence(HIGH, LOW, LOW, LOW);
    sequence(HIGH, LOW, LOW, HIGH);
}
//==================================
void setup()
{
  pinMode(IN1, OUTPUT); /* set four wires as output */
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}
//=============================
void loop()
{
  Blynk.run();
  if(digitalRead(D1)==1){
    CW();
  }
  else if(digitalRead(D2)==1){
    CCW();
  }
}
