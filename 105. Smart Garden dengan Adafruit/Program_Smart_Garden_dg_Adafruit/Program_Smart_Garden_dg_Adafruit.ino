/***************************************
 * Project Smart Garden dengan Adafruit
 * Board  : NodeMCU ESP8266 V3
 * Input  : Modul Soil Moisture
 *          Modul Rain Drops
 *          DHT11
 * actuator: Relay --> pump
 * Output : Blynk
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <Wire.h> 
#include <DHT.h>

#define DHTPIN D1 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define SOILPIN A0
#define RAINPIN D2
#define PUMPPIN D3

byte humi, temp;
byte delaySend;
byte MODE=1;

//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define WLAN_SSID       "ArdutechWiFi"  // Nama Hotspot/WiFi
#define WLAN_PASS       "12345678"      //  Password
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
//---GANTI SESUAI DENGAN USER NAME ADAFRUIT  ANDA
#define AIO_USERNAME    "ArdutechJogja"
//---GANTI SESUAI DENGAN IO KEY ADAFRUIT ANDA
#define AIO_KEY         "aio_mAXJ90DJnEIBVj0IDmG6BIMZqMAW"

/************ Global State (you don't need to change this!) ******************/
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/
Adafruit_MQTT_Publish TEMP = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Temperature");
Adafruit_MQTT_Publish HUMI = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Humidity");
Adafruit_MQTT_Publish SOIL = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/soilmoisture");
Adafruit_MQTT_Publish RAIN = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Raindrop");

Adafruit_MQTT_Subscribe MANUAL = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/manual pump", MQTT_QOS_1);
Adafruit_MQTT_Subscribe PUMP = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoffpump", MQTT_QOS_1);

void onoffMANUAL(char *data, uint16_t len) {
  String message = String(data);
  message.trim();
  if (message == "ON") {MODE=2;Serial.println("MODE: 2");}
  if (message == "OFF") {MODE=1;Serial.println("MODE: 1");} 
}

void onoffPUMP(char *data, uint16_t len) {
  Serial.print("PUMP: ");
  Serial.println(data);
  String message = String(data);
  message.trim();
  if (message == "ON" && MODE==2) {digitalWrite(PUMPPIN, LOW);} //RELAY AKTIF LOW
  if (message == "OFF" && MODE==2) {digitalWrite(PUMPPIN, HIGH);}
}

void setup() {
  pinMode(PUMPPIN, OUTPUT);
  digitalWrite(PUMPPIN,LOW);   
  pinMode(RAINPIN, INPUT_PULLUP);   
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.println("SMART GARDEN");
  // Connect to WiFi access point.
  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  dht.begin();
  MANUAL.setCallback(onoffMANUAL);
  mqtt.subscribe(&MANUAL);  
  PUMP.setCallback(onoffPUMP);
  mqtt.subscribe(&PUMP);  
}

void loop() {
  MQTT_connect();
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  if (isnan(humi) || isnan(temp)) {
    Serial.println("DHT22 tidak terbaca... !");
    return;
  } 
  
  word soilMoisture=analogRead(SOILPIN);
  soilMoisture=map(soilMoisture, 0, 1023, 100, 0);

  if(MODE==1){
    if(soilMoisture<25 && digitalRead(RAINPIN)==1){
      digitalWrite(PUMPPIN, LOW);
    }
    else {
      digitalWrite(PUMPPIN, HIGH);
    }
  }
    
  Serial.print("Mode: ");
  if(MODE==1) Serial.println("Otomatis");
  else Serial.println("Manual");
  Serial.print("Pump: ");
  if(digitalRead(PUMPPIN)) Serial.println("OFF");
  else Serial.println("ON"); 
  //-----------------------------------------SEND TEMP
  Serial.print("Sending temperature: ");
  Serial.print(temp);
  Serial.print(" -->");  
  if (! TEMP.publish(temp)) {
    Serial.println("Failed");
  } else {
    Serial.println("OK!");
  }
  //-----------------------------------------SEND HUMI
  Serial.print("Sending humidity: ");
  Serial.print(humi);
  Serial.print(" -->");  
  if (! HUMI.publish(humi)) {
    Serial.println("Failed");
  } else {
    Serial.println("OK!");
  }
  //-----------------------------------------SEND SOIL MOISTURE  
  Serial.print("Sending soil moisture: ");
  Serial.print(soilMoisture);
  Serial.print(" -->");  
  if (! SOIL.publish(soilMoisture)) {
    Serial.println("Failed");
  } else {
    Serial.println("OK!");
  }
  //-----------------------------------------SEND RAINDROP STATUS  
  Serial.print("Sending rain drop status: ");
  Serial.print(digitalRead(RAINPIN));
  Serial.print(" -->");  
  if (! RAIN.publish(digitalRead(RAINPIN))) {
    Serial.println("Failed");
  } else {
    Serial.println("OK!");
  }
  
  mqtt.processPackets(10000);
  Serial.println(); 
  Serial.println(); 
}

void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { 
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 10 seconds...");
       mqtt.disconnect();
       delay(10000);  // wait 10 seconds
       retries--;
       if (retries == 0) {
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
