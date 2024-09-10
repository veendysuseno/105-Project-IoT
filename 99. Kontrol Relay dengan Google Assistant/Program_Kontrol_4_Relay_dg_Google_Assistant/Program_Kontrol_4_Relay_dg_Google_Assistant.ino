 /***************************************
 * Project Kontrol 4 Relay dengan Google Assistant
 * Board  : NodeMCU ESP8266 V3
 * Input  : Google Assistant
 * Output : 4 Relay
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define RL1            D5
#define RL2            D6
#define RL3            D7
#define RL4            D8
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define WLAN_SSID       "ArdutechWiFi"  // Nama Hotspot/WiFi
#define WLAN_PASS       "12345678"   //  Password
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883    
//---GANTI SESUAI DENGAN USER NAME ADAFRUIT  ANDA               
#define AIO_USERNAME    "ArdutechJogja"
//---GANTI SESUAI DENGAN IO KEY ADAFRUIT ANDA
#define AIO_KEY         "aio_mAXJ90DJnEIBVj0IDmG6BIMZqMAW"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe Relay1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Relay1"); // FeedName
Adafruit_MQTT_Subscribe Relay2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay2");
Adafruit_MQTT_Subscribe Relay3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay3");
Adafruit_MQTT_Subscribe Relay4 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay4");

void MQTT_connect();
//======================================
void setup() {
  Serial.begin(9600);
  pinMode(RL1, OUTPUT);
  pinMode(RL2, OUTPUT);
  pinMode(RL3, OUTPUT);
  pinMode(RL4, OUTPUT);
 
  // Connect to WiFi access point.
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
  mqtt.subscribe(&Relay1);
  mqtt.subscribe(&Relay3);
  mqtt.subscribe(&Relay2);
  mqtt.subscribe(&Relay4);
}
//===============================================
void loop() {
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) {
    if (subscription == &Relay1) {
      Serial.print(F("Got: "));
      Serial.println((char *)Relay1.lastread);
      int Relay1_State = atoi((char *)Relay1.lastread);
      digitalWrite(RL1, Relay1_State);
    }
    if (subscription == &Relay2) {
      Serial.print(F("Got: "));
      Serial.println((char *)Relay2.lastread);
      int Relay2_State = atoi((char *)Relay2.lastread);
      digitalWrite(RL2, Relay2_State);
    }
    if (subscription == &Relay3) {
      Serial.print(F("Got: "));
      Serial.println((char *)Relay3.lastread);
      int Relay3_State = atoi((char *)Relay3.lastread);
      digitalWrite(RL3, Relay3_State);
    }
    if (subscription == &Relay4) {
      Serial.print(F("Got: "));
      Serial.println((char *)Relay4.lastread);
      int Relay4_State = atoi((char *)Relay4.lastread);
      digitalWrite(RL4, Relay4_State);
      
    }
  }

  
}
//=========================================
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
