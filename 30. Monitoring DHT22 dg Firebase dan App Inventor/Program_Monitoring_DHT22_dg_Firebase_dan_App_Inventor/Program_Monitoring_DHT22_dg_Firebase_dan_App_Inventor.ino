/***************************************
 * Project Suhu Kelembaban dg MIT App Inventor dan Firebase 
 * Board  : NodeMCU ESP8266 V3
 * Input  : DHT22
 * Output : App Inventor
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <DHT.h>
//GANTI SESUAI DG FIREBASE HOST ANDA
#define FIREBASE_HOST "monitoring-dht22.firebaseio.com"
//GANTI SESUAI DG FIREBASE AUTH ANDA
#define FIREBASE_AUTH "HAV0dR9Di5axFvegT42MVUkr9sp0HrCDywl4zCd1"
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define WIFI_SSID "ArdutechWiFi"   // Nama Hotspot/WiFi
#define WIFI_PASSWORD "12345678"   //  Password
#define DHTPIN D5 
FirebaseData firebaseData;
DHT dht(DHTPIN, DHT22); 
String s;
float temp,humi;
//======================================
void setup()
{
  Serial.begin(9600);  
  dht.begin(); 
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
//===========================================
void loop()
{ char buffer[6];
  humi = dht.readHumidity();
  temp = dht.readTemperature(); 
  if (isnan(humi) || isnan(temp)) {
        Serial.println("DHT11 tidak terbaca... !");
        return;
        }
  else{  
      s = dtostrf(temp, 5,2, buffer);  
      Firebase.setString(firebaseData,"Temp",s);
      s = dtostrf(humi, 5,2, buffer);  
      Firebase.setString(firebaseData,"Humi",s);
      Serial.print("Temperature=");
      Serial.println(temp);
      Serial.print("Humidity=");
      Serial.println(humi);
      Serial.println();
  }
  delay(2000);
}
