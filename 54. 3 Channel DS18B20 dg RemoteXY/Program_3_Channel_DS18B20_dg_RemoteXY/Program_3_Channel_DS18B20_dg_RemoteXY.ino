/***************************************
 * Project 3 Channel Sensor DS18B20 dengan RemoteXY
 * Board  : NodeMCU ESP8266 V3
 * Input  : 3 Ch DS18B20
 * Output : RemoteXY
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/

#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD
#include <ESP8266WiFi.h>

#include <RemoteXY.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define REMOTEXY_WIFI_SSID "ArdutechWiFi"  // Nama Hotspot/WiFi
#define REMOTEXY_WIFI_PASSWORD "12345678"  //  Password
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
//---GANTI SESUAI DENGAN TOKEN RemoteXY Anda
#define REMOTEXY_CLOUD_TOKEN "1198a726c98413e7f60cae35db5c64a3"
#define ONE_WIRE_BUS 14
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int numberOfDevices;
float temperature1,temperature2,temperature3;
DeviceAddress tempDeviceAddress; 
// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,0,0,3,0,52,0,10,13,1,
  129,0,3,4,56,6,17,51,32,67,
  104,97,110,110,101,108,32,68,83,49,
  56,66,50,48,0,66,132,16,13,32,
  25,2,24,66,132,17,42,31,24,96,
  24,66,132,18,71,31,24,21,24 };
  
struct {
    // output variables
  int8_t level_1; // =0..100 level position 
  int8_t level_2; // =0..100 level position 
  int8_t level_3; // =0..100 level position 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)
//==================================
void setup() 
{
  Serial.begin(9600);
  RemoteXY_Init (); 
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
}
//============================================
void loop() 
{ 
  RemoteXY_Handler ();
  sensors.requestTemperatures(); 
  for(int i=0;i<numberOfDevices; i++){
    if(sensors.getAddress(tempDeviceAddress, i)){
      float tempC = sensors.getTempC(tempDeviceAddress);
      if(i==0){
        RemoteXY.level_1 =tempC;
        Serial.print("Temperature 1: ");
        Serial.println(tempC);
      }
      else if(i==1){
        RemoteXY.level_2 =tempC;
        Serial.print("Temperature 2: ");
        Serial.println(tempC);
      }
      else if(i==2){
        RemoteXY.level_3 =tempC;
        Serial.print("Temperature 3: ");
        Serial.println(tempC);
      }
     
      }
  }
  delay(2000);
}
//========================================
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++){
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
}
