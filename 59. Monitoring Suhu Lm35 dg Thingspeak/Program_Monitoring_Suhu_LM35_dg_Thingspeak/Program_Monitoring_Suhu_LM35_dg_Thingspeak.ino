/***************************************
 * Project Monitoring Suhu LM35 dengan Thingspeak
 * Board  : NodeMCU ESP8266 V3
 * Input  : LM35
 * Output : Thingspeak
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi";  // ganti dg Hotspot anda 
char pass[] = "12345678";     // ganti dg passwordanda
WiFiClient  client;
//---GANTI SESUAI DENGAN DATA THINGSPEAK ANDA
unsigned long myChannelNumber = 908720; //ganti dg Channel ID Thingspeak anda
const char * myWriteAPIKey = "Y3FHS8YQFWRWYYMC";//ganti dengan Write API Key

int analogValue;
float millivolts,celsius;
void setup() {
  Serial.begin(9600);  // Inisialisasi serial
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Inisialisasi ThingSpeak 
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");    
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  } 
}
//=======================
void loop() {  
  analogValue = analogRead(A0);
  millivolts = (analogValue/1024.0) * 3300; 
  celsius = millivolts/10;   
  int x = ThingSpeak.writeField(myChannelNumber, 1, celsius, myWriteAPIKey);
  if(x == 200){
    Serial.print("Temperature=");
    Serial.print(celsius);
    Serial.println(" C");
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  } 
  delay(20000); // tunggu 20 detik untuk update 
}
