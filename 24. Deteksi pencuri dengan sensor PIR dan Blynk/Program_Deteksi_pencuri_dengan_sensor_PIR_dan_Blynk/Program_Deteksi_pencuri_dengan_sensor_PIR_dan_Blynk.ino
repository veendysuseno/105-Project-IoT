/***************************************
 * Project Deteksi Manusia dg sensor PIR dan Blynk
 * Board  : NodeMCU ESP8266 V3
 * Input  : PIR sensor
 * Output : Blynk (Notification)
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
 
#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial    
#include <BlynkSimpleEsp8266.h>
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "CbS0l3x8agGfefffJ9GJ6b3G5kKE5Q4S";
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi";   // Nama Hotspot/WiFi
char pass[] = "12345678";      //  Password

#define pirPin D5 // sensor PIR
int pirValue;  

void setup()
{
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  delay(10);
  Blynk.begin(auth, ssid, pass); 
}

void loop()
{
  cekPIR();
  Blynk.run();
}

// **************************************************/
void cekPIR(void)
{
  pirValue = digitalRead(pirPin);
  if (pirValue) 
  { 
    Serial.println("==>Obyek terdeteksi");
    Blynk.notify("Obyek terdeteksi.....!");  
    delay(1000);    
  }
  
}
