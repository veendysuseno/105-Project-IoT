/***************************************
 * Project Stasiun Cuaca dg Adafruit dan BME280
 * Board  : NodeMCU ESP8266 V3
 * Input  : BME280
 * Output : Adafruit IO
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;
float temp, humi, pres, alti;

//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define WLAN_SSID       "ArdutechWiFi"  // Nama Hotspot/WiFi
#define WLAN_PASS       "12345678"      //  Password
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   
//---GANTI SESUAI DENGAN USER NAME ADAFRUIT  ANDA
#define AIO_USERNAME    "ArdutechJogja"
//---GANTI SESUAI DENGAN IO KEY ADAFRUIT ANDA
#define AIO_KEY         "aio_mAXJ90DJnEIBVj0IDmG6BIMZqMAW"
//***********************           
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/BMETemp");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/BMEHumi");
Adafruit_MQTT_Publish pressure = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/BMEPress");
Adafruit_MQTT_Publish altit = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/BMEAlti");
//===============================================
void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
//====================================================
void setup() {
  Serial.begin(9600);
  delay(100);  
  bme.begin(0x76);   
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
}
//==============================================
void loop() {
  MQTT_connect();
  temp = bme.readTemperature();
  humi = bme.readHumidity();
  pres = bme.readPressure() / 100.0F;
  alti = bme.readAltitude(SEALEVELPRESSURE_HPA);  
   if (! temperature.publish(temp)) {
      Serial.println(F("Publish Temperature Failed"));
      } else {
      Serial.println(F("Publish Temperature OK!"));
    }
   if (! humidity.publish(humi)) {
      Serial.println(F("Publish humidity Failed"));
      } else {
      Serial.println(F("Publish Humidity OK!"));
    }
   if (! pressure.publish(pres)) {
      Serial.println(F("Publish Pressure Failed"));
      } else {
      Serial.println(F("Publish Pressure OK!"));
    }
   if (! altit.publish(alti)) {
      Serial.println(F("Publish Altitude Failed"));
      } else {
      Serial.println(F("Publish Altitude OK!"));
    }
  Serial.print("Temperature=");
  Serial.println(temp);
  Serial.print("humidity=");
  Serial.println(humi);
  Serial.print("Pressure=");
  Serial.println(pres); 
  Serial.print("Altitude=");
  Serial.println(alti); 
  Serial.println();
  delay(30000);
}
