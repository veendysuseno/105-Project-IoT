/***************************************
 * Project Kontrol ESP8266 dengan Google Assistant
 * Board  : NodeMCU ESP8266 V3
 * Input  : Google Assistant
 * Output : LED
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
 
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define LED            D5
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define WLAN_SSID       "ArdutechWiFi" // Nama Hotspot/WiFi
#define WLAN_PASS       "12345678"  //  Password
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883          // use 8883 for SSL
//---GANTI SESUAI DENGAN USER NAME ADAFRUIT  ANDA
#define AIO_USERNAME    "ArdutechJogja"
//---GANTI SESUAI DENGAN IO KEY ADAFRUIT ANDA
#define AIO_KEY         "aio_mAXJ90DJnEIBVj0IDmG6BIMZqMAW"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe LEDONOFF = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/LED"); // FeedName

void MQTT_connect();
//==========================================
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);  
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
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
  mqtt.subscribe(&LEDONOFF);
}

void loop() {
  MQTT_connect();  
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) {
    if (subscription == &LEDONOFF) {
      Serial.print(F("Got: "));
      Serial.println((char *)LEDONOFF.lastread);
      int Light1_State = atoi((char *)LEDONOFF.lastread);
      digitalWrite(LED, Light1_State);      
    }    
  } 
}
//===========================================================
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
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
  
}
