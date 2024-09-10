/***************************************
 * Project 2 Ch DS18B20 dg ThingSpeak
 * Board  : NodeMCU ESP8266 V3
 * Input  : 2 DS18B20
 * Output : ThingSpeak
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#define ONE_WIRE_BUS 14

// ganti dengan API Keys anda di Thingspeak
String apiKey = "Z6SZ8RUO760NFP26";
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
const char* ssid = "ArdutechWiFi";  // Nama Hotspot/WiFi
const char* password = "12345678";  //  Password
const char* server = "api.thingspeak.com";
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int numberOfDevices;
float temperature1,temperature2;
DeviceAddress tempDeviceAddress; 
WiFiClient client;
//============================
void ReadDS18B20(){
   sensors.requestTemperatures(); // Send the command to get temperatures
   for(int i=0;i<numberOfDevices; i++){
   if(sensors.getAddress(tempDeviceAddress, i)){
      float tempC = sensors.getTempC(tempDeviceAddress);
      if(i==0){
        temperature1=tempC;         
        Serial.print("Temperature 1: ");
        Serial.println(temperature1);
      }
      else if(i==1){
        temperature2=tempC;        
        Serial.print("Temperature 2: ");
        Serial.println(temperature2);
      }     
      }  
}  
}
//=============================
void setup(){
  Serial.begin(9600);
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
  delay(10);
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
//===============================================
void loop(){ 
  ReadDS18B20();
  if (client.connect(server,80)) { 
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(temperature1);
    postStr +="&field2=";
    postStr += String(temperature2);
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("DS18B20 Ch 1: ");
    Serial.print(temperature1);
    Serial.print("DS18B20 Ch 2: ");
    Serial.print(temperature2);
    Serial.println(" send to Thingspeak");
  }
  client.stop();
  Serial.println("Waiting…");
  delay(20000);
}
//=========================================
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++){
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
}
