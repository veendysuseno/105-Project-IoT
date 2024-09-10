/***************************************
 * Project Monitoring Sensor DHT11 + BMP280 dengan Blynk
 * Board  : NodeMCU ESP8266 V3
 * Input  : DHT11, BMP280
 * Output : Blynk
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#define BLYNK_PRINT Serial 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>
#define SEALEVELPRESSURE_HPA (1013.25)
#define DHTPIN D5 // DHT11 terhubung dengan PIN D5 NODEMCU

DHT dht(DHTPIN, DHT11); 
//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "CbS0l3x8agGfefffJ9GJ6b3kKE5Q4S"; 
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi"; // Nama Hotspot/WiFi
char pass[] = "12345678";     //  Password
BlynkTimer timer;
Adafruit_BMP280 bmp;
float temperature, pressure, altitude,humidity;
//==============================================
void setup()
{
  Serial.begin(9600); 
  dht.begin();
  bmp.begin(0x76);   
  delay(10);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, ReadBMP280);   
}

//=================================================
void ReadBMP280()
{  
  pressure = bmp.readPressure()/100.0F;
  temperature = bmp.readTemperature();
  altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);
  humidity = dht.readHumidity();
  Blynk.virtualWrite(V1, pressure);     
  Blynk.virtualWrite(V2, temperature);  
  Blynk.virtualWrite(V3, humidity);  
  Blynk.virtualWrite(V4, altitude);     
      //Print values to serial monitor:
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");
 
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humi: ");
  Serial.print(humidity);
  Serial.println(" C");
 
  Serial.print("Altimeter: ");
  Serial.print(altitude); 
  Serial.println(" m");    
}
//==================================================
void loop()
{
  Blynk.run();
  timer.run();
}
