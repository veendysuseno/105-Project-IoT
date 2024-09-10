/***************************************
 * Project Ultrasonic Range Meter dg ThingSpeak
 * Board  : NodeMCU ESP8266 V3
 * Input  : Sensor Ultrasonik HC-SR04
 * Output : ThingSpeak
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
const char* ssid     = "ArdutechWiFi"; // ssid/hotspot
const char* password = "12345678"; //  Password
//---GANTI dg Channel ID Thingspeak anda
unsigned long myChannelNumber = 908720; 
//---GANTI dg API Key Thingspeak anda
const char * myWriteAPIKey = "Y3FHS8YQFWRWYYMC";//ganti dengan Write API Key

const int trigP = D6;  
const int echoP = D5; 

long duration;
int distance;
WiFiClient client;
//=====================================
void setup() {
  Serial.begin(9600);
  pinMode(trigP, OUTPUT);  
  pinMode(echoP, INPUT);   
  Serial.println();  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Inisialisasi ThingSpeak 
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");    
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, password);  
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  } 
}
//=========================================
void loop() {
  digitalWrite(trigP, LOW);   
  delayMicroseconds(2);        
  digitalWrite(trigP, HIGH);  
  delayMicroseconds(10);      
  digitalWrite(trigP, LOW);   

  duration = pulseIn(echoP, HIGH);   
  distance= duration*0.034/2;        
  int x = ThingSpeak.writeField(myChannelNumber, 1, distance, myWriteAPIKey);
  if(x == 200){
    Serial.print("Distance = ");         
    Serial.print(distance);
    Serial.println(" cm");
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }   
  delay(20000);
}
