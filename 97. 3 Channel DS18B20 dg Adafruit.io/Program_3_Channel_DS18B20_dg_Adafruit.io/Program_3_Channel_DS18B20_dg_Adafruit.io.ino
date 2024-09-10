/***************************************
 * Project 3 Channel DS18B20 dg Adafruit IO
 * Board  : NodeMCU ESP8266 V3
 * Input  : 3 Ch DS18B20
 * Output : Adafruit IO
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <OneWire.h>
#include <DallasTemperature.h>
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define WLAN_SSID       "ArdutechWiFi" // Nama Hotspot/WiFi
#define WLAN_PASS       "12345678"     //  Password
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
//---GANTI SESUAI DENGAN USER NAME ADAFRUIT  ANDA
#define AIO_USERNAME    "ArdutechJogja"
//---GANTI SESUAI DENGAN IO KEY ADAFRUIT ANDA
#define AIO_KEY         "aio_mAXJ90DJnEIBVj0IDmG6BIMZqMAW"
#define ONE_WIRE_BUS 14

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish DS1 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temp1");
Adafruit_MQTT_Publish DS2 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temp2");
Adafruit_MQTT_Publish DS3 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temp3");

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int numberOfDevices;
float temperature1,temperature2,temperature3;
DeviceAddress tempDeviceAddress; 
uint32_t x=0;
void MQTT_connect();
//========================================
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++){
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
}
//=========================================================
void setup() {
  Serial.begin(9600);
  delay(10);
  sensors.begin();    
  numberOfDevices = sensors.getDeviceCount();
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");
  for(int i=0;i<numberOfDevices; i++){
    if(sensors.getAddress(tempDeviceAddress, i)){
      Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: ");
      printAddress(tempDeviceAddress);
      Serial.println();
    } else {
      Serial.print("Found ghost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
    }
  }
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
//=============================================
void loop() {  
  MQTT_connect();
  sensors.requestTemperatures(); // Send the command to get temperatures
  for(int i=0;i<numberOfDevices; i++){
    if(sensors.getAddress(tempDeviceAddress, i)){
      float tempC = sensors.getTempC(tempDeviceAddress);
      if(i==0){
        temperature1 =tempC;
        Serial.print("Temperature 1: ");
        Serial.println(tempC);
      }
      else if(i==1){
        temperature2 =tempC;
        Serial.print("Temperature 2: ");
        Serial.println(tempC);
      }
      else if(i==2){
        temperature3 =tempC;
        Serial.print("Temperature 3: ");
        Serial.println(tempC);
      }     
      }
  }
  
    if (! DS1.publish(temperature1)) {
      Serial.println(F("Publish Channel 1 Failed"));
      } else {
      Serial.println(F("Publish Channel 1 OK!"));
    }   
    
    if (! DS2.publish(temperature2)) {
      Serial.println(F("Publish Channel 2 Failed"));
      } else {
      Serial.println(F("Publish Channel 2 OK!"));
    }

    if (! DS3.publish(temperature3)) {
      Serial.println(F("Publish Channel 3 Failed"));
      } else {
      Serial.println(F("Publish Channel 3 OK!"));
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
