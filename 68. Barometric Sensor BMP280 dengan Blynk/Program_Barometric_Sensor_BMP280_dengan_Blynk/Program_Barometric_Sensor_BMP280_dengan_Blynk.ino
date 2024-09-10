/***************************************
 * Project Monitoring Sensor BMP280 dengan Blynk
 * Board  : NodeMCU ESP8266 V3
 * Input  : BMP280
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
#define SEALEVELPRESSURE_HPA (1013.25)

//---GANTI SESUAI DENGAN TOKEN BLYNK ANDA
char auth[] = "-htbXm6E3Lizwp915_No7P516Ywa7nrj"; 
// Ganti dengan WiFi dan Password anda
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
char ssid[] = "ArdutechWiFi";  // Nama Hotspot/WiFi
char pass[] = "12345678";      //  Password
BlynkTimer timer;
Adafruit_BMP280 bmp;
float temperature, pressure, altitude;
//==============================================
void setup()
{
  Serial.begin(9600); 
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
 
  Blynk.virtualWrite(V1, pressure);     
  Blynk.virtualWrite(V2, temperature);  
  Blynk.virtualWrite(V3, altitude);      
      
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");
 
  Serial.print(("Temp: "));
  Serial.print(temperature);
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
