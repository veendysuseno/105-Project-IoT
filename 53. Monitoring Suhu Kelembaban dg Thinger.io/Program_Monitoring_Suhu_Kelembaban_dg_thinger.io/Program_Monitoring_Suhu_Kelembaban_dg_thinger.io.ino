/***************************************
 * Project Monitoring Suhu Kelembaban dg thinger.io
 * Board  : NodeMCU ESP8266 V3
 * Input  : DHT11
 * Output : thinger.io
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <DHT.h>
#include <ThingerESP8266.h>
//---GANTI SESUAI DENGAN USER NAME Thinger.io  ANDA
#define USERNAME "Ardutech" 
//---GANTI SESUAI DENGAN DEVICE ID Thinger.io  ANDA
#define DEVICE_ID "MonDHT11" 
//---GANTI SESUAI DENGAN TOKEN Thinger.io  ANDA
#define DEVICE_CREDENTIAL "3U60t0OwKGOb"
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define SSID "ArdutechWiFi"       // Nama Hotspot/WiFi
#define SSID_PASSWORD "12345678"  //  Password

#define DHTPIN D5 
#define DHTTYPE DHT11

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
DHT dht(DHTPIN, DHTTYPE);
float hum,temp;
//======================================
void setup() {
  Serial.begin(9600);
  Serial.println("Baca DHT11");
  dht.begin();
  thing.add_wifi(SSID, SSID_PASSWORD);
  thing["dht11"] >> [](pson& out){
    out["humidity"] = hum;
    out["celsius"] = temp;
  };
}
//======================================
void loop() {  
  thing.handle();  
  float h = dht.readHumidity(); 
  float t = dht.readTemperature(); 
  float f = dht.readTemperature(true); 
  hum = h;
  temp = t;
}
