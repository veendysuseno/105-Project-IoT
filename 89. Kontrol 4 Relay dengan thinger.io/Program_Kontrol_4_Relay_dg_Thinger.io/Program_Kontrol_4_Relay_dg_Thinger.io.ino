/***************************************
 * Project Kontrol 4 Relay dg thinger.io
 * Board  : NodeMCU ESP8266 V3
 * Input  : thinger.io
 * Output : Relay 4 Channel
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
 
#include <ThingerESP8266.h>
//---GANTI SESUAI DENGAN USER NAME Thinger.io  ANDA
#define USERNAME "Ardutech"
//---GANTI SESUAI DENGAN DEVICE ID Thinger.io  ANDA
#define DEVICE_ID "Kontrol_Relay"
//---GANTI SESUAI DENGAN TOKEN Thinger.io  ANDA
#define DEVICE_CREDENTIAL "SmZAUN9SSsw7"
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define SSID "ArdutechWiFi"   // Nama Hotspot/WiFi
#define SSID_PASSWORD "12345678"   //  Password
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
//================================================
void setup() {
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  Serial.begin(9600);
  thing.add_wifi(SSID, SSID_PASSWORD);
  thing["D5"] << digitalPin(D5); 
  thing["D6"] << digitalPin(D6); 
  thing["D7"] << digitalPin(D7); 
  thing["D8"] << digitalPin(D8);  
 
}
//=================================================
void loop() {
  thing.handle();  
}
