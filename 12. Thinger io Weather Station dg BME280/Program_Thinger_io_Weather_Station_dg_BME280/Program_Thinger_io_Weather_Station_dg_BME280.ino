/***************************************
 * Project Thinger io Weather Station
 * Board  : NodeMCU ESP8266 V3
 * Input  : BME280
 * Output : thinger.io
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include <ThingerESP8266.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)
//---GANTI SESUAI DENGAN USER NAME Thinger.io  ANDA
#define USERNAME "Ardutech" //Username thinger.io
//---GANTI SESUAI DENGAN DEVICE ID Thinger.io  ANDA
#define DEVICE_ID "Mon_BME280" 
//---GANTI SESUAI DENGAN TOKEN Thinger.io  ANDA
#define DEVICE_CREDENTIAL "RxPyfxVuP581"
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define SSID "ArdutechWiFi"       // Nama Hotspot/WiFi
#define SSID_PASSWORD "12345678"  //  Password

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
Adafruit_BME280 bme;
float temperature, humidity, pressure, altitude;

//=============================
void setup() {
  Serial.begin(9600);
  Serial.println("Baca BME280");
  delay(100);
  bme.begin(0x76);  
  thing.add_wifi(SSID, SSID_PASSWORD);
  thing["BME280"] >> [](pson& out){
    out["temp"] = temperature;
    out["humi"] = humidity;
    out["press"] = pressure;
    out["alti"] = altitude;
  };
}
//====================================
void loop() {  
  thing.handle();   
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA); 
  Serial.println(temperature);
  Serial.println(humidity);
  Serial.println(pressure);
  Serial.println(altitude);
  delay(1000);
}
