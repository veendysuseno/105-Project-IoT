/***************************************
 * Project Kontrol Servo SG90 dengan Blynk
 * Board  : NodeMCU ESP8266 V3
 * Input  : Blynk
 * Output : Servo SG90
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
 
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "-htbXm6E3Lizwp915_No7P516Ywa7nrj";

//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi";  // Nama Hotspot/WiFi
char pass[] = "12345678";   //  Password
Servo servo;

BLYNK_WRITE(V3) {

servo.write(param.asInt());

}
//=======================
void setup()
{
  Serial.begin(9600);
  servo.attach(D5); // 1
  Blynk.begin(auth, ssid, pass);    
}
//=======================
void loop()
{
  Blynk.run(); 
}
