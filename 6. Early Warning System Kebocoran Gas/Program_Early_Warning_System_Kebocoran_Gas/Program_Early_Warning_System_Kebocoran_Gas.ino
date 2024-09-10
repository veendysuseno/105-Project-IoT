/***************************************
 * Project Early Warning System Kebocoran Gas
 * Board  : NodeMCU ESP8266 V3
 * Input  : Sensor gas MQ-2
 * Output : Blynk
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial    
#include <BlynkSimpleEsp8266.h>

//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi";  // Nama Hotspot/WiFi
char pass[] = "12345678";  //  Password
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "-htbXm6E3Lizwp915_No7P516Ywa7nrj";

#define MQ2Pin D5 
int MQ2Value; 
//=======================================
void setup()
{
  Serial.begin(9600);
  delay(10);
  Blynk.begin(auth, ssid, pass);
  pinMode(MQ2Pin, INPUT);    
}
//=======================================
void loop()
{
  getMQ2Value();
  Blynk.run();
}

// **************************************************/
void getMQ2Value(void)
{
  MQ2Value = digitalRead(MQ2Pin);
  if (!MQ2Value) 
  { 
    Serial.println("==>Gas terdeteksi");
    Blynk.notify("Kebocoran Gas terdeteksi.....!");  
    delay(1000);
    while(!digitalRead(MQ2Pin));
  }
  
}
