/***************************************
 * Project Kontrol IoT Dasar dg ESP8266 dan App Inventor 
 * Board  : NodeMCU ESP8266 V3
 * Input  : MIT App Inventor
 * Output : LED
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
#define WIFI_PASSWORD "12345678"  //  Password
#define LED D5
FirebaseData firebaseData;
String c;
//======================================
void setup()
{
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected ...");
  //Serial.println(WiFi.localIP());
  //Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  if(Firebase.setString(firebaseData, "LED", "0"))
  {
    //Success
     Serial.println("Set int data success");

  }else{
    //Failed?, get the error reason from firebaseData

    Serial.print("Error in setString, ");
    Serial.println(firebaseData.errorReason());
  }
 }
//===================================
void loop()
{
   if(Firebase.get(firebaseData, "LED"))
  {
    //Success
    Serial.print("Get int data success, int = ");
    Serial.println(firebaseData.stringData());
    c=firebaseData.stringData();
    digitalWrite(LED,(c.toInt()));

  }else{
    //Failed?, get the error reason from firebaseData

    Serial.print("Error in getInt, ");
    Serial.println(firebaseData.errorReason());
  }
  delay(2000);
}
