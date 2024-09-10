/***************************************
 * Project Kontrol Servo SG90 dengan RemoteXY
 * Board  : NodeMCU ESP8266 V3
 * Input  : RemoteXY
 * Output : Servo SG90
 * 99 Proyek IoT
 * www.ardutech.com
 ****************************************/
#define REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD
#include <ESP8266WiFi.h>
#include <RemoteXY.h>
#include <Servo.h>  
//---GANTI SESUAI DENGAN JARINGAN WIFI
//---HOTSPOT ANDA
#define REMOTEXY_WIFI_SSID "ArdutechWiFi" // Nama Hotspot/WiFi
#define REMOTEXY_WIFI_PASSWORD "12345678" //  Password
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
//---GANTI SESUAI DENGAN TOKEN RemoteXY Anda
#define REMOTEXY_CLOUD_TOKEN "1198a726c98413e7f60cae35db5c64a3"
// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,1,0,0,0,37,0,10,13,1,
  129,0,4,7,56,6,17,75,111,110,
  116,114,111,108,32,83,101,114,118,111,
  32,83,71,57,48,0,4,128,3,22,
  58,13,2,26 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t slider_1; // =0..100 slider position 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

Servo myservo; 

void setup() 
{
  RemoteXY_Init (); 
  myservo.attach(D5); 
  RemoteXY.slider_1 = 50;   
}

void loop() 
{ 
  RemoteXY_Handler ();    
  int ms = RemoteXY.slider_1*20+500; 
  myservo.writeMicroseconds(ms); 

}
