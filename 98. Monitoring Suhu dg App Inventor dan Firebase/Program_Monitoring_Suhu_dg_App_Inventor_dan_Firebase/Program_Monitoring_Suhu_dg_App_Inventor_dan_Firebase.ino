/***************************************
 * Project Monitoring LM35 dg MIT App Inventor dan Firebase 
 * Board  : NodeMCU ESP8266 V3
 * Input  : LM35
 * Output : App Inventor
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
//GANTI SESUAI DG FIREBASE HOST ANDA
#define FIREBASE_HOST "monitoring-lm35-30d4.firebaseio.com"
//GANTI SESUAI DG FIREBASE AUTH ANDA
#define FIREBASE_AUTH "5nge5lDKDXKCfrvxxAlNxjQRxdhWTN5Ja3HC3U"
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define WIFI_SSID "ArdutechWiFi"  // Nama Hotspot/WiFi
#define WIFI_PASSWORD "12345678"  //  Password

FirebaseData firebaseData;
String c;
int analogValue;
float millivolts,celsius;
//======================================
void setup()
{
  Serial.begin(9600);  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected ..."); 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);  
}
//=========================================
void loop()
{ char buffer[6];
  analogValue = analogRead(A0);
  millivolts = (analogValue/1024.0) * 3300; 
  celsius = millivolts/10;  
  String s = dtostrf(celsius, 5,2, buffer);  
  Firebase.setString(firebaseData,"Temp",s);
  Serial.print("Temp=");
  Serial.println(celsius);
  delay(2000);
}
