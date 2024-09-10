/***************************************
 * Project Monitoring BMP280 di Thingspeak
 * Board  : NodeMCU ESP8266 V3
 * Input  : BMP280
 * Output : Thingspeak
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#define SEALEVELPRESSURE_HPA (1013.25)

// ------ GANTI dengan API Keys anda di Thingspeak
String apiKey = "75DSG3UWHQKMBL9W";
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
const char* ssid = "ArdutechWiFi";// Nama Hotspot/WiFi
const char* password = "12345678";//  Password
const char* server = "api.thingspeak.com";
Adafruit_BMP280 bmp;
float temperature, pressure, altitude;
WiFiClient client;
//==========================
void setup() {
  Serial.begin(9600);
  delay(10);
  bmp.begin(0x76);   
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
//================================
void loop() {
  temperature = bmp.readTemperature();
  pressure = bmp.readPressure() / 100.0F;
  altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);
 
  if (client.connect(server,80)) { 
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(temperature);
    postStr +="&field2=";
    postStr += String(pressure);
    postStr +="&field3=";
    postStr += String(altitude);
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\r\n\r\n");
    client.print(postStr);

    Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.println(" Celsius, ");
    Serial.print("Pressure = ");
    Serial.println(pressure);
    Serial.print("Altitude = ");
    Serial.println(altitude);
    Serial.println("send to Thingspeak");
  }
  client.stop();
  Serial.println("Waiting…");
  delay(20000);  //minimal nunggu 20 detik update Thingspeak
}
