/***************************************
 * Project Early Warning System Kebocoran Gas
 * Board  : NodeMCU ESP8266 V3
 * Input  : Sensor gas MQ-2
 * Output : Blynk
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <BlynkSimpleEsp8266.h>
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "CbS0l3x8agGfefffJ9GJ6b3G5kKE5Q4S";
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi";  // Nama Hotspot/WiFi
char pass[] = "12345678";      //  Password

#define FlameSensor D5 
int FlameStatus; 
//=======================================
void setup()
{
  Serial.begin(9600);
  delay(10);
  Blynk.begin(auth, ssid, pass);
  pinMode(FlameSensor, INPUT);      
}
//=======================================
void loop()
{
  CekFlame();
  Blynk.run();
}

// **************************************************/
void CekFlame(void)
{
  FlameStatus = digitalRead(FlameSensor);  
   if (!FlameStatus) 
  { 
    Serial.println("Terjadi kebakaran...");
    Blynk.notify("Terjadi kebakaran ...!");  
    delay(1000);
    while(!digitalRead(FlameSensor));
    delay(1000);
  }
}
