/***************************************
 * Project Kontrol 4 Relay dg MIT App Inventor dan Firebase 
 * Board  : NodeMCU ESP8266 V3
 * Input  : App Inventor
 * Output : Relay module
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
//GANTI SESUAI DG FIREBASE HOST ANDA
#define FIREBASE_HOST "kontrol-4-relay-d2ba3.firebaseio.com"
//GANTI SESUAI DG FIREBASE AUTH ANDA
#define FIREBASE_AUTH "hVDIdGeKlEInRxVa2rVeF87zRk6gVUxpwwXRqh2F"
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define WIFI_SSID "ArdutechWiFi"
#define WIFI_PASSWORD "12345678"
#define RL1 D5
#define RL2 D6
#define RL3 D7
#define RL4 D8
FirebaseData firebaseData;
String c;
//======================================
void setup()
{
  Serial.begin(9600);
  pinMode(RL1,OUTPUT);
  pinMode(RL2,OUTPUT);
  pinMode(RL3,OUTPUT);
  pinMode(RL4,OUTPUT);
  digitalWrite(RL1,HIGH);
  digitalWrite(RL2,HIGH);
  digitalWrite(RL3,HIGH);
  digitalWrite(RL4,HIGH);
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
  Firebase.setString(firebaseData, "RL1", "1");
  Firebase.setString(firebaseData, "RL2", "1");
  Firebase.setString(firebaseData, "RL3", "1");
  Firebase.setString(firebaseData, "RL4", "1");
 }
//============================================
void loop()
{
   if(Firebase.get(firebaseData, "RL1"))
    {   
      c=firebaseData.stringData();    
      digitalWrite(RL1,(c.toInt()));
     }else{    
      Serial.print("Error in getInt, ");
      Serial.println(firebaseData.errorReason());
      }
    //===========
    if(Firebase.get(firebaseData, "RL2"))
    {   
      c=firebaseData.stringData();    
      digitalWrite(RL2,(c.toInt()));
     }else{    
      Serial.print("Error in getInt, ");
      Serial.println(firebaseData.errorReason());
      }
    //===========
    if(Firebase.get(firebaseData, "RL3"))
    {   
      c=firebaseData.stringData();    
      digitalWrite(RL3,(c.toInt()));
     }else{    
      Serial.print("Error in getInt, ");
      Serial.println(firebaseData.errorReason());
      }
    //=============
    if(Firebase.get(firebaseData, "RL4"))
    {   
      c=firebaseData.stringData();    
      digitalWrite(RL4,(c.toInt()));
     }else{    
      Serial.print("Error in getInt, ");
      Serial.println(firebaseData.errorReason());
      }
  delay(1000);
}
