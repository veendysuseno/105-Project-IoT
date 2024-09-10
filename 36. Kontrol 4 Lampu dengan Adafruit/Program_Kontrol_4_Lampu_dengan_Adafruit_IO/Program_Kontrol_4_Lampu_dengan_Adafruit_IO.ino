/***************************************
 * Project Kontrol 4 Lampu dg Adafruit IO
 * Board  : NodeMCU ESP8266 V3
 * Input  : MQTT (tombol) Adafruit IO
 * Output : Relay (Lampu)
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define WLAN_SSID       "ArdutechWiFi" // Nama Hotspot/WiFi
#define WLAN_PASS       "firmas20"     // Password
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
//---GANTI SESUAI DENGAN USER NAME ADAFRUIT  ANDA
#define AIO_USERNAME    "ArdutechJogja"
//---GANTI SESUAI DENGAN IO KEY ADAFRUIT ANDA
#define AIO_KEY         "aio_mAXJ90DJnEIBVj0IDmG6BIMZqMAW"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/photocell");
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/LED");
/*************************** Sketch Code ************************************/
void MQTT_connect();
//===================================
void setup() {
  Serial.begin(9600);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);
  delay(10);
  Serial.println(); Serial.println();
  Serial.print("Connecting to... ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  mqtt.subscribe(&onoffbutton);
}
uint32_t x=0;
//==========================
void loop() {
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton.lastread);
      if(strcmp((char*)onoffbutton.lastread,"ON1")==0){
        digitalWrite(D5,HIGH);
      }
      else if(strcmp((char*)onoffbutton.lastread,"OFF1")==0){
        digitalWrite(D5,LOW);
      }
      else if(strcmp((char*)onoffbutton.lastread,"ON2")==0){
        digitalWrite(D6,HIGH);
      }
      else if(strcmp((char*)onoffbutton.lastread,"OFF2")==0){
        digitalWrite(D6,LOW);
      }
       else if(strcmp((char*)onoffbutton.lastread,"ON3")==0){
        digitalWrite(D7,HIGH);
      }
      else if(strcmp((char*)onoffbutton.lastread,"OFF3")==0){
        digitalWrite(D7,LOW);
      }
       else if(strcmp((char*)onoffbutton.lastread,"ON4")==0){
        digitalWrite(D8,HIGH);
      }
      else if(strcmp((char*)onoffbutton.lastread,"OFF4")==0){
        digitalWrite(D8,LOW);
      }
    }
  } 
}
//=====================================================
void MQTT_connect() {
  int8_t ret;
  // Stop if already connected.
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
