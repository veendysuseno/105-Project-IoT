/***************************************
 * Project Kontrol IoT Dasar dh thinger.io
 * Board  : NodeMCU ESP8266 V3
 * Input  : thinger.io
 * Output : LED
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
 
#include <ThingerESP8266.h>
//---GANTI SESUAI DENGAN USER NAME Thinger.io  ANDA
#define USERNAME "Ardutech"
//---GANTI SESUAI DENGAN DEVICE ID Thinger.io  ANDA
#define DEVICE_ID "Kontrol_LED"
//---GANTI SESUAI DENGAN TOKEN Thinger.io  ANDA
#define DEVICE_CREDENTIAL "cRFVY6&&+yv9"
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define SSID "ArdutechWiFi"   // Nama Hotspot/WiFi
#define SSID_PASSWORD "12345678"   //  Password
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
//================================================
void setup() {
  pinMode(D5, OUTPUT);
  Serial.begin(9600);
  thing.add_wifi(SSID, SSID_PASSWORD);
  thing["LED"] << digitalPin(D5); 
}
//=================================================
void loop() {
  thing.handle();
}
