/***************************************
 * Project 2 Ch DS18B20 dg Thinger io
 * Board  : NodeMCU ESP8266 V3
 * Input  : 2 DS18B20
 * Output : thinger.io
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ThingerESP8266.h>
#define ONE_WIRE_BUS 14
//---GANTI SESUAI DENGAN USER NAME Thinger.io  ANDA
#define USERNAME "Ardutech" //Username thinger.io
//---GANTI SESUAI DENGAN DEVICE ID Thinger.io  ANDA
#define DEVICE_ID "2CH_DS18B20" 
//---GANTI SESUAI DENGAN TOKEN Thinger.io  ANDA
#define DEVICE_CREDENTIAL "6ujbucWj6nMN"
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define SSID "ArdutechWiFi"       // Nama Hotspot/WiFi
#define SSID_PASSWORD "12345678"  //  Password

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int numberOfDevices;
float temperature1,temperature2;
DeviceAddress tempDeviceAddress; 
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

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
  thing.add_wifi(SSID, SSID_PASSWORD);
  thing["DS1820"] >> [](pson& out){
    out["temp1"] = temperature1;
    out["temp2"] = temperature2;    
  };
}
//===============================================
void loop(){ 
  thing.handle();   
  sensors.requestTemperatures(); 
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
  delay(5000);
}
//==========================================
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++){
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
}
