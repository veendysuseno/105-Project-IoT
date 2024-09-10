/***************************************
 * Project Google Maps dg Modul GPS dan thinger.io
 * Board  : NodeMCU ESP8266 V3
 * Input  : DHT11
 * Output : thinger.io
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ThingerESP8266.h>
//---GANTI SESUAI DENGAN USER NAME Thinger.io  ANDA
#define USERNAME "Ardutech" 
//---GANTI SESUAI DENGAN DEVICE ID Thinger.io  ANDA
#define DEVICE_ID "Maps_NEO" 
//---GANTI SESUAI DENGAN TOKEN Thinger.io  ANDA
#define DEVICE_CREDENTIAL "EN1C#mXy3tzN"
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define SSID "ArdutechWiFi"       // Nama Hotspot/WiFi
#define SSID_PASSWORD "12345678"  //  Password
TinyGPSPlus gps;
static const int RX= D6, TX= D7;
SoftwareSerial soft(RX, TX);
String latitude_data,lati;
String longitude_data,longi;
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
//===================================================
void displaydata()
{
  if (gps.location.isValid())
  {
    double latitude = (gps.location.lat());
    double longitude = (gps.location.lng());
    latitude_data= (String(latitude, 6));
    longitude_data= (String(longitude, 6));   
    delay(20000);
  }
  else
  {
    Serial.println(F("Data error!!!"));
  }
}
//======================================
void setup() {
  Serial.begin(9600);
  soft.begin(9600);  
  thing.add_wifi(SSID, SSID_PASSWORD);
  thing["GPSNeo"] >> [](pson& out){
    out["latitude"] = lati;
    out["longitude"] = longi;
  };
}
//======================================
void loop() {  
  thing.handle();  
  while (soft.available() > 0)
    if (gps.encode(soft.read()))
    {
      displaydata();     
      lati=latitude_data;
      longi=longitude_data;       
    }
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("GPS Connection Error!!"));
    while (true);
  }
}
