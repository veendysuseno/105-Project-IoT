/***************************************
 * Project Kontrol RGB dengan Blynk
 * Board  : NodeMCU ESP8266 V3
 * Input  : Blynk
 * Output : RGB
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
 
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "CbS0l3x8agGfefffJ9GJ6b3G5kKE5Q4S";
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi";  // Nama Hotspot/WiFi
char pass[] = "12345678";   //  Password
//==========================================
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);  
}
//===========================================
void loop()
{
  Blynk.run(); 
}
