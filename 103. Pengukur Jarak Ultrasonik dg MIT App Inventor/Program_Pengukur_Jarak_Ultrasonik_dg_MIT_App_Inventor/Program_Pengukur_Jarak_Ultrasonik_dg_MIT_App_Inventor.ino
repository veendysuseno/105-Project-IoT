/***************************************
 * Project Ultrasonic Range Finder dg MIT App Inventor dan Firebase 
 * Board  : NodeMCU ESP8266 V3
 * Input  : Sensor Ultrasonic
 * Output : App Inventor
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
//GANTI SESUAI DG FIREBASE HOST ANDA
#define FIREBASE_HOST "ultrasonic-range-meter.firebaseio.com"
//GANTI SESUAI DG FIREBASE AUTH ANDA
#define FIREBASE_AUTH "tzD3gOfnAdg7jkkavyCuBUrKkt8XGm6HBDDUnpMA"
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define WIFI_SSID "ArdutechWiFi"  // Nama Hotspot/WiFi
#define WIFI_PASSWORD "12345678"  //  Password

FirebaseData firebaseData;
String c;
const int trigP = D6;  
const int echoP = D5;
long duration;
int distance; 
//======================================
void setup()
{
  Serial.begin(9600);  
  pinMode(trigP, OUTPUT);  
  pinMode(echoP, INPUT);    
  delay(20);
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
//====================================
void loop()
{ char buffer[6];
  digitalWrite(trigP, LOW);   
  delayMicroseconds(2);        
  digitalWrite(trigP, HIGH);  
  delayMicroseconds(10);      
  digitalWrite(trigP, LOW);   
  duration = pulseIn(echoP, HIGH);   
  distance= duration*0.034/2;  
  Firebase.setInt(firebaseData,"Range",distance);
  Serial.print("Range=");
  Serial.println(distance);
  delay(2000);
}
