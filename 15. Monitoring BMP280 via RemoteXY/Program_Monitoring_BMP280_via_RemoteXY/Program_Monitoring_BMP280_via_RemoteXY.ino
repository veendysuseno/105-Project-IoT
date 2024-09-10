/***************************************
 * Project Monitoring Sensor BMP280 dengan RemoteXY
 * Board  : NodeMCU ESP8266 V3
 * Input  : BMP280
 * Output : RemoteXY
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD
#include <ESP8266WiFi.h>

#include <RemoteXY.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define REMOTEXY_WIFI_SSID "ArdutechWiFi"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
//---GANTI SESUAI DENGAN TOKEN RemoteXY Anda
#define REMOTEXY_CLOUD_TOKEN "1198a726c98413e7f60cae35db5c64a3"
#define SEALEVELPRESSURE_HPA (1013.25)

// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,0,0,3,0,52,0,10,13,1,
  129,0,4,8,55,6,17,77,111,110,
  105,116,111,114,105,110,103,32,66,77,
  80,50,56,48,0,66,130,6,22,33,
  26,2,26,66,132,6,57,36,28,2,
  36,66,1,49,22,10,61,2,26 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // output variables
  int8_t level_1; // =0..100 level position 
  int8_t level_2; // =0..100 level position 
  int8_t level_3; // =0..100 level position 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

Adafruit_BMP280 bmp;
float temperature, pressure, altitude;
//=====================================
void setup() 
{
  RemoteXY_Init (); 
  bmp.begin(0x76);     
  // TODO you setup code 
}
//======================================
void loop() 
{ 
  RemoteXY_Handler ();
  pressure = bmp.readPressure()/100.0F;
  temperature = bmp.readTemperature();
  altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);
  int level3=map(altitude ,0,30000,0,100);
  RemoteXY.level_1 =temperature ;
  RemoteXY.level_2 =pressure;
  RemoteXY.level_3 =level3;
 
  delay(2000);  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
}
