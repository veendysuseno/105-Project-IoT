/***************************************
 * Project Deteksi Pencuri dg MIT App Inventor dan Firebase 
 * Board  : NodeMCU ESP8266 V3
 * Input  : Sensor Ultrasonic (2)
 * Output : App Inventor
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
//GANTI SESUAI DG FIREBASE HOST ANDA
#define FIREBASE_HOST "deteksi-pencuri.firebaseio.com"
//GANTI SESUAI DG FIREBASE AUTH ANDA
#define FIREBASE_AUTH "WpziLwl1bSTQHqqmFMcf3mJGhq26g7S6vO34VSIT"
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define WIFI_SSID "ArdutechWiFi"   // Nama Hotspot/WiFi
#define WIFI_PASSWORD "12345678"   //  Password

FirebaseData firebaseData;
String c;
const int echo1 = D5;
const int trig1 = D6;  
const int echo2 = D7;
const int trig2 = D8;  
long duration1,duration2;
int distance1,distance2; 
//======================================
void sensor1(){
  digitalWrite(trig1, LOW);   
  delayMicroseconds(2);        
  digitalWrite(trig1, HIGH);  
  delayMicroseconds(10);      
  digitalWrite(trig1, LOW);   
  duration1 = pulseIn(echo1, HIGH);   
  distance1= duration1*0.034/2;  
}
void sensor2(){
  digitalWrite(trig2, LOW);   
  delayMicroseconds(2);        
  digitalWrite(trig2, HIGH);  
  delayMicroseconds(10);      
  digitalWrite(trig2, LOW);   
  duration2 = pulseIn(echo2, HIGH);   
  distance2= duration2*0.034/2;  
}
void setup()
{
  Serial.begin(9600);  
  pinMode(trig1, OUTPUT);  
  pinMode(echo1, INPUT); 
  pinMode(trig2, OUTPUT);  
  pinMode(echo2, INPUT);   
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

void loop()
{ 
  sensor1();
  sensor2();
  
  if(distance1<=20){
      Firebase.setString(firebaseData,"Kondisi1","Bahaya");
      Serial.print("AREA 1 BAHAYA !!! , ");
      delay(20000);
  }
  else if(distance1>20){
      Firebase.setString(firebaseData,"Kondisi1","Aman");
      Serial.print("AREA 1 AMAN, ");
  }
 
   if(distance2<=20){
      Firebase.setString(firebaseData,"Kondisi2","Bahaya");
      Serial.println("AREA 2 BAHAYA !!!");
      delay(20000);
  }
  else if(distance2>20){
      Firebase.setString(firebaseData,"Kondisi2","Aman");
      Serial.println("AREA 2 AMAN");
  }  
  Serial.println();
  delay(1000);
}
