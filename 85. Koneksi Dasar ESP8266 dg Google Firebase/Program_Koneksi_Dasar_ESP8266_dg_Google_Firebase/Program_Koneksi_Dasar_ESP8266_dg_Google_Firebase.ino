/***************************************
 * Project Koneksi Dasar ESP8266 dg Google Firebase
 * Board  : NodeMCU ESP8266 V3
 * Input  : -
 * Output : Firebase
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
//  GANTI DENGAN FIREBASE HOST ANDA
#define FIREBASE_HOST "led-nodemcu-bf157.firebaseio.com"
//GANTI DENGAN FIREBASE AUTH ANDA
#define FIREBASE_AUTH "8r7TnLtOOK1BPDlqshS7ls8HoyRzpAtBQSgqvGbY"
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define WIFI_SSID "ArdutechWiFi"  // Nama Hotspot/WiFi
#define WIFI_PASSWORD "firmas20"  //  Password

FirebaseData firebaseData;
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
  if(Firebase.setInt(firebaseData, "LED", 1))
  {
     Serial.println("Set int data success");

  }else{
    Serial.print("Error in setInt, ");
    Serial.println(firebaseData.errorReason());
  }

  if(Firebase.getInt(firebaseData, "LED"))
  {
    Serial.print("Get int data success, int = ");
    Serial.println(firebaseData.intData());

  }else{
    Serial.print("Error in getInt, ");
    Serial.println(firebaseData.errorReason());
  }
}
//============================================
void loop()
{
   if(Firebase.getInt(firebaseData, "LED"))
  {
    Serial.print("Get int data success, int = ");
    Serial.println(firebaseData.intData());
  }else{
    Serial.print("Error in getInt, ");
    Serial.println(firebaseData.errorReason());
  }
  delay(2000);
}
