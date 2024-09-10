/***************************************
 * Project Kontrol Robotic Arm dg Android (Blynk)
 * Board  : NodeMCU ESP8266 V3
 * Input  : Blynk
 * Output : Robot Arm (Servo)
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "htbXm6E3Lizwp915_No7P516Ywa7nrj";//token
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "Ardutech"; // Nama Hotspot/WiFi
char pass[] = "12345678"; //  Password

Servo claw;
Servo left;
Servo right;
Servo middle;

BLYNK_WRITE(V0)
{
  claw.write(param.asInt());
}

BLYNK_WRITE(V1)
{
  left.write(param.asInt());
}

BLYNK_WRITE(V2)
{
  right.write(param.asInt());
}

BLYNK_WRITE(V3)
{
  middle.write(param.asInt());
}
//==========================
void setup()
{
  claw.attach(D1);
  left.attach(D2);
  right.attach(D3);
  middle.attach(D4);
  delay(1000);
  claw.write(25);
  left.write(90);
  right.write(70);
  middle.write(90);
  delay(2000);
  
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);  

  Blynk.virtualWrite(V0,25);
  Blynk.virtualWrite(V1,90);
  Blynk.virtualWrite(V2,70);
  Blynk.virtualWrite(V3,90);
}
//===============================
void loop()
{
  Blynk.run();
}
