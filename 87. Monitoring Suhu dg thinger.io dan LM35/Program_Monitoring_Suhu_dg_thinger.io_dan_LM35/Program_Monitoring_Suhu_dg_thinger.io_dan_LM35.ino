/***************************************
 * Project Monitoring Suhu dg thinger.io dan LM35
 * Board  : NodeMCU ESP8266 V3
 * Input  : LM35
 * Output : thinger.io
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include <ThingerESP8266.h>
//---GANTI SESUAI DENGAN USER NAME Thinger.io  ANDA
#define USERNAME "Ardutech" //Username thinger.io
//---GANTI SESUAI DENGAN DEVICE ID Thinger.io  ANDA
#define DEVICE_ID "Mon_LM35"
//---GANTI SESUAI DENGAN TOKEN Thinger.io  ANDA 
#define DEVICE_CREDENTIAL "1YdMPrRM8n9$"
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define SSID "ArdutechWiFi"       // Nama Hotspot/WiFi
#define SSID_PASSWORD "12345678"  //  Password

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

int analogValue;
float millivolts,celsius;
//=======================================
void setup() {  
  Serial.begin(9600);
  thing.add_wifi(SSID, SSID_PASSWORD);
  thing["SensorLM35"] >> [](pson& out){
    out["temperature"] = celsius;   
  };
}
//=======================================
void loop() {  
  thing.handle();   
  analogValue = analogRead(A0);
  millivolts = (analogValue/1024.0) * 3300; 
  celsius = millivolts/10; 
  Serial.println(celsius);
  Serial.println();
}
