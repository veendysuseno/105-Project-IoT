/***************************************
 * Project Monitoring Suhu LM35 dg Adafruit IO
 * Board  : NodeMCU ESP8266 V3
 * Input  : LM35
 * Output : Adafruit IO
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
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

/************ Global State (you don't need to change this!) ******************/
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
/****************************** Feeds ***************************************/
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
float C = 0;
uint32_t x=0;
void MQTT_connect();
//=========================================================
void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(A0, INPUT);    
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
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
}
//=============================================
void loop() {  
  MQTT_connect();
  C = (analogRead(A0) * 330.0) / 1023.0;
  Serial.print("Temperature=");
  Serial.print(C);
  Serial.print("...");
  if (! temperature.publish(C)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
  delay(5000);
}

//===============================================
void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { 
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
